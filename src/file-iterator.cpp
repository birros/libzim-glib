#include <zim/file.h>
#include <zim/fileiterator.h>
#include "file-iterator.h"
#include "file.h"
#include "file-private.h"
#include "article-private.h"

/**
 * SECTION: zim-file-iterator
 * @Title: ZimFileIterator
 * @short_description: A zim file_iterator
 *
 * #ZimFileIterator represent a result of a call to findByTitle for example.
 */

#define ZIM_FILE_ITERATOR_GET_PRIVATE(obj) \
    ((ZimFileIteratorPrivate *) zim_file_iterator_get_instance_private ((ZimFileIterator *) (obj)))

typedef struct _ZimFileIteratorPrivate ZimFileIteratorPrivate;
struct _ZimFileIteratorPrivate
{
    ZimFile *file;
    zim::File::const_iterator current;
};

G_DEFINE_TYPE_WITH_PRIVATE (ZimFileIterator, zim_file_iterator, G_TYPE_OBJECT)

static void
zim_file_iterator_finalize (GObject *gobject)
{
    ZimFileIteratorPrivate *priv = ZIM_FILE_ITERATOR_GET_PRIVATE (gobject);

    g_object_unref (priv->file);

    G_OBJECT_CLASS (zim_file_iterator_parent_class)->dispose (gobject);
}

static void
zim_file_iterator_class_init (ZimFileIteratorClass *klass)
{
    G_OBJECT_CLASS (klass)->finalize = zim_file_iterator_finalize;
}

static void
zim_file_iterator_init (ZimFileIterator *object)
{
}

void
zim_file_iterator_set_internal_file_iterator (ZimFileIterator *file_iterator, ZimFile *file, zim::File::const_iterator file_iterator_cpp)
{
    ZimFileIteratorPrivate *priv = ZIM_FILE_ITERATOR_GET_PRIVATE (file_iterator);
    priv->file = file;
    g_object_ref (priv->file);

    priv->current = file_iterator_cpp;
}

/**
 * zim_file_iterator_new:
 *
 * Allocates a new #ZimFileIterator.
 *
 * Returns: (transfer full): the newly created #ZimFileIterator instance
 */
ZimFileIterator *
zim_file_iterator_new ()
{
    ZimFileIterator *file_iterator = (ZimFileIterator *) g_object_new (ZIM_TYPE_FILE_ITERATOR, NULL);

    return file_iterator;
}

/**
 * zim_file_iterator_get_article:
 * @file_iterator: A #ZimFileIterator
 *
 * Get #ZimArticle of the iterator.
 *
 * Returns: (transfer full): the newly created #ZimArticle instance
 */
ZimArticle *
zim_file_iterator_get_article (ZimFileIterator *file_iterator)
{
    ZimFileIteratorPrivate *priv = ZIM_FILE_ITERATOR_GET_PRIVATE (file_iterator);

    ZimArticle *article = zim_article_new ();
    zim::Article article_cpp = *priv->current;
    zim_article_set_internal_article (article, priv->file, article_cpp);

    return article;
}

/**
 * zim_file_iterator_next:
 * @file_iterator: A #ZimFileIterator
 *
 * Go to the next article.
 *
 * Returns: TRUE if the next article exist, FALSE otherwise
 */
gboolean
zim_file_iterator_next (ZimFileIterator *file_iterator)
{
    ZimFileIteratorPrivate *priv = ZIM_FILE_ITERATOR_GET_PRIVATE (file_iterator);

    priv->current++;
    zim::Article article_cpp = *priv->current;

    if (article_cpp.good()) {
        return TRUE;
    } else {
        return FALSE;
    }
}
