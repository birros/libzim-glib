#include <sstream>
#include <iostream>
#include <zim/archive.h>
#include <zim/error.h>
#include "archive.h"
#include "entry.h"
#include "entry-private.h"
#include "item.h"
#include "item-private.h"
// #include <zim/file.h>
// #include <zim/fileiterator.h>
// #include <zim/article.h>
// #include "file.h"
// #include "fileheader.h"
// #include "fileheader-private.h"
// #include "article.h"
// #include "article-private.h"
// #include "file-iterator.h"
// #include "file-iterator-private.h"

/**
 * SECTION: zim-file
 * @Title: ZimArchive
 * @short_description: A zim file
 *
 * #ZimArchive class is the root class to access to the articles of the zim file.
 */

#define ZIM_ARCHIVE_GET_PRIVATE(obj) \
    ((ZimArchivePrivate *) zim_archive_get_instance_private ((ZimArchive *) (obj)))

typedef struct _ZimArchivePrivate ZimArchivePrivate;
struct _ZimArchivePrivate
{
    zim::Archive *file;
};

G_DEFINE_TYPE_WITH_PRIVATE (ZimArchive, zim_archive, G_TYPE_OBJECT)

static void
zim_archive_finalize (GObject *gobject)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE (gobject);

    delete priv->file;

    G_OBJECT_CLASS (zim_archive_parent_class)->dispose (gobject);
}

static void
zim_archive_class_init (ZimArchiveClass *klass)
{
    G_OBJECT_CLASS (klass)->finalize = zim_archive_finalize;
}

static void
zim_archive_init (ZimArchive *object)
{
}

zim::Archive *
zim_archive_get_internal_zim_archive (ZimArchive *zim_archive)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE (zim_archive);
    return priv->file;
}

/**
 * zim_archive_new:
 * @zimpath: the path to the zim file
 * @error: a #GError object
 *
 * Allocates a new #ZimArchive.
 *
 * Returns: (transfer full): the newly created #ZimArchive instance
 */
ZimArchive *
zim_archive_new (const char *zimpath, GError **error)
{
    ZimArchive *file;
    file = (ZimArchive*) g_object_new (ZIM_TYPE_ARCHIVE, NULL);

    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE (file);
    try
    {
        priv->file = new zim::Archive (zimpath);
    }
    catch (const std::exception &err)
    {
        *error = g_error_new_literal (1, 0, err.what ());
    }

    return file;
}

// /**
//  * zim_archive_get_namespace_begin_offset:
//  * @file: A #ZimArchive
//  * @namesp: the namespace
//  *
//  * Get the offset of the beginning of the namespace.
//  *
//  * Returns: the offset of the namespace
//  */
// unsigned int
// zim_archive_get_namespace_begin_offset (ZimArchive *file, char namesp)
// {
//     ZimArchivePrivate *priv = ZIM_FILE_GET_PRIVATE (file);
//     unsigned int index = priv->file->getNamespaceBeginOffset (namesp);
//     return index;
// }

// /**
//  * zim_archive_get_namespace_count:
//  * @file: A #ZimArchive
//  * @namesp: the namespace
//  *
//  * Get the count of entries in the namespace.
//  *
//  * Returns: the count of entries
//  */
// unsigned int
// zim_archive_get_namespace_count (ZimArchive *file, char namesp)
// {
//     ZimArchivePrivate *priv = ZIM_FILE_GET_PRIVATE (file);
//     unsigned int count = priv->file->getNamespaceCount (namesp);
//     return count;
// }

// /**
//  * zim_archive_get_fileheader:
//  * @file: A #ZimArchive
//  *
//  * Get the #ZimArchiveheader object of the zim file.
//  *
//  * Returns: (transfer full): the #ZimArchiveheader
//  */
// ZimArchiveheader *
// zim_archive_get_fileheader (ZimArchive *file)
// {
//     ZimArchivePrivate *priv = ZIM_FILE_GET_PRIVATE (file);

//     ZimArchiveheader* fileheader = zim_archiveheader_new ();
//     zim_archiveheader_set_internal_fileheader (fileheader, file, priv->file->getFileheader ());

//     return fileheader;
// }

/**
 * zim_archive_has_main_entry:
 * @archive: A #ZimArchive
 *
 * Check if the zim file has a main page.
 *
 * Returns: TRUE if the zim file hash main page, FALSE otherwise
 */
gboolean
zim_archive_has_main_entry (ZimArchive* archive)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE (archive);
    return priv->file->hasMainEntry ();
}

/**
 * zim_archive_get_main_entry:
 * @archive: A #ZimArchive
 *
 * Get the index of the main page.
 *
 * Returns: (transfer full): the index of the main page
 */
ZimEntry*
zim_archive_get_main_entry (ZimArchive* archive)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE (archive);

    try {
        zim::Entry entry_cpp = priv->file->getMainEntry ();

        ZimEntry *entry = zim_entry_new ();
        zim_entry_set_internal_entry (entry, archive, entry_cpp);

        return entry;
    } catch (zim::EntryNotFound &e) {
        std::wcout << "WARNING: zim_archive_get_main_entry(): " << e.what () << std::endl;

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
zim_archive_get_uuid (ZimArchive* archive)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE (archive);

    std::ostringstream s;
    s << priv->file->getUuid();
    std::string uuid = s.str();
    return g_strdup (uuid.c_str ());
}

/**
 * zim_archive_get_entry_by_path:
 * @archive: A #ZimArchive
 * @path: path of an article
 *
 * Get the article at the given path.
 *
 * Returns: (transfer full): the #ZimEntry at the given path
 */
