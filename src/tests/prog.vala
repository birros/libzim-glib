const string STYLE_BOLD    = "\033[1m";
const string STYLE_NO_BOLD = "\033[22m";

public class Suggestion {
    public string title;
    public string url;
}

public class ZimReader {
    private Zim.File zim_file;
    private List<Suggestion> suggestions;
    private uint suggestions_offset;

    public ZimReader (Zim.File zim_file) {
        this.zim_file = zim_file;

        suggestions = new List<Suggestion> ();
        suggestions_offset = 0;
    }

    public string get_title () {
        return getMetatag ("Title");
    }

    public string get_date () {
        return getMetatag ("Date");
    }

    public string get_language () {
        return getMetatag ("Language");
    }

    public string get_tags () {
        return getMetatag ("Tags");
    }

    public string get_name () {
        return getMetatag ("Name");
    }

    public string get_description () {
        return getMetatag ("Description");
    }

    public string get_creator () {
        return getMetatag ("Creator");
    }

    public string get_publisher () {
        return getMetatag ("Publisher");
    }

    public ulong get_file_size () {
        ulong size = zim_file.get_filesize ();
        return size / 1024;
    }

    public string get_id () {
        Zim.Fileheader fileheader = zim_file.get_fileheader ();
        string uuid = fileheader.get_uuid ();
        return uuid;
    }

    public string get_random_page_url () {
        uint articles_namespace_begin_offset =
            zim_file.get_namespace_begin_offset ('A');
        uint articles_namespace_count = zim_file.get_namespace_count ('A');

        int random_number = Random.int_range(0, (int) articles_namespace_count);
        uint idx = articles_namespace_begin_offset + random_number;

        Zim.Article article = zim_file.get_article_by_index (idx);
        string url = "A/" + article.get_url ();

        return url;
    }

    public uint get_article_count () {
        HashTable<string, uint> table = parseCounterMetadata ();

        uint count = table.get ("text/html");
        if (count == 0) {
            count = zim_file.get_namespace_count ('A');
        }

        return count;
    }

    public uint get_media_count () {
        HashTable<string, uint> table = parseCounterMetadata ();

        uint count = 0;
        string [] types = {"image/jpeg", "image/gif", "image/png"};
        foreach (unowned string type in types) {
            count += table.get (type);
        }

        if (count == 0) {
            count = zim_file.get_namespace_count ('I');
        }
        return count;
    }

    public uint get_global_count () {
        uint global_count = zim_file.get_count_articles ();
        return global_count;
    }

    public bool get_faveicon (out uint8[] data, out string mimetype) {
        uint8[] foo = {};
        data = foo;
        mimetype = "";

        string [] paths = {
            "-/favicon.png", "I/favicon.png", "I/favicon", "-/favicon"
        };
        foreach (unowned string path in paths) {
            string [] infos = path.split ("/");
            char namesp = infos[0][0];
            string url = infos[1];

            Zim.Article article = zim_file.get_article_by_namespace (
                namesp, url
            );
            if (article.good ()) {
                data = article.get_data ();
                mimetype = article.get_mime_type ();
                return true;
            }
        }

        return false;
    }

    public bool get_next_suggestion (
        out string suggestion_title,
        out string suggestion_url
    ) {
        if (this.suggestions_offset != this.suggestions.length()) {
            Suggestion suggestion = this.suggestions.nth_data (
              this.suggestions_offset
            );
            suggestion_title = suggestion.title;
            suggestion_url = suggestion.url;
            this.suggestions_offset++;
            return true;
        } else {
            suggestion_title = "";
            suggestion_url = "";
            return false;
        }
    }

    public void search_suggestions_smart (string query, uint limit) {
        this.suggestions = new List<Suggestion> ();
        this.suggestions_offset = 0;

        Zim.Search search = new Zim.Search (zim_file);
        search.set_query (query);
        search.set_range (0, limit);
        search.set_suggestion_mode (true);

        uint matches_estimated = search.get_matches_estimated ();

        if (matches_estimated > 0) {
            Zim.SearchIterator search_iterator = search.begin ();
            do {
                Suggestion suggestion = new Suggestion ();
                suggestion.title = search_iterator.get_title();
                suggestion.url = "/" + search_iterator.get_url();
                this.suggestions.append (suggestion);
            } while (search_iterator.next());
        } else {
            string[] variants = get_title_variants (query);
            foreach (string variant in variants) {
                search_suggestions (variant, limit);
            }
        }
    }

