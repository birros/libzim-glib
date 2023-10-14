#include <zim/entry.h>
#include "entry.h"
#include "archive.h"
#include "item-private.h"

/**
 * SECTION: zim-entry
 * @Title: ZimEntry
 * @short_description: A zim entry
 *
 * #ZimEntry represent an entry stored in a zim file.
 */

#define ZIM_ENTRY_GET_PRIVATE(obj) \
    ((ZimEntryPrivate *)zim_entry_get_instance_private((ZimEntry *)(obj)))

typedef struct _ZimEntryPrivate ZimEntryPrivate;
struct _ZimEntryPrivate
{
    ZimArchive *archive;
    zim::Entry entry;
};

G_DEFINE_TYPE_WITH_PRIVATE(ZimEntry, zim_entry, G_TYPE_OBJECT)

static void
zim_entry_finalize(GObject *gobject)
{
    ZimEntryPrivate *priv = ZIM_ENTRY_GET_PRIVATE(gobject);

    g_object_unref(priv->archive);

    G_OBJECT_CLASS(zim_entry_parent_class)->dispose(gobject);
}

static void
zim_entry_class_init(ZimEntryClass *klass)
{
    G_OBJECT_CLASS(klass)->finalize = zim_entry_finalize;
}

static void
zim_entry_init(ZimEntry *object)
{
}

ZimEntry *zim_entry_new(ZimArchive *archive, const zim::Entry entry_cpp)
{
    ZimEntry *entry = (ZimEntry *)g_object_new(ZIM_TYPE_ENTRY, NULL);
    ZimEntryPrivate *priv = ZIM_ENTRY_GET_PRIVATE(entry);

    priv->archive = archive;
    priv->entry = entry_cpp;

    g_object_ref(priv->archive);

    return entry;
}

/**
 * zim_entry_get_title:
 * @entry: A #ZimEntry
 *
 * Get the title of the entry.
 *
 * Returns: (transfer full): the title of the entry
 */
const char *
zim_entry_get_title(ZimEntry *entry)
{
    ZimEntryPrivate *priv = ZIM_ENTRY_GET_PRIVATE(entry);
    std::string title = priv->entry.getTitle();
    return g_strdup(title.c_str());
}

/**
 * zim_entry_get_path:
 * @entry: A #ZimEntry
 *
 * Get the path of the entry.
 *
 * Returns: (transfer full): the path of the entry
 */
const char *
zim_entry_get_path(ZimEntry *entry)
{
    ZimEntryPrivate *priv = ZIM_ENTRY_GET_PRIVATE(entry);
    std::string path = priv->entry.getPath();
    return g_strdup(path.c_str());
}

/**
 * zim_entry_get_item:
 * @entry: A #ZimEntry
 * @follow: A #gboolean
 *
 * Get the index of the main page.
 *
 * Returns: (transfer full): the index of the main page
 */
ZimItem *
zim_entry_get_item(ZimEntry *entry, gboolean follow)
{
    ZimEntryPrivate *priv = ZIM_ENTRY_GET_PRIVATE(entry);

    zim::Item item_cpp = priv->entry.getItem(follow);
    ZimItem *item = zim_item_new(priv->archive, item_cpp);

    return item;
}
