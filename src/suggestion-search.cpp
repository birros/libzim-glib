#include <zim/suggestion.h>
#include "archive.h"
#include "suggestion-search.h"
#include "suggestion-searcher.h"
#include "suggestion-result-iterator-private.h"

/**
 * SECTION: zim-suggestion_search
 * @Title: ZimSuggestionSearch
 * @short_description: A zim suggestion_search
 *
 * #ZimSuggestionSearch represent a suggestion_search for a zim file.
 */

#define ZIM_SUGGESTION_SEARCH_GET_PRIVATE(obj) \
    ((ZimSuggestionSearchPrivate *)zim_suggestion_search_get_instance_private((ZimSuggestionSearch *)(obj)))

typedef struct _ZimSuggestionSearchPrivate ZimSuggestionSearchPrivate;
struct _ZimSuggestionSearchPrivate
{
    ZimArchive *zim_archive;
    ZimSuggestionSearcher *zim_suggestion_searcher;
    zim::SuggestionSearch *suggestion_search;
};

G_DEFINE_TYPE_WITH_PRIVATE(ZimSuggestionSearch, zim_suggestion_search, G_TYPE_OBJECT)

static void
zim_suggestion_search_finalize(GObject *gobject)
{
    ZimSuggestionSearchPrivate *priv = ZIM_SUGGESTION_SEARCH_GET_PRIVATE(gobject);

    g_object_unref(priv->zim_archive);
    g_object_unref(priv->zim_suggestion_searcher);

    G_OBJECT_CLASS(zim_suggestion_search_parent_class)->dispose(gobject);
}

static void
zim_suggestion_search_class_init(ZimSuggestionSearchClass *klass)
{
    G_OBJECT_CLASS(klass)->finalize = zim_suggestion_search_finalize;
}

static void
zim_suggestion_search_init(ZimSuggestionSearch *object)
{
}

ZimSuggestionSearch *zim_suggestion_search_new(ZimArchive *archive, ZimSuggestionSearcher *suggestion_searcher, zim::SuggestionSearch *search_cpp)
{
    ZimSuggestionSearch *suggestion_search = (ZimSuggestionSearch *)g_object_new(ZIM_TYPE_SUGGESTION_SEARCH, NULL);
    ZimSuggestionSearchPrivate *priv = ZIM_SUGGESTION_SEARCH_GET_PRIVATE(suggestion_search);

    priv->zim_archive = archive;
    priv->zim_suggestion_searcher = suggestion_searcher;
    priv->suggestion_search = search_cpp;

    g_object_ref(priv->zim_archive);
    g_object_ref(priv->zim_suggestion_searcher);

    return suggestion_search;
}

/**
 * zim_suggestion_search_get_results:
 * @start: start position
 * @max_results: max results
 *
 * Allocates a new #ZimSuggestionSearch.
 *
 * Returns: (transfer full): a #ZimSuggestionResultIterator instance
 */
ZimSuggestionResultIterator *
zim_suggestion_search_get_results(ZimSuggestionSearch *suggestion_search, int start, int max_results)
{
    ZimSuggestionSearchPrivate *priv = ZIM_SUGGESTION_SEARCH_GET_PRIVATE(suggestion_search);

    zim::SuggestionResultSet results = priv->suggestion_search->getResults(start, max_results);

    zim::SuggestionResultSet::iterator begin = results.begin();
    zim::SuggestionResultSet::iterator end = results.end();

    return zim_suggestion_result_iterator_new(priv->zim_archive, suggestion_search, begin, end);
}
