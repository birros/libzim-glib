#include <zim/search_iterator.h>
#include "search-iterator.h"
#include "file.h"
#include "file-private.h"

/**
 * SECTION: zim-search-iterator
 * @Title: ZimSearchIterator
 * @short_description: A zim search_iterator
 *
 * #ZimSearchIterator represent a result of a #ZimSearch class.
 */

#define ZIM_SEARCH_ITERATOR_GET_PRIVATE(obj) \
    ((ZimSearchIteratorPrivate *) zim_search_iterator_get_instance_private ((ZimSearchIterator *) (obj)))

typedef struct _ZimSearchIteratorPrivate ZimSearchIteratorPrivate;
struct _ZimSearchIteratorPrivate
{
    zim::search_iterator begin;
    zim::search_iterator current;
    zim::search_iterator end;
};

G_DEFINE_TYPE_WITH_PRIVATE (ZimSearchIterator, zim_search_iterator, G_TYPE_OBJECT)

static void
zim_search_iterator_finalize (GObject *gobject)
{
    G_OBJECT_CLASS (zim_search_iterator_parent_class)->dispose (gobject);
}

static void
zim_search_iterator_class_init (ZimSearchIteratorClass *klass)
{
    G_OBJECT_CLASS (klass)->finalize = zim_search_iterator_finalize;
}

static void
zim_search_iterator_init (ZimSearchIterator *object)
{
}

void
zim_search_iterator_set_internals (ZimSearchIterator *search_iterator, zim::search_iterator begin, zim::search_iterator end)
{
    ZimSearchIteratorPrivate *priv = ZIM_SEARCH_ITERATOR_GET_PRIVATE (search_iterator);
    priv->begin = begin;
    priv->current = begin;
    priv->end = end;
}

/**
 * zim_search_iterator_new:
 *
 * Allocates a new #ZimSearchIterator.
 *
 * Returns: (transfer full): the newly created #ZimSearchIterator instance
 */
ZimSearchIterator *
zim_search_iterator_new ()
{
    ZimSearchIterator *search_iterator = (ZimSearchIterator *) g_object_new (ZIM_TYPE_SEARCH_ITERATOR, NULL);

    ZimSearchIteratorPrivate *priv = ZIM_SEARCH_ITERATOR_GET_PRIVATE (search_iterator);

    priv->current = zim::search_iterator ();
    priv->end = priv->current++;

    return search_iterator;
}

/**
 * zim_search_iterator_get_title:
 * @search_iterator: A #ZimSearchIterator
 *
 * Get the title of the article.
 *
 * Returns: (transfer full): the title of the article
 */
const char *
zim_search_iterator_get_title (ZimSearchIterator *search_iterator)
{
    ZimSearchIteratorPrivate *priv = ZIM_SEARCH_ITERATOR_GET_PRIVATE (search_iterator);
    std::string title = priv->current.get_title ();
    return g_strdup (title.c_str ());
}

/**
 * zim_search_iterator_get_url:
 * @search_iterator: A #ZimSearchIterator
 *
 * Get the url of the article.
 *
 * Returns: (transfer full): the url of the article
 */
const char *
zim_search_iterator_get_url (ZimSearchIterator *search_iterator)
{
    ZimSearchIteratorPrivate *priv = ZIM_SEARCH_ITERATOR_GET_PRIVATE (search_iterator);
    std::string url = priv->current.get_url ();
    return g_strdup (url.c_str ());
}

/**
 * zim_search_iterator_next:
 * @search_iterator: A #ZimSearchIterator
 *
 * Go to the next result of a search.
 *
 * Returns: TRUE if the next result exist, FALSE otherwise
 */
gboolean
zim_search_iterator_next (ZimSearchIterator *search_iterator)
{
    ZimSearchIteratorPrivate *priv = ZIM_SEARCH_ITERATOR_GET_PRIVATE (search_iterator);

    priv->current++;
    if (priv->current == priv->end) {
      return FALSE;
    } else {
      return TRUE;
    }
}
