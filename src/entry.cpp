#include <memory.h>
#include <zim/entry.h>
#include <zim/item.h>
#include <zim/blob.h>
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

// /**
//  * zim_entry_get_mime_type:
//  * @entry: A #ZimEntry
//  *
//  * Get the mime type of the entry.
//  *
//  * Returns: (transfer full): the mime type of the entry
//  */
// const char *
// zim_entry_get_mime_type (ZimEntry *entry)
// {
//     ZimEntryPrivate *priv = ZIM_ENTRY_GET_PRIVATE (entry);
//     try {
//         std::string mime_type = priv->entry.getMimeType ();
//         return g_strdup (mime_type.c_str ());
//     } catch (std::runtime_error e) {
//         std::wcout << "WARNING : " << e.what () << std::endl;
//         std::string mime_type = "";
//         return g_strdup (mime_type.c_str ());
//     }
// }

// /**
//  * zim_entry_get_namespace:
//  * @entry: A #ZimEntry
//  *
//  * Get the namespace of the entry.
//  *
//  * Returns: the namespace of the entry
//  */
// const char
// zim_entry_get_namespace (ZimEntry *entry)
// {
//     ZimEntryPrivate *priv = ZIM_ENTRY_GET_PRIVATE (entry);
//     return priv->entry.getNamespace ();
// }

// /**
//  * zim_entry_get_data:
//  * @entry: A #ZimEntry
//  * @size: (out) (optional): length of data
//  *
//  * Get the data of the entry.
//  *
//  * Returns: (array length=size) (element-type guint8) (transfer full): data of the entry
//  */
// const char *
// zim_entry_get_data (ZimEntry *entry, gsize *size)
// {
//     ZimEntryPrivate *priv = ZIM_ENTRY_GET_PRIVATE (entry);

//     zim::Blob blob = priv->entry.getData ();

//     *size = blob.size();

//     // copy the data
//     char *content = (char*) malloc (blob.size () * sizeof (char));
//     memcpy (content, blob.data (), blob.size ());

//     return content;
// }

// /**
//  * zim_entry_get_data_size:
//  * @entry: A #ZimEntry
//  *
//  * Get the data size of the entry.
//  *
//  * Returns: the data size of the entry
//  */
// gsize
// zim_entry_get_data_size (ZimEntry *entry)
// {
//     ZimEntryPrivate *priv = ZIM_ENTRY_GET_PRIVATE (entry);
//     return priv->entry.getEntrySize ();
// }

// /**
//  * zim_entry_get_offset:
//  * @entry: A #ZimEntry
//  *
//  * Get the offset of the entry data.
//  *
//  * Returns: the offset of the entry data
//  */
// gsize
// zim_entry_get_offset (ZimEntry *entry)
// {
//     ZimEntryPrivate *priv = ZIM_ENTRY_GET_PRIVATE (entry);
//     return priv->entry.getOffset ();
// }

// /**
//  * zim_entry_good:
//  * @entry: A #ZimEntry
//  *
//  * Check if the entry is good.
//  *
//  * Returns: TRUE if it's good, FALSE otherwise
//  */
// gboolean
// zim_entry_good (ZimEntry *entry)
// {
//     ZimEntryPrivate *priv = ZIM_ENTRY_GET_PRIVATE (entry);
//     return priv->entry.good ();
// }

// /**
//  * zim_entry_is_redirect:
//  * @entry: A #ZimEntry
//  *
//  * Check if the entry is a redirection.
//  *
//  * Returns: TRUE if it's a redirection, FALSE otherwise
//  */
// gboolean
// zim_entry_is_redirect (ZimEntry *entry)
// {
//     ZimEntryPrivate *priv = ZIM_ENTRY_GET_PRIVATE (entry);
//     return priv->entry.isRedirect ();
// }

// /**
//  * zim_entry_get_redirect_entry:
//  * @entry: A #ZimEntry
//  *
//  * Get the entry pointed by this entry if it's a redirection.
//  *
//  * Returns: (transfer full): the #ZimEntry pointed by this entry
//  */
// ZimEntry *
// zim_entry_get_redirect_entry (ZimEntry *entry)
// {
//     ZimEntryPrivate *priv = ZIM_ENTRY_GET_PRIVATE (entry);

//     ZimEntry *redirect = zim_entry_new ();

//     zim::Entry redirect_cpp = priv->entry.getRedirectEntry ();
//     zim_entry_set_internal_entry (redirect, priv->zim_file, redirect_cpp);

//     return redirect;
// }