    private string[] get_title_variants (string title) {
        string[] variants = {};
        variants += title;
        variants += change_case (title, true, false); //first letter upper case
        variants += change_case (title, false, false); //first letter lower case
        variants += change_case (title, true, true); //title case
        return variants;
    }

    private string change_case (string title, bool upper, bool title_case) {
        bool next = true;

        StringBuilder result = new StringBuilder ();
        unichar c;

        for (int i = 0; title.get_next_char (ref i, out c);) {
            if (next) {
                if (upper || title_case) {
                    result.append_unichar (c.totitle ());
                } else {
                    result.append_unichar (c.tolower ());
                }
                next = false;
            } else {
                if (title_case) {
                    result.append_unichar (c.tolower ());
                    next = c.isspace () || c.iscntrl ();
                } else {
                    result.append_unichar (c);
                }
            }
        }

        return result.str;
    }

    private void search_suggestions (string query, uint limit) {
        if (this.suggestions.length () > limit) {
            return;
        }

        if (query.length == 0) {
            return;
        }

        Zim.FileIterator file_iterator = zim_file.find_by_title ('A', query);
        while (true) {
            Zim.Article article = file_iterator.get_article();

            Suggestion suggestion = new Suggestion ();
            suggestion.title = article.get_title();
            suggestion.url = "/A/" + article.get_url();

            if (suggestion.title.has_prefix (query)) {
                bool insert = true;
                this.suggestions.foreach ((item) => {
                    if (item.url == suggestion.url) {
                        insert = false;
                        return;
                    }
                });
                if (insert) {
                    this.suggestions.append (suggestion);
                }
            }

            if (!(
                  file_iterator.next() &&
                  this.suggestions.length () < limit &&
                  suggestion.title.has_prefix (query)
                )) {
                break;
            }
        }
    }

    private HashTable<string, uint> parseCounterMetadata () {
        HashTable<string, uint> table = new HashTable<string, uint> (
            str_hash, str_equal
        );

        string counter = getMetatag ("Counter");
        string[] lines = counter.split (";");
        foreach (unowned string line in lines) {
            string[] infos = line.split ("=");
            if (infos.length == 2) {
                string mimetype = infos[0];
                uint count = (uint) uint64.parse (infos[1]);
                table.insert (mimetype, count);
            }
        }
        return table;
    }

    private string getMetatag (string name) {
        Zim.Article article = zim_file.get_article_by_namespace ('M', name);

        if (article.good ()) {
            uint8[] data = article.get_data ();
            var builder = new StringBuilder ();
            builder.append_len ((string)data, data.length);
            return builder.str;
        }

        return "";
    }
}

