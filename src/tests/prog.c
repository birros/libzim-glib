#include <stdio.h>
#include "file.h"
#include "fileheader.h"
#include "article.h"
#include "search.h"
#include "search-iterator.h"
#include "misc.h"

#define STYLE_BOLD    "\033[1m"
#define STYLE_NO_BOLD "\033[22m"

int
main (int argc, char *argv[])
{
    // filename argument
    char *filename;
    if (argc == 2) {
        filename = argv [1];
    } else {
        fprintf (stderr, "missing zim file argument, see README.md\n");
        return 1;
    }


    // init zim
    GError* err = NULL;
    ZimFile *zim_file = zim_file_new (filename, &err);
    if (err != NULL)
    {
        fprintf (stderr, "%s\n", err->message);
        g_error_free (err);
        return 1;
    }


    // zim file
    printf ("==ZIM FILE==\n");

    printf (STYLE_BOLD "zim_path: " STYLE_NO_BOLD "%s\n", filename);


    // main_page
    printf ("==MAIN PAGE==\n");

    ZimFileheader *fileheader = zim_file_get_fileheader (zim_file);
    gboolean has_main_page = zim_fileheader_has_main_page (fileheader);
    unsigned int main_page_index;
    ZimArticle *main_page;
    const char *main_page_url;

    if (has_main_page) {
        main_page_index = zim_fileheader_get_main_page (fileheader);
        main_page = zim_file_get_article_by_index (zim_file, main_page_index);
        main_page_url = zim_article_get_url (main_page);
    }

    if (has_main_page) {
        printf (STYLE_BOLD "main_page_index: " STYLE_NO_BOLD "%u\n", main_page_index);
        printf (STYLE_BOLD "main_page_url:   " STYLE_NO_BOLD "%s\n", main_page_url);
    } else {
        printf ("doesn't has main page\n");
    }


    // misc
    printf ("==MISC==\n");

    const char *urlencoded = "Wikip%C3%A9dia";
    const char *urldecoded = zim_urldecode (urlencoded);

    printf (STYLE_BOLD "urlencoded: " STYLE_NO_BOLD "%s\n", urlencoded);
    printf (STYLE_BOLD "urldecoded: " STYLE_NO_BOLD "%s\n", urldecoded);


    // first_article
    printf ("==FIRST ARTICLE==\n");

    unsigned int articles_namespace_begin_offset = zim_file_get_namespace_begin_offset (zim_file, 'A');
    ZimArticle *first_article = zim_file_get_article_by_index (zim_file, articles_namespace_begin_offset);
    const char *first_article_url = zim_article_get_url (first_article);
    const char *first_article_mime_type = zim_article_get_mime_type (first_article);

    printf (STYLE_BOLD "articles_namespace_begin_offset: " STYLE_NO_BOLD "%u\n", articles_namespace_begin_offset);
    printf (STYLE_BOLD "first_article_url:               " STYLE_NO_BOLD "%s\n", first_article_url);
    printf (STYLE_BOLD "first_article_mime_type:         " STYLE_NO_BOLD "%s\n", first_article_mime_type);


    // first_article redirect
    printf ("==FIRST ARTICLE REDIRECT==\n");

    gboolean is_redirect = zim_article_is_redirect (first_article);
    ZimArticle *redirect_article;
    const char *redirect_article_url;

    if (is_redirect) {
        redirect_article = zim_article_get_redirect_article (first_article);
        redirect_article_url = zim_article_get_url (redirect_article);
    }

    if (is_redirect) {
        printf (STYLE_BOLD "redirect_article_url: " STYLE_NO_BOLD "%s\n", redirect_article_url);
    } else {
        printf ("no redirection\n");
    }


    // first article data (10 first lines)
    printf ("==FIRST ARTICLE DATA (10 first lines)==\n");

    gsize size;
    const char* data = zim_article_get_data (first_article, &size);
    char **lines = g_strsplit (data, "\n", 0);

    // print 10 first lines
    unsigned int i = 0;
    while (lines[i] != NULL && i < 10) {
        printf ("%s\n", lines[i]);
        i++;
    }


    //g_assert_cmpstr (first_article_url, ==, "!!!.html");


    // zim search suggestion mode (10 first results)
    printf ("==ZIM SEARCH SUGGESTION MODE (10 first results)==\n");

    ZimSearch *search = zim_search_new (zim_file);
    g_object_unref (zim_file);
    zim_search_set_query (search, "ab");
    zim_search_set_range (search, 0, 10);
    zim_search_set_suggestion_mode (search, TRUE);

    unsigned int matches_estimated = zim_search_get_matches_estimated (search);
    printf (STYLE_BOLD "matches_estimated: " STYLE_NO_BOLD "%d\n", matches_estimated);

    ZimSearchIterator *search_iterator = zim_search_begin (search);
    g_object_unref (search);
    do {
        const char *title = zim_search_iterator_get_title(search_iterator);
        const char *url = zim_search_iterator_get_url(search_iterator);
        printf (STYLE_BOLD "title: " STYLE_NO_BOLD "%s\n", title);
        printf (STYLE_BOLD "\turl: " STYLE_NO_BOLD "%s\n", url);
    } while (zim_search_iterator_next(search_iterator));


    return 0;
}
