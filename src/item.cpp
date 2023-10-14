#include <zim/item.h>
#include "item.h"
#include "archive.h"

/**
 * SECTION: zim-item
 * @Title: ZimItem
 * @short_description: A zim item
 *
 * #ZimItem represent an item stored in a zim file.
 */

#define ZIM_ITEM_GET_PRIVATE(obj) \
    ((ZimItemPrivate *)zim_item_get_instance_private((ZimItem *)(obj)))

typedef struct _ZimItemPrivate ZimItemPrivate;
struct _ZimItemPrivate
{
    ZimArchive *archive;
    zim::Item item;
};

G_DEFINE_TYPE_WITH_PRIVATE(ZimItem, zim_item, G_TYPE_OBJECT)

static void
zim_item_finalize(GObject *gobject)
{
    ZimItemPrivate *priv = ZIM_ITEM_GET_PRIVATE(gobject);

    g_object_unref(priv->archive);

    G_OBJECT_CLASS(zim_item_parent_class)->dispose(gobject);
}

static void
zim_item_class_init(ZimItemClass *klass)
{
    G_OBJECT_CLASS(klass)->finalize = zim_item_finalize;
}

static void
zim_item_init(ZimItem *object)
{
}

ZimItem *zim_item_new(ZimArchive *archive, const zim::Item item_cpp)
{
    ZimItem *item = (ZimItem *)g_object_new(ZIM_TYPE_ITEM, NULL);
    ZimItemPrivate *priv = ZIM_ITEM_GET_PRIVATE(item);

    priv->archive = archive;
    priv->item = item_cpp;

    g_object_ref(priv->archive);

    return item;
}

/**
 * zim_item_get_title:
 * @item: A #ZimItem
 *
 * Get the title of the item.
 *
 * Returns: (transfer full): the title of the item
 */
const char *
zim_item_get_title(ZimItem *item)
{
    ZimItemPrivate *priv = ZIM_ITEM_GET_PRIVATE(item);
    std::string title = priv->item.getTitle();
    return g_strdup(title.c_str());
}

/**
 * zim_item_get_path:
 * @item: A #ZimItem
 *
 * Get the path of the item.
 *
 * Returns: (transfer full): the path of the item
 */
const char *
zim_item_get_path(ZimItem *item)
{
    ZimItemPrivate *priv = ZIM_ITEM_GET_PRIVATE(item);
    std::string path = priv->item.getPath();
    return g_strdup(path.c_str());
}

/**
 * zim_item_get_mimetype:
 * @item: A #ZimItem
 *
 * Get the mime type of the item.
 *
 * Returns: (transfer full): the mime type of the item
 */
const char *
zim_item_get_mimetype(ZimItem *item)
{
    ZimItemPrivate *priv = ZIM_ITEM_GET_PRIVATE(item);

    std::string mime_type = priv->item.getMimetype();

    return g_strdup(mime_type.c_str());
}

/**
 * zim_item_get_data:
 * @item: A #ZimItem
 * @size: (out) (optional): length of data
 *
 * Get the data of the item.
 *
 * Returns: (array length=size) (element-type guint8) (transfer full): data of the item
 */
const char *
zim_item_get_data(ZimItem *item, gsize *size)
{
    ZimItemPrivate *priv = ZIM_ITEM_GET_PRIVATE(item);

    zim::Blob blob = priv->item.getData();

    *size = blob.size();

    // copy the data
    char *content = (char *)malloc(blob.size() * sizeof(char));
    memcpy(content, blob.data(), blob.size());

    return content;
}

/**
 * zim_item_get_size:
 * @item: A #ZimItem
 *
 * Get the data size of the item.
 *
 * Returns: the data size of the item
 */
gsize zim_item_get_size(ZimItem *item)
{
    ZimItemPrivate *priv = ZIM_ITEM_GET_PRIVATE(item);
    return priv->item.getSize();
}
