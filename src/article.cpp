#include <memory.h>
#include <zim/article.h>
#include <zim/blob.h>
#include "article.h"
#include "file.h"

/**
 * SECTION: zim-article
 * @Title: ZimArticle
 * @short_description: A zim article
 *
 * #ZimArticle represent an article stored in a zim file.
 */

#define ZIM_ARTICLE_GET_PRIVATE(obj) \
    ((ZimArticlePrivate *) zim_article_get_instance_private ((ZimArticle *) (obj)))

typedef struct _ZimArticlePrivate ZimArticlePrivate;
struct _ZimArticlePrivate
{
    ZimFile *zim_file;
    zim::Article article;
};

G_DEFINE_TYPE_WITH_PRIVATE (ZimArticle, zim_article, G_TYPE_OBJECT)

static void
zim_article_finalize (GObject *gobject)
{
    ZimArticlePrivate *priv = ZIM_ARTICLE_GET_PRIVATE (gobject);

    g_object_unref (priv->zim_file);

    G_OBJECT_CLASS (zim_article_parent_class)->dispose (gobject);
}

static void
zim_article_class_init (ZimArticleClass *klass)
{
    G_OBJECT_CLASS (klass)->finalize = zim_article_finalize;
}

static void
zim_article_init (ZimArticle *object)
{
}

void
zim_article_set_internal_article (ZimArticle *article, ZimFile *zim_file, const zim::Article article_cpp)
{
    ZimArticlePrivate *priv = ZIM_ARTICLE_GET_PRIVATE (article);

    priv->zim_file = zim_file;
    g_object_ref (zim_file);

    priv->article = article_cpp;
}

/**
 * zim_article_new:
 *
 * Allocates a new #ZimArticle.
 *
 * Returns: (transfer full): the newly created #ZimArticle instance
 */
ZimArticle *
zim_article_new (void)
{
    ZimArticle *article = (ZimArticle *) g_object_new (ZIM_TYPE_ARTICLE, NULL);

    ZimArticlePrivate *priv = ZIM_ARTICLE_GET_PRIVATE (article);
    priv->article = zim::Article ();

    return article;
}

/**
 * zim_article_get_title:
 * @article: A #ZimArticle
 *
 * Get the title of the article.
 *
 * Returns: (transfer full): the title of the article
 */
const char *
zim_article_get_title (ZimArticle *article)
{
    ZimArticlePrivate *priv = ZIM_ARTICLE_GET_PRIVATE (article);
    std::string title = priv->article.getTitle ();
    return g_strdup (title.c_str ());
}

/**
 * zim_article_get_url:
 * @article: A #ZimArticle
 *
 * Get the url of the article.
 *
 * Returns: (transfer full): the url of the article
 */
const char *
zim_article_get_url (ZimArticle *article)
{
    ZimArticlePrivate *priv = ZIM_ARTICLE_GET_PRIVATE (article);
    std::string url = priv->article.getUrl ();
    return g_strdup (url.c_str ());
}

/**
 * zim_article_get_mime_type:
 * @article: A #ZimArticle
 *
 * Get the mime type of the article.
 *
 * Returns: (transfer full): the mime type of the article
 */
const char *
zim_article_get_mime_type (ZimArticle *article)
{
    ZimArticlePrivate *priv = ZIM_ARTICLE_GET_PRIVATE (article);
    try {
        std::string mime_type = priv->article.getMimeType ();
        return g_strdup (mime_type.c_str ());
    } catch (std::runtime_error e) {
        std::wcout << "WARNING : " << e.what () << std::endl;
        std::string mime_type = "";
        return g_strdup (mime_type.c_str ());
    }
}

/**
 * zim_article_get_namespace:
 * @article: A #ZimArticle
 *
 * Get the namespace of the article.
 *
 * Returns: the namespace of the article
 */
const char
zim_article_get_namespace (ZimArticle *article)
{
    ZimArticlePrivate *priv = ZIM_ARTICLE_GET_PRIVATE (article);
    return priv->article.getNamespace ();
}

/**
 * zim_article_get_data:
 * @article: A #ZimArticle
 * @size: (out) (optional): length of data
 *
 * Get the data of the article.
 *
 * Returns: (array length=size) (element-type guint8) (transfer full): data of the article
 */
const char *
zim_article_get_data (ZimArticle *article, gsize *size)
{
    ZimArticlePrivate *priv = ZIM_ARTICLE_GET_PRIVATE (article);

    zim::Blob blob = priv->article.getData ();

    *size = blob.size();

    // copy the data
    char *content = (char*) malloc (blob.size () * sizeof (char));
    memcpy (content, blob.data (), blob.size ());

    return content;
}

/**
 * zim_article_get_data_size:
 * @article: A #ZimArticle
 *
 * Get the data size of the article.
 *
 * Returns: the data size of the article
 */
gsize
zim_article_get_data_size (ZimArticle *article)
{
    ZimArticlePrivate *priv = ZIM_ARTICLE_GET_PRIVATE (article);
    return priv->article.getArticleSize ();
}

/**
 * zim_article_get_offset:
 * @article: A #ZimArticle
 *
 * Get the offset of the article data.
 *
 * Returns: the offset of the article data
 */
gsize
zim_article_get_offset (ZimArticle *article)
{
    ZimArticlePrivate *priv = ZIM_ARTICLE_GET_PRIVATE (article);
    return priv->article.getOffset ();
}

/**
 * zim_article_good:
 * @article: A #ZimArticle
 *
 * Check if the article is good.
 *
 * Returns: TRUE if it's good, FALSE otherwise
 */
gboolean
zim_article_good (ZimArticle *article)
{
    ZimArticlePrivate *priv = ZIM_ARTICLE_GET_PRIVATE (article);
    return priv->article.good ();
}

/**
 * zim_article_is_redirect:
 * @article: A #ZimArticle
 *
 * Check if the article is a redirection.
 *
 * Returns: TRUE if it's a redirection, FALSE otherwise
 */
gboolean
zim_article_is_redirect (ZimArticle *article)
{
    ZimArticlePrivate *priv = ZIM_ARTICLE_GET_PRIVATE (article);
    return priv->article.isRedirect ();
}

/**
 * zim_article_get_redirect_article:
 * @article: A #ZimArticle
 *
 * Get the article pointed by this article if it's a redirection.
 *
 * Returns: (transfer full): the #ZimArticle pointed by this article
 */
ZimArticle *
zim_article_get_redirect_article (ZimArticle *article)
{
    ZimArticlePrivate *priv = ZIM_ARTICLE_GET_PRIVATE (article);

    ZimArticle *redirect = zim_article_new ();

    zim::Article redirect_cpp = priv->article.getRedirectArticle ();
    zim_article_set_internal_article (redirect, priv->zim_file, redirect_cpp);

    return redirect;
}
