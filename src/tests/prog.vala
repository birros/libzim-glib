const string STYLE_BOLD    = "\033[1m";
const string STYLE_NO_BOLD = "\033[22m";

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

    return 0;
}
