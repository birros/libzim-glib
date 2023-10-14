#include <zim/archive.h>
#include <zim/error.h>
#include "archive.h"
#include "entry-private.h"
#include "item-private.h"

/**
 * SECTION: zim-archive
 * @Title: ZimArchive
 * @short_description: A zim archive
 *
 * #ZimArchive represent a zim::Archive.
 */

#define ZIM_ARCHIVE_GET_PRIVATE(obj) \
    ((ZimArchivePrivate *)zim_archive_get_instance_private((ZimArchive *)(obj)))

typedef struct _ZimArchivePrivate ZimArchivePrivate;
struct _ZimArchivePrivate
{
    zim::Archive *archive;
};

G_DEFINE_TYPE_WITH_PRIVATE(ZimArchive, zim_archive, G_TYPE_OBJECT)

static void
zim_archive_finalize(GObject *gobject)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE(gobject);

    delete priv->archive;

    G_OBJECT_CLASS(zim_archive_parent_class)->dispose(gobject);
}

static void
zim_archive_class_init(ZimArchiveClass *klass)
{
    G_OBJECT_CLASS(klass)->finalize = zim_archive_finalize;
}

static void
zim_archive_init(ZimArchive *object)
{
}

zim::Archive *
zim_archive_get_internal_archive(ZimArchive *archive)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE(archive);
    return priv->archive;
}

/**
 * zim_archive_new:
 * @path: the path to the #ZimArchive
 * @error: a #GError object
 *
 * Instantiate a new #ZimArchive.
 *
 * Returns: (transfer full): a #ZimArchive instance
 */
ZimArchive *
zim_archive_new(const char *path, GError **error)
{
    ZimArchive *archive = (ZimArchive *)g_object_new(ZIM_TYPE_ARCHIVE, NULL);
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE(archive);

    try
    {
        priv->archive = new zim::Archive(path);
        return archive;
    }
    catch (const std::exception &err)
    {
        *error = g_error_new_literal(1, 0, err.what());
        return NULL;
    }
}

/**
 * zim_archive_has_main_entry:
 * @archive: a #ZimArchive
 *
 * Check if the #ZimArchive has a main #ZimEntry.
 *
 * Returns: TRUE if the #ZimArchive hash main entry, FALSE otherwise
 */
gboolean
zim_archive_has_main_entry(ZimArchive *archive)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE(archive);
    return priv->archive->hasMainEntry();
}

/**
 * zim_archive_get_main_entry:
 * @archive: a #ZimArchive
 * @error: a #GError object
 *
 * Get the main #ZimEntry.
 *
 * Returns: (transfer full): the main #ZimEntry
 */
ZimEntry *
zim_archive_get_main_entry(ZimArchive *archive, GError **error)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE(archive);

    try
    {
        zim::Entry entry_cpp = priv->archive->getMainEntry();
        ZimEntry *entry = zim_entry_new(archive, entry_cpp);

        return entry;
    }
    catch (zim::EntryNotFound &err)
    {
        *error = g_error_new_literal(1, 0, err.what());
        return NULL;
    }
}

/**
 * zim_archive_get_uuid:
 * @archive: a #ZimArchive
 *
 * Get the uuid of the #ZimArchive.
 *
 * Returns: the uuid of the #ZimArchive
 */
const char *
zim_archive_get_uuid(ZimArchive *archive)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE(archive);

    zim::Uuid uuid_cpp = priv->archive->getUuid();
    std::string uuid = static_cast<std::string>(uuid_cpp);

    return g_strdup(uuid.c_str());
}

/**
 * zim_archive_get_entry_by_path:
 * @archive: a #ZimArchive
 * @path: path of an #ZimEntry
 * @error: a #GError object
 *
 * Get the #ZimEntry at the given path.
 *
 * Returns: (transfer full): the #ZimEntry at the given path
 */
ZimEntry *
zim_archive_get_entry_by_path(ZimArchive *archive, const char *path, GError **error)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE(archive);

    try
    {
        zim::Entry entry_cpp = priv->archive->getEntryByPath(path);
        ZimEntry *entry = zim_entry_new(archive, entry_cpp);

        return entry;
    }
    catch (zim::EntryNotFound &err)
    {
        *error = g_error_new_literal(1, 0, err.what());
        return NULL;
    }
}

/**
 * zim_archive_get_random_entry:
 * @archive: a #ZimArchive
 * @error: a #GError object
 *
 * Get a random #ZimEntry.
 *
 * Returns: (transfer full): a random #ZimEntry
 */
ZimEntry *
zim_archive_get_random_entry(ZimArchive *archive, GError **error)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE(archive);

    try
    {
        zim::Entry entry_cpp = priv->archive->getRandomEntry();
        ZimEntry *entry = zim_entry_new(archive, entry_cpp);

        return entry;
    }
    catch (zim::EntryNotFound &err)
    {
        *error = g_error_new_literal(1, 0, err.what());
        return NULL;
    }
}

/**
 * zim_archive_get_illustration_item:
 * @archive: a #ZimArchive
 * @size: size of the illustration
 * @error: a #GError object
 *
 * Get the illustration.
 *
 * Returns: (transfer full): a illustration as a #ZimItem
 */
ZimItem *
zim_archive_get_illustration_item(ZimArchive *archive, unsigned int size, GError **error)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE(archive);

    try
    {
        zim::Item item_cpp = priv->archive->getIllustrationItem(size);
        ZimItem *item = zim_item_new(archive, item_cpp);

        return item;
    }
    catch (zim::EntryNotFound &err)
    {
        *error = g_error_new_literal(1, 0, err.what());
        return NULL;
    }
}

/**
 * zim_archive_get_filesize:
 * @archive: a #ZimArchive
 *
 * Get file size of the #ZimArchive.
 *
 * Returns: the size of the #ZimArchive
 */
unsigned long
zim_archive_get_filesize(ZimArchive *archive)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE(archive);
    unsigned long size = priv->archive->getFilesize();
    return size;
}

/**
 * zim_archive_get_all_entry_count:
 * @archive: a #ZimArchive
 *
 * Get the global count of entries.
 *
 * Returns: the global count of entries
 */
unsigned int
zim_archive_get_all_entry_count(ZimArchive *archive)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE(archive);
    unsigned int count = priv->archive->getAllEntryCount();
    return count;
}

/**
 * zim_archive_get_article_count:
 * @archive: a #ZimArchive
 *
 * Get the count of articles.
 *
 * Returns: the count of articles
 */
unsigned int
zim_archive_get_article_count(ZimArchive *archive)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE(archive);
    unsigned int count = priv->archive->getArticleCount();
    return count;
}

/**
 * zim_archive_get_metadata:
 * @archive: A #ZimArchive
 * @name: name of metadata
 * @error: a #GError object
 *
 * Get the metadata associated to the name.
 *
 * Returns: the metadata associated to the name
 */
const char *
zim_archive_get_metadata(ZimArchive *archive, const char *name, GError **error)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE(archive);

    try
    {
        std::string metadata = priv->archive->getMetadata(name);
        return g_strdup(metadata.c_str());
    }
    catch (zim::EntryNotFound &err)
    {
        *error = g_error_new_literal(1, 0, err.what());
        return NULL;
    }
}