static int main (string[] argv) {
    // filename argument
    string filename;
    if (argv.length == 2) {
        filename = argv [1];
    } else {
        error ("missing zim file argument, see README.md");
    }


    // init zim
    Zim.File zim_file;
    try {
        zim_file = new Zim.File (filename);
    } catch (Error e) {
        error ("%s\n", e.message);
    }


    // zim file
    stdout.printf ("==ZIM FILE==\n");

    stdout.printf (STYLE_BOLD + "zim_path: " + STYLE_NO_BOLD + "%s\n", filename);


    // main_page
    stdout.printf ("==MAIN PAGE==\n");

    Zim.Fileheader fileheader = zim_file.get_fileheader ();
    bool has_main_page = fileheader.has_main_page ();
    uint main_page_index = 0;
    Zim.Article main_page;
    string main_page_url = "";

    if (has_main_page) {
        main_page_index = fileheader.get_main_page ();
        main_page = zim_file.get_article_by_index (main_page_index);
        main_page_url = main_page.get_url ();
    }

    if (has_main_page) {
        stdout.printf (STYLE_BOLD + "main_page_index: " + STYLE_NO_BOLD + "%u\n", main_page_index);
        stdout.printf (STYLE_BOLD + "main_page_url:   " + STYLE_NO_BOLD + "%s\n", main_page_url);
    } else {
        stdout.printf ("doesn't has main page\n");
    }


    // misc
    stdout.printf ("==MISC==\n");

    const string urlencoded = "Wikip%C3%A9dia";
    string urldecoded = Zim.urldecode (urlencoded);

    stdout.printf (STYLE_BOLD + "urlencoded: " + STYLE_NO_BOLD + "%s\n", urlencoded);
    stdout.printf (STYLE_BOLD + "urldecoded: " + STYLE_NO_BOLD + "%s\n", urldecoded);


    // first_article
    stdout.printf ("==FIRST ARTICLE==\n");

    uint articles_namespace_begin_offset = zim_file.get_namespace_begin_offset ('A');
    Zim.Article first_article = zim_file.get_article_by_index (articles_namespace_begin_offset);
    string first_article_url = first_article.get_url ();
    string first_article_mime_type = first_article.get_mime_type ();

    stdout.printf (STYLE_BOLD + "articles_namespace_begin_offset: " + STYLE_NO_BOLD + "%u\n", articles_namespace_begin_offset);
    stdout.printf (STYLE_BOLD + "first_article_url:               " + STYLE_NO_BOLD + "%s\n", first_article_url);
    stdout.printf (STYLE_BOLD + "first_article_mime_type:         " + STYLE_NO_BOLD + "%s\n", first_article_mime_type);


    // first_article redirect
    stdout.printf ("==FIRST ARTICLE REDIRECT==\n");

    bool is_redirect = first_article.is_redirect ();
    Zim.Article redirect_article;
    string redirect_article_url = "";

    if (is_redirect) {
        redirect_article = first_article.get_redirect_article ();
        redirect_article_url = redirect_article.get_url ();
    }

    if (is_redirect) {
        stdout.printf (STYLE_BOLD + "redirect_article_url: " + STYLE_NO_BOLD + "%s\n", redirect_article_url);
    } else {
        stdout.printf ("no redirection\n");
    }


    // first article data (10 first lines)
    stdout.printf ("==FIRST ARTICLE DATA (10 first lines)==\n");

    uint8[] data = first_article.get_data ();
    string data_string = (string) data;
    string[] lines = data_string.split ("\n");

    // print 10 first lines
    uint i = 0;
    while (lines[i] != null && i < 10) {
        stdout.printf ("%s\n", lines[i]);
        i++;
    }


    //assert (first_article_url == "!!!.html");


    // zim search suggestion mode (10 first results)
    stdout.printf ("==ZIM SEARCH SUGGESTION MODE (10 first results)==\n");

    Zim.Search search = new Zim.Search (zim_file);
    search.set_query ("ab");
    search.set_range (0, 10);
    search.set_suggestion_mode (true);

    uint matches_estimated = search.get_matches_estimated ();
    stdout.printf (STYLE_BOLD + "matches_estimated: " + STYLE_NO_BOLD + "%d\n", matches_estimated);

    Zim.SearchIterator search_iterator = search.begin ();
    do {
        string title = search_iterator.get_title();
        string url = search_iterator.get_url();
        stdout.printf (STYLE_BOLD + "title: " + STYLE_NO_BOLD + "%s\n", title);
        stdout.printf (STYLE_BOLD + "\turl: " + STYLE_NO_BOLD + "%s\n", url);
    } while (search_iterator.next());


    // zim find by title
    stdout.printf ("==ZIM FIND BY TITLE==\n");

    uint suggestion_size = 0;
    const uint suggestion_count = 10;

    Zim.FileIterator file_iterator = zim_file.find_by_title ('A', "ab");
    do {
        Zim.Article article = file_iterator.get_article();
        string title = article.get_title();
        string url = article.get_url();
        stdout.printf (STYLE_BOLD + "title: " + STYLE_NO_BOLD + "%s\n", title);
        stdout.printf (STYLE_BOLD + "\turl: " + STYLE_NO_BOLD + "%s\n", url);

        suggestion_size++;
    } while (file_iterator.next() && suggestion_size < suggestion_count);


    // ZimReader (Replacement of Kiwix.Reader)
    stdout.printf ("===============================================\n");
    stdout.printf ("====ZimReader (Replacement of Kiwix.Reader)====\n");
    stdout.printf ("===============================================\n");

    ZimReader reader = new ZimReader (zim_file);

    // infos
    stdout.printf ("==INFOS==\n");

    string title = reader.get_title ();
    string date = reader.get_date ();
    string language = reader.get_language ();
    string tags = reader.get_tags ();
    string name = reader.get_name ();
    string description = reader.get_description ();
    string creator = reader.get_creator ();
    string publisher = reader.get_publisher ();
    ulong file_size = reader.get_file_size ();
    string id = reader.get_id ();
    string random_page_url = reader.get_random_page_url ();
    uint article_count = reader.get_article_count ();
    uint media_count = reader.get_media_count ();
    uint global_count = reader.get_global_count ();

    stdout.printf (STYLE_BOLD + "Archive path:    " + STYLE_NO_BOLD + "%s\n", filename);
    stdout.printf (STYLE_BOLD + "Title:           " + STYLE_NO_BOLD + "%s\n", title);
    stdout.printf (STYLE_BOLD + "Date:            " + STYLE_NO_BOLD + "%s\n", date);
    stdout.printf (STYLE_BOLD + "Language:        " + STYLE_NO_BOLD + "%s\n", language);
    stdout.printf (STYLE_BOLD + "Tags:            " + STYLE_NO_BOLD + "%s\n", tags);
    stdout.printf (STYLE_BOLD + "Name:            " + STYLE_NO_BOLD + "%s\n", name);
    stdout.printf (STYLE_BOLD + "Description:     " + STYLE_NO_BOLD + "%s\n", description);
    stdout.printf (STYLE_BOLD + "Creator:         " + STYLE_NO_BOLD + "%s\n", creator);
    stdout.printf (STYLE_BOLD + "Publisher:       " + STYLE_NO_BOLD + "%s\n", publisher);
    stdout.printf (STYLE_BOLD + "File size:       " + STYLE_NO_BOLD + "%d\n", file_size);
    stdout.printf (STYLE_BOLD + "ID:              " + STYLE_NO_BOLD + "%s\n", id);
    stdout.printf (STYLE_BOLD + "Random page url: " + STYLE_NO_BOLD + "%s\n", random_page_url);
    stdout.printf (STYLE_BOLD + "Article count:   " + STYLE_NO_BOLD + "%u\n", article_count);
    stdout.printf (STYLE_BOLD + "Media count:     " + STYLE_NO_BOLD + "%u\n", media_count);
    stdout.printf (STYLE_BOLD + "Global count:    " + STYLE_NO_BOLD + "%u\n", global_count);


    // favicon
    stdout.printf ("==FAVICON==\n");

    uint8[]? favicon_data;
    string mime_type;
    reader.get_faveicon (out favicon_data, out mime_type);
    uint favicon_size = favicon_data.length;

    stdout.printf (STYLE_BOLD + "Faveicon size     : " + STYLE_NO_BOLD + "%lu\n", favicon_size);
    stdout.printf (STYLE_BOLD + "Faveicon mime type: " + STYLE_NO_BOLD + "%s\n", mime_type);

    // write faveicon to file
    FileStream f = FileStream.open ("faveicon-from-vala.png", "wb");
    f.write (favicon_data);


    // suggestions
    stdout.printf ("==SUGGESTIONS==\n");

    reader.search_suggestions_smart ("ab", 20);

    string suggestion;
    string suggestion_url;
    while (reader.get_next_suggestion (out suggestion, out suggestion_url)) {
        stdout.printf (STYLE_BOLD + "Suggestion: " + STYLE_NO_BOLD + "%s, ", suggestion);
        stdout.printf (STYLE_BOLD + "Suggestion url: " + STYLE_NO_BOLD + "%s\n", suggestion_url);
    }


    return 0;
}
