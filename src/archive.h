#ifndef ZIM_ARCHIVE_GLIB_H
#define ZIM_ARCHIVE_GLIB_H

#include <glib-object.h>
#include "entry.h"
// #include "archiveheader.h"
// #include "article.h"
// #include "archive-iterator.h"
typedef struct _ZimArchiveIterator      ZimArchiveIterator;

G_BEGIN_DECLS

#define ZIM_TYPE_ARCHIVE \
    (zim_archive_get_type())
#define ZIM_ARCHIVE(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST((obj), ZIM_TYPE_ARCHIVE, ZimArchive))
#define ZIM_ARCHIVE_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST((klass), ZIM_TYPE_ARCHIVE, ZimArchiveClass))
#define ZIM_IS_ARCHIVE(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE((obj), ZIM_TYPE_ARCHIVE))
#define ZIM_IS_ARCHIVE_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE((klass), ZIM_TYPE_ARCHIVE))
#define ZIM_ARCHIVE_GET_CLASS(obj) \
    (G_TYPE_INSTANCE_GET_CLASS((obj), ZIM_TYPE_ARCHIVE, ZimArchiveClass))

typedef struct _ZimArchive      ZimArchive;
typedef struct _ZimArchiveClass ZimArchiveClass;

struct _ZimArchive
{
    GObject parent_instance;
};

struct _ZimArchiveClass
{
    GObjectClass parent_class;
};

GType             zim_archive_get_type (void) G_GNUC_CONST;
ZimArchive *         zim_archive_new (const char *zimpath, GError **error);
gboolean        zim_archive_has_main_entry (ZimArchive *archive);
ZimEntry* zim_archive_get_main_entry (ZimArchive* archive);
const char *     zim_archive_get_uuid (ZimArchive *archive);
// ZimArticle *      zim_archive_get_article_by_index (ZimArchive *archive, unsigned int index);
// ZimArticle *      zim_archive_get_article_by_namespace (ZimArchive *archive, const char namesp, const char *path);
// ZimArchiveIterator * zim_archive_find_by_title (ZimArchive *archive, const char namesp, const char *title);
unsigned long     zim_archive_get_filesize (ZimArchive *archive);
unsigned int      zim_archive_get_article_count (ZimArchive *archive);

G_END_DECLS

#endif