ZimEntry *
zim_archive_get_entry_by_path (ZimArchive *archive, const char * path)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE (archive);

    try {
        zim::Entry entry_cpp = priv->file->getEntryByPath (path);

        ZimEntry *entry = zim_entry_new ();
        zim_entry_set_internal_entry (entry, archive, entry_cpp);

        return entry;
    } catch (zim::EntryNotFound &e) {
        std::wcout << "WARNING: zim_archive_get_entry_by_path(" << path << "): " << e.what () << std::endl;

        return NULL;
    }
}

/**
 * zim_archive_get_random_entry:
 * @archive: A #ZimArchive
 *
 * Get a random entry.
 *
 * Returns: (transfer full): a random #ZimEntry
 */
ZimEntry *
zim_archive_get_random_entry (ZimArchive *archive)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE (archive);

    try {
        zim::Entry entry_cpp = priv->file->getRandomEntry ();

        ZimEntry *entry = zim_entry_new ();
        zim_entry_set_internal_entry (entry, archive, entry_cpp);

        return entry;
    } catch (zim::EntryNotFound &e) {
        std::wcout << "WARNING: zim_archive_get_random_entry(): " << e.what () << std::endl;

        return NULL;
    }
}

/**
 * zim_archive_get_illustration_item:
 * @archive: A #ZimArchive
 * @size: size of the illustration
 *
 * Get the illustration.
 *
 * Returns: (transfer full): a illustration #ZimItem
 */
ZimItem *
zim_archive_get_illustration_item (ZimArchive *archive, unsigned int size)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE (archive);

    try {
        zim::Item item_cpp = priv->file->getIllustrationItem (size);

        ZimItem *item = zim_item_new ();
        zim_item_set_internal_item (item, archive, item_cpp);

        return item;
    } catch (zim::EntryNotFound &e) {
        std::wcout << "WARNING: zim_archive_get_illustration_item(" << size << "): " << e.what () << std::endl;

        return NULL;
    }
}

// /**
//  * zim_archive_get_article_by_index:
//  * @file: A #ZimArchive
//  * @index: index of an article
//  *
//  * Get the article at the given index.
//  *
//  * Returns: (transfer full): the #ZimArticle at the given index
//  */
// ZimArticle *
// zim_archive_get_article_by_index (ZimArchive *file, unsigned int index)
// {
//     ZimArchivePrivate *priv = ZIM_FILE_GET_PRIVATE (file);

//     ZimArticle *article = zim_article_new ();
//     zim::Article article_cpp = priv->file->getArticle (index);
//     zim_article_set_internal_article (article, file, article_cpp);

//     return article;
// }

// /**
//  * zim_archive_get_article_by_namespace:
//  * @file: A #ZimArchive
//  * @namesp: the namespace
//  * @path: the path of the article inside the namespace
//  *
//  * Get an article knowing its path inside a namespace.
//  *
//  * Returns: (transfer full): the #ZimArticle found
//  */
// ZimArticle *
// zim_archive_get_article_by_namespace (ZimArchive *file, const char namesp, const char *path)
// {
//     ZimArchivePrivate *priv = ZIM_FILE_GET_PRIVATE (file);

//     ZimArticle *article = zim_article_new ();
//     zim::Article article_cpp = priv->file->getArticle (namesp, path);
//     zim_article_set_internal_article (article, file, article_cpp);

//     return article;
// }

// /**
//  * zim_archive_find_by_title:
//  * @file: A #ZimArchive
//  * @namesp: the namespace
//  * @title: title
//  *
//  * Start search of articles corresponding to a title.
//  *
//  * Returns: (transfer full): the #ZimArchiveIterator
//  */
// ZimArchiveIterator *
// zim_archive_find_by_title (ZimArchive *file, const char namesp, const char *title)
// {
//     ZimArchivePrivate *priv = ZIM_FILE_GET_PRIVATE (file);

//     ZimArchiveIterator *file_iterator = zim_archive_iterator_new ();
//     zim::Archive::const_iterator file_iterator_cpp = priv->file->findByTitle (namesp, title);
//     zim_archive_iterator_set_internal_file_iterator (file_iterator, file, file_iterator_cpp);

//     return file_iterator;
// }

/**
 * zim_archive_get_filesize:
 * @archive: A #ZimArchive
 *
 * Get file size of the archive.
 *
 * Returns: the size
 */
unsigned long
zim_archive_get_filesize (ZimArchive *archive)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE (archive);
    unsigned long size = priv->file->getFilesize ();
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
zim_archive_get_all_entry_count (ZimArchive *archive)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE (archive);
    unsigned int count = priv->file->getAllEntryCount ();
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
zim_archive_get_article_count (ZimArchive *archive)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE (archive);
    unsigned int count = priv->file->getArticleCount ();
    return count;
}

/**
 * zim_archive_get_metadata:
 * @archive: A #ZimArchive
 * @name: name of metadata
 *
 * Get the metadata associated to the name.
 *
 * Returns: the metadata associated to the name
 */
const char *
zim_archive_get_metadata (ZimArchive* archive, const char * name)
{
    ZimArchivePrivate *priv = ZIM_ARCHIVE_GET_PRIVATE (archive);

    try {
        std::string metadata_cpp = priv->file->getMetadata (name);

        std::ostringstream s;
        s << metadata_cpp;
        std::string metadata = s.str();

        return g_strdup (metadata.c_str ());
    } catch (zim::EntryNotFound &e) {
        std::wcout << "WARNING: zim_archive_get_metadata(" << name << "): " << e.what () << std::endl;

        return NULL;
    }
}
