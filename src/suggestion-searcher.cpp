#include <iostream>
#include <memory.h>
#include <zim/suggestion.h>
#include "suggestion-searcher.h"
#include "archive.h"
#include "archive-private.h"
#include "suggestion-search.h"
#include "suggestion-search-private.h"

/**
 * SECTION: zim-suggestion_searcher
 * @Title: ZimSuggestionSearcher
 * @short_description: A zim suggestion_searcher
 *
 * #ZimSuggestionSearcher represent a suggestion_searcher for a zim file.
 */

#define ZIM_SUGGESTION_SEARCHER_GET_PRIVATE(obj) \
    ((ZimSuggestionSearcherPrivate *) zim_suggestion_searcher_get_instance_private ((ZimSuggestionSearcher *) (obj)))

typedef struct _ZimSuggestionSearcherPrivate ZimSuggestionSearcherPrivate;
struct _ZimSuggestionSearcherPrivate
{
    ZimArchive *zim_archive;
    zim::SuggestionSearcher suggestion_searcher;
};

G_DEFINE_TYPE_WITH_PRIVATE (ZimSuggestionSearcher, zim_suggestion_searcher, G_TYPE_OBJECT)

static void
zim_suggestion_searcher_finalize (GObject *gobject)
{
    ZimSuggestionSearcherPrivate *priv = ZIM_SUGGESTION_SEARCHER_GET_PRIVATE (gobject);

    g_object_unref (priv->zim_archive);

    G_OBJECT_CLASS (zim_suggestion_searcher_parent_class)->dispose (gobject);
}

static void
zim_suggestion_searcher_class_init (ZimSuggestionSearcherClass *klass)
{
    G_OBJECT_CLASS (klass)->finalize = zim_suggestion_searcher_finalize;
}

static void
zim_suggestion_searcher_init (ZimSuggestionSearcher *object)
{
}

/**
 * zim_suggestion_searcher_new:
 * @zim_archive: a #ZimArchive
 *
 * Allocates a new #ZimSuggestionSearcher.
 *
 * Returns: (transfer full): the newly created #ZimSuggestionSearcher instance
 */
ZimSuggestionSearcher *
zim_suggestion_searcher_new (ZimArchive *zim_archive)
{
    ZimSuggestionSearcher *suggestion_searcher = (ZimSuggestionSearcher *) g_object_new (ZIM_TYPE_SUGGESTION_SEARCHER, NULL);
    ZimSuggestionSearcherPrivate *priv = ZIM_SUGGESTION_SEARCHER_GET_PRIVATE (suggestion_searcher);

    zim::Archive* archive_cpp = zim_archive_get_internal_zim_archive(zim_archive);

    priv->zim_archive = zim_archive;
    priv->suggestion_searcher = zim::SuggestionSearcher(*archive_cpp);

    g_object_ref (zim_archive);

    return suggestion_searcher;
}

/**
 * zim_suggestion_searcher_suggest:
 * @zim_suggestion_searcher: a #ZimSuggestionSearcher
 * @query: a query string
 *
 * Create a Search.
 *
 * Returns: (transfer full): a #ZimSuggestionSearch instance
 */
ZimSuggestionSearch *
zim_suggestion_searcher_suggest (ZimSuggestionSearcher *zim_suggestion_searcher, const char *query)
{
    ZimSuggestionSearcherPrivate *priv = ZIM_SUGGESTION_SEARCHER_GET_PRIVATE (zim_suggestion_searcher);

    zim::SuggestionSearch search_cpp = priv->suggestion_searcher.suggest(query);

    return zim_suggestion_search_new(priv->zim_archive, zim_suggestion_searcher, &search_cpp);
}