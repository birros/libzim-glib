#ifndef ZIM_ARCHIVE_GLIB_H
#define ZIM_ARCHIVE_GLIB_H

#include <glib-object.h>
#include "entry.h"
#include "item.h"

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
ZimEntry *      zim_archive_get_entry_by_path (ZimArchive *archive, const char * path);
ZimEntry *      zim_archive_get_random_entry (ZimArchive *archive);
ZimItem *     zim_archive_get_illustration_item (ZimArchive *archive, unsigned int size);
unsigned long     zim_archive_get_filesize (ZimArchive *archive);
unsigned int      zim_archive_get_all_entry_count (ZimArchive *archive);
unsigned int      zim_archive_get_article_count (ZimArchive *archive);
const char *      zim_archive_get_metadata (ZimArchive *archive, const char * name);

G_END_DECLS

#endif
