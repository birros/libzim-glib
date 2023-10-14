#ifndef ZIM_ITEM_GLIB_H
#define ZIM_ITEM_GLIB_H

#include <glib-object.h>

G_BEGIN_DECLS

#define ZIM_TYPE_ITEM \
    (zim_item_get_type())
#define ZIM_ITEM(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST((obj), ZIM_TYPE_ITEM, ZimItem))
#define ZIM_ITEM_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST((klass), ZIM_TYPE_ITEM, ZimItemClass))
#define ZIM_IS_ITEM(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE((obj), ZIM_TYPE_ITEM))
#define ZIM_IS_ITEM_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE((klass), ZIM_TYPE_ITEM))
#define ZIM_ITEM_GET_CLASS(obj) \
    (G_TYPE_INSTANCE_GET_CLASS((obj), ZIM_TYPE_ITEM, ZimItemClass))

typedef struct _ZimItem ZimItem;
typedef struct _ZimItemClass ZimItemClass;

struct _ZimItem
{
    GObject parent_instance;
};

struct _ZimItemClass
{
    GObjectClass parent_class;
};

GType zim_item_get_type(void);
const char *zim_item_get_title(ZimItem *item);
const char *zim_item_get_path(ZimItem *item);
const char *zim_item_get_mimetype(ZimItem *item);
const char *zim_item_get_data(ZimItem *item, gsize *size);
gsize zim_item_get_size(ZimItem *item);

G_END_DECLS

#endif
