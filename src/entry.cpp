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
    ((ZimEntryPrivate *) zim_entry_get_instance_private ((ZimEntry *) (obj)))

typedef struct _ZimEntryPrivate ZimEntryPrivate;
struct _ZimEntryPrivate
{
    ZimArchive *zim_archive;
    zim::Entry entry;
};

G_DEFINE_TYPE_WITH_PRIVATE (ZimEntry, zim_entry, G_TYPE_OBJECT)

static void
zim_entry_finalize (GObject *gobject)
{
    ZimEntryPrivate *priv = ZIM_ENTRY_GET_PRIVATE (gobject);

    g_object_unref (priv->zim_archive);

    G_OBJECT_CLASS (zim_entry_parent_class)->dispose (gobject);
}

static void
zim_entry_class_init (ZimEntryClass *klass)
{
    G_OBJECT_CLASS (klass)->finalize = zim_entry_finalize;
}

static void
zim_entry_init (ZimEntry *object)
{
}

void
zim_entry_set_internal_entry (ZimEntry *entry, ZimArchive *zim_archive, const zim::Entry entry_cpp)
{
    ZimEntryPrivate *priv = ZIM_ENTRY_GET_PRIVATE (entry);

    priv->zim_archive = zim_archive;
    g_object_ref (zim_archive);

    priv->entry = entry_cpp;
}

/**
 * zim_entry_new:
 *
 * Allocates a new #ZimEntry.
 *
 * Returns: (transfer full): the newly created #ZimEntry instance
 */
ZimEntry *
zim_entry_new (void)
{
    ZimEntry *entry = (ZimEntry *) g_object_new (ZIM_TYPE_ENTRY, NULL);

    // ZimEntryPrivate *priv = ZIM_ENTRY_GET_PRIVATE (entry);
    // priv->entry = zim::Entry ();

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
zim_entry_get_title (ZimEntry *entry)
{
    ZimEntryPrivate *priv = ZIM_ENTRY_GET_PRIVATE (entry);
    std::string title = priv->entry.getTitle ();
    return g_strdup (title.c_str ());
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
zim_entry_get_path (ZimEntry *entry)
{
    ZimEntryPrivate *priv = ZIM_ENTRY_GET_PRIVATE (entry);
    std::string path = priv->entry.getPath ();
    return g_strdup (path.c_str ());
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
ZimItem*
zim_entry_get_item (ZimEntry *entry, gboolean follow)
{
    ZimEntryPrivate *priv = ZIM_ENTRY_GET_PRIVATE (entry);

    ZimItem *item = zim_item_new ();

    zim::Item item_cpp = priv->entry.getItem (follow);
    zim_item_set_internal_item (item, priv->zim_archive, item_cpp);

    return item;
}
