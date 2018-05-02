#include <zim/search.h>
#include <zim/search_iterator.h>
#include "search.h"
#include "file.h"
#include "file-private.h"
#include "search-iterator-private.h"

/**
 * SECTION: zim-search
 * @Title: ZimSearch
 * @short_description: A zim search
 *
 * #ZimSearch represent an search object to perform full text search.
 */

#define ZIM_SEARCH_GET_PRIVATE(obj) \
    ((ZimSearchPrivate *) zim_search_get_instance_private ((ZimSearch *) (obj)))

typedef struct _ZimSearchPrivate ZimSearchPrivate;
struct _ZimSearchPrivate
{
    zim::File *file;
    zim::Search *search;
};

G_DEFINE_TYPE_WITH_PRIVATE (ZimSearch, zim_search, G_TYPE_OBJECT)

static void
zim_search_finalize (GObject *gobject)
{
    ZimSearchPrivate *priv = ZIM_SEARCH_GET_PRIVATE (gobject);

    delete priv->file;
    delete priv->search;

    G_OBJECT_CLASS (zim_search_parent_class)->dispose (gobject);
}

static void
zim_search_class_init (ZimSearchClass *klass)
{
    G_OBJECT_CLASS (klass)->finalize = zim_search_finalize;
}

static void
zim_search_init (ZimSearch *object)
{
}

/**
 * zim_search_new:
 * @zim_file: A #ZimFile
 *
 * Allocates a new #ZimSearch.
 *
 * Returns: (transfer full): the newly created #ZimSearch instance
 */
ZimSearch *
zim_search_new (ZimFile *zim_file)
{
    ZimSearch *search = (ZimSearch *) g_object_new (ZIM_TYPE_SEARCH, NULL);

    ZimSearchPrivate *priv = ZIM_SEARCH_GET_PRIVATE (search);

    zim::File zim_file_cpp = zim_file_get_internal_zim_file (zim_file);
    std::string filepath = zim_file_cpp.getFilename();

    priv->file = new zim::File (filepath);
    priv->search = new zim::Search (priv->file);

    return search;
}

/**
 * zim_search_set_query:
 * @search: A #ZimSearch
 * @query: A string query
 *
 * Set the string query used to perform search.
 */
void
zim_search_set_query (ZimSearch *search, const char *query)
{
    ZimSearchPrivate *priv = ZIM_SEARCH_GET_PRIVATE (search);
    priv->search->set_query(query);
}

/**
 * zim_search_set_range:
 * @search: A #ZimSearch
 * @start: A number represent start of range
 * @end: A number represent end of range
 *
 * Set the range of the search.
 */
void
zim_search_set_range (ZimSearch *search, unsigned int start, unsigned int end)
{
    ZimSearchPrivate *priv = ZIM_SEARCH_GET_PRIVATE (search);
    priv->search->set_range(start, end);
}

/**
 * zim_search_set_suggestion_mode:
 * @search: A #ZimSearch
 * @boolean: A gboolean
 *
 * Set if the search needs to be made in suggestion mode.
 */
void
zim_search_set_suggestion_mode (ZimSearch *search, gboolean boolean)
{
    ZimSearchPrivate *priv = ZIM_SEARCH_GET_PRIVATE (search);
    priv->search->set_suggestion_mode(boolean);
}

/**
 * zim_search_get_matches_estimated:
 * @search: A #ZimSearch
 *
 * Get the estimated number of matches.
 */
unsigned int
zim_search_get_matches_estimated (ZimSearch *search)
{
    ZimSearchPrivate *priv = ZIM_SEARCH_GET_PRIVATE (search);
    return priv->search->get_matches_estimated();
}

/**
 * zim_search_begin:
 * @search: A #ZimSearch
 *
 * Get the first result of the search.
 *
 * Returns: (transfer full): A #ZimSearchIterator
 */
ZimSearchIterator *
zim_search_begin (ZimSearch *search)
{
    ZimSearchPrivate *priv = ZIM_SEARCH_GET_PRIVATE (search);

    ZimSearchIterator *search_iterator = zim_search_iterator_new();

    zim::search_iterator begin = priv->search->begin();
    zim::search_iterator end = priv->search->end();
    zim_search_iterator_set_internals (search_iterator, begin, end);

    return search_iterator;
}
