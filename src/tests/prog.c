#include <assert.h>
#include <stdio.h>
#include "archive.h"
#include "suggestion-searcher.h"

int main(int argc, char *argv[])
{
    char *filename;
    if (argc == 2)
    {
        filename = argv[1];
    }
    else
    {
        fprintf(stderr, "missing zim archive argument\n");
        return 1;
    }

    GError *err = NULL;
    ZimArchive *zim_archive = zim_archive_new(filename, &err);
    if (err != NULL)
    {
        fprintf(stderr, "%s\n", err->message);
        g_error_free(err);
        return 1;
    }

    unsigned int article_count = zim_archive_get_all_entry_count(zim_archive);
    assert(article_count == 7646);

    unsigned int filesize = zim_archive_get_filesize(zim_archive);
    assert(filesize == 32131510);

    const char *uuid = zim_archive_get_uuid(zim_archive);
    assert(strcmp(uuid, "b82357c7-c074-ac4c-ec07-9a30a1d77791") == 0);

    const char *counter = zim_archive_get_metadata(zim_archive, "Counter", &err);
    if (err != NULL)
    {
        fprintf(stderr, "%s\n", err->message);
        g_error_free(err);
        return 1;
    }
    assert(strcmp(counter, "text/plain=10;text/css=23;application/javascript=20;image/png=60;text/html=1837;image/svg+xml=208;image/jpeg=62;application/pdf=4;image/gif=3") == 0);

    ZimItem *illustration_item = zim_archive_get_illustration_item(zim_archive, 48, &err);
    if (err != NULL)
    {
        fprintf(stderr, "%s\n", err->message);
        g_error_free(err);
        return 1;
    }

    const char *illustration_mimetype = zim_item_get_mimetype(illustration_item);
    assert(strcmp(illustration_mimetype, "image/png") == 0);

    gboolean has_main_entry = zim_archive_has_main_entry(zim_archive);
    assert(has_main_entry == TRUE);

    ZimEntry *main_entry = zim_archive_get_main_entry(zim_archive, &err);
    if (err != NULL)
    {
        fprintf(stderr, "%s\n", err->message);
        g_error_free(err);
        return 1;
    }

    const char *main_entry_title = zim_entry_get_title(main_entry);
    assert(strcmp(main_entry_title, "Main Page") == 0);

    const char *main_entry_path = zim_entry_get_path(main_entry);
    assert(strcmp(main_entry_path, "A/index") == 0);

    ZimItem *main_item = zim_entry_get_item(main_entry, TRUE);

    const char *main_item_title = zim_item_get_title(main_item);
    assert(strcmp(main_item_title, "Main Page") == 0);

    const char *main_item_path = zim_item_get_path(main_item);
    assert(strcmp(main_item_path, "A/index") == 0);

    const char *main_item_mimetype = zim_item_get_mimetype(main_item);
    assert(strcmp(main_item_mimetype, "text/html") == 0);

    gsize main_item_size = zim_item_get_size(main_item);
    assert(main_item_size == 17207);

    gsize size;
    const char *data = zim_item_get_data(main_item, &size);
    char **lines = g_strsplit(data, "\n", 0);
    assert(strcmp(lines[0], "<html><head>") == 0);

    ZimSuggestionSearcher *suggestion_searcher = zim_suggestion_searcher_new(zim_archive);
    ZimSuggestionSearch *suggestion_search = zim_suggestion_searcher_suggest(suggestion_searcher, "paris");
    ZimSuggestionResultIterator *results_iterator = zim_suggestion_search_get_results(suggestion_search, 0, 1);
    do
    {
        GError *err = NULL;
        ZimEntry *entry = zim_suggestion_result_iterator_get_entry(results_iterator, &err);
        if (err != NULL)
        {
            fprintf(stderr, "%s\n", err->message);
            g_error_free(err);
            continue;
        }

        const char *title = zim_entry_get_title(entry);
        const char *path = zim_entry_get_path(entry);
        assert(strcmp(title, "Paris 2015") == 0);
        assert(strcmp(path, "A/Paris_2015") == 0);
    } while (zim_suggestion_result_iterator_next(results_iterator));

    return 0;
}
