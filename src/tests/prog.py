#!/usr/bin/env python3

import sys
import gi
gi.require_version('Zim', '3.0')
from gi.repository import Zim
from gi.repository import GLib

STYLE_BOLD    = "\033[1m"
STYLE_NO_BOLD = "\033[22m"

def main (argc, argv):
    # filename argument
    if argc == 2:
        filename = argv[1]
    else:
        print ("missing zim file argument, see README.md", file=sys.stderr)
        exit (1)


    # init zim
    try:
        zim_file = Zim.File.new (filename)
    except GLib.Error as e:
        print (e, file=sys.stderr)
        exit (1)


    # zim file
    print ("==ZIM FILE==")

    print (STYLE_BOLD + "zim_path: " + STYLE_NO_BOLD + filename);


    # main_page
    print ("==MAIN PAGE==")

    fileheader = zim_file.get_fileheader ()
    has_main_page = fileheader.has_main_page ()
    main_page_index = None
    main_page = None
    main_page_url = None

    if has_main_page:
        main_page_index = fileheader.get_main_page ()
        main_page = zim_file.get_article_by_index (main_page_index)
        main_page_url = main_page.get_url ()

    if has_main_page:
        print (STYLE_BOLD + "main_page_index: " + STYLE_NO_BOLD + str(main_page_index))
        print (STYLE_BOLD + "main_page_url:   " + STYLE_NO_BOLD + main_page_url)
    else:
        print ("doesn't has main page")


    # misc
    print ("==MISC==")

    urlencoded = "Wikip%C3%A9dia"
    urldecoded = Zim.urldecode (urlencoded)

    print (STYLE_BOLD + "urlencoded: " + STYLE_NO_BOLD + urlencoded);
    print (STYLE_BOLD + "urldecoded: " + STYLE_NO_BOLD + urldecoded);


    # first_article
    print ("==FIRST ARTICLE==")

    articles_namespace_begin_offset = zim_file.get_namespace_begin_offset (ord('A'))
    first_article = zim_file.get_article_by_index (articles_namespace_begin_offset)
    first_article_url = first_article.get_url ()
    first_article_mime_type = first_article.get_mime_type ();

    print (STYLE_BOLD + "articles_namespace_begin_offset: " + STYLE_NO_BOLD + str(articles_namespace_begin_offset))
    print (STYLE_BOLD + "first_article_url:               " + STYLE_NO_BOLD + first_article_url)
    print (STYLE_BOLD + "first_article_mime_type:         " + STYLE_NO_BOLD + first_article_mime_type)


    # first_article redirect
    print ("==FIRST ARTICLE REDIRECT==")

    is_redirect = first_article.is_redirect ()
    redirect_article = None
    redirect_article_url = None

    if is_redirect:
        redirect_article = first_article.get_redirect_article ()
        redirect_article_url = redirect_article.get_url ()

    if is_redirect:
        print (STYLE_BOLD + "redirect_article_url: " + STYLE_NO_BOLD + redirect_article_url)
    else:
        print ("no redirection")


    # first article data (10 first lines)
    print ("==FIRST ARTICLE DATA (10 first lines)==")

    data = first_article.get_data ()
    lines = data.splitlines ()

    # print 10 first lines
    for index, line in enumerate(lines):
        print (line.decode ())
        if index == 9:
            break


    #assert (first_article_url == "!!!.html" )


    # zim search suggestion mode (10 first results)
    print ("==ZIM SEARCH SUGGESTION MODE (10 first results)==");

    search = Zim.Search.new (zim_file)
    search.set_query ("ab")
    search.set_range (0, 10)
    search.set_suggestion_mode (True)

    matches_estimated = search.get_matches_estimated ()
    print(STYLE_BOLD + "matches_estimated: " + STYLE_NO_BOLD + str(matches_estimated))

    search_iterator = search.begin ();
    while True:
        title = search_iterator.get_title();
        url = search_iterator.get_url();
        print (STYLE_BOLD + "title: " + STYLE_NO_BOLD + title);
        print (STYLE_BOLD + "\turl: " + STYLE_NO_BOLD + url);
        if not search_iterator.next ():
            break;


    # zim find by title
    print ("==ZIM FIND BY TITLE==")

    suggestion_size = 0
    suggestion_count = 10

    file_iterator = zim_file.find_by_title (ord('A'), "ab")
    while True:
        article = file_iterator.get_article()
        title = article.get_title()
        url = article.get_url()
        print (STYLE_BOLD + "title: " + STYLE_NO_BOLD + title)
        print (STYLE_BOLD + "\turl: " + STYLE_NO_BOLD + url)

        suggestion_size += 1
        if not (file_iterator.next () and suggestion_size < suggestion_count):
            break;


if __name__ == "__main__":
    main (len(sys.argv), sys.argv)
