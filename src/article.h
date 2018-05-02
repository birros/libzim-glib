#ifndef ZIM_ARTICLE_GLIB_H
#define ZIM_ARTICLE_GLIB_H

#include <glib-object.h>

G_BEGIN_DECLS

#define ZIM_TYPE_ARTICLE \
    (zim_article_get_type())
#define ZIM_ARTICLE(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST((obj), ZIM_TYPE_ARTICLE, ZimArticle))
#define ZIM_ARTICLE_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST((klass), ZIM_TYPE_ARTICLE, ZimArticleClass))
#define ZIM_IS_ARTICLE(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE((obj), ZIM_TYPE_ARTICLE))
#define ZIM_IS_ARTICLE_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE((klass), ZIM_TYPE_ARTICLE))
#define ZIM_ARTICLE_GET_CLASS(obj) \
    (G_TYPE_INSTANCE_GET_CLASS((obj), ZIM_TYPE_ARTICLE, ZimArticleClass))

typedef struct _ZimArticle      ZimArticle;
typedef struct _ZimArticleClass ZimArticleClass;

struct _ZimArticle
{
    GObject parent_instance;
};

struct _ZimArticleClass
{
    GObjectClass parent_class;
};

GType        zim_article_get_type (void);
ZimArticle * zim_article_new (void);
const char * zim_article_get_title (ZimArticle *article);
const char * zim_article_get_url (ZimArticle *article);
const char * zim_article_get_mime_type (ZimArticle *article);
const char * zim_article_get_data (ZimArticle *article, gsize *size);
gboolean     zim_article_good (ZimArticle *article);
gboolean     zim_article_is_redirect (ZimArticle *article);
ZimArticle * zim_article_get_redirect_article (ZimArticle *article);

G_END_DECLS

#endif
