#include <sstream>
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
 * #ZimArchive class is the root class to access to the articles of the zim archive.
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
 * @path: the path to the zim file
 * @error: a #GError object
 *
 * Allocates a new #ZimArchive.
 *
 * Returns: (transfer full): the newly created #ZimArchive instance
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
 * @archive: A #ZimArchive
 *
 * Check if the zim file has a main page.
 *
 * Returns: TRUE if the zim file hash main page, FALSE otherwise
 */
gboolean
zim_archive_has_main_entry(ZimArchive *archive)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE(archive);
    return priv->archive->hasMainEntry();
}

/**
 * zim_archive_get_main_entry:
 * @archive: A #ZimArchive
 * @error: a #GError object
 *
 * Get the index of the main page.
 *
 * Returns: (transfer full): the index of the main page
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
 * @archive: A #ZimArchive
 *
 * Get the uuid of the zim archive.
 *
 * Returns: the uuid of the zim archive
 */
const char *
zim_archive_get_uuid(ZimArchive *archive)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE(archive);

    std::ostringstream s;
    s << priv->archive->getUuid();
    std::string uuid = s.str();
    return g_strdup(uuid.c_str());
}

/**
 * zim_archive_get_entry_by_path:
 * @archive: A #ZimArchive
 * @path: path of an article
 * @error: a #GError object
 *
 * Get the article at the given path.
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
 * @archive: A #ZimArchive
 * @error: a #GError object
 *
 * Get a random entry.
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
 * @archive: A #ZimArchive
 * @size: size of the illustration
 * @error: a #GError object
 *
 * Get the illustration.
 *
 * Returns: (transfer full): a illustration #ZimItem
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
 * @archive: A #ZimArchive
 *
 * Get file size of the archive.
 *
 * Returns: the size
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
 * @archive: A #ZimArchive
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
 * @archive: A #ZimArchive
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
        std::string metadata_cpp = priv->archive->getMetadata(name);

        std::ostringstream s;
        s << metadata_cpp;
        std::string metadata = s.str();

        return g_strdup(metadata.c_str());
    }
    catch (zim::EntryNotFound &err)
    {
        *error = g_error_new_literal(1, 0, err.what());
        return NULL;
    }
}
