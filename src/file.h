#ifndef ZIM_FILE_GLIB_H
#define ZIM_FILE_GLIB_H

#include <glib-object.h>
#include "fileheader.h"
#include "article.h"
#include "file-iterator.h"
typedef struct _ZimFileIterator      ZimFileIterator;

G_BEGIN_DECLS

#define ZIM_TYPE_FILE \
    (zim_file_get_type())
#define ZIM_FILE(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST((obj), ZIM_TYPE_FILE, ZimFile))
#define ZIM_FILE_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST((klass), ZIM_TYPE_FILE, ZimFileClass))
#define ZIM_IS_FILE(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE((obj), ZIM_TYPE_FILE))
#define ZIM_IS_FILE_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE((klass), ZIM_TYPE_FILE))
#define ZIM_FILE_GET_CLASS(obj) \
    (G_TYPE_INSTANCE_GET_CLASS((obj), ZIM_TYPE_FILE, ZimFileClass))

typedef struct _ZimFile      ZimFile;
typedef struct _ZimFileClass ZimFileClass;

struct _ZimFile
{
    GObject parent_instance;
};

struct _ZimFileClass
{
    GObjectClass parent_class;
};

GType             zim_file_get_type (void) G_GNUC_CONST;
ZimFile *         zim_file_new (const char *zimpath, GError **error);
unsigned int      zim_file_get_namespace_begin_offset (ZimFile *file, char namesp);
ZimFileheader *   zim_file_get_fileheader (ZimFile *file);
ZimArticle *      zim_file_get_article_by_index (ZimFile *file, unsigned int index);
ZimArticle *      zim_file_get_article_by_namespace (ZimFile *file, const char namesp, const char *path);
ZimFileIterator * zim_file_find_by_title (ZimFile *file, const char namesp, const char *title);

G_END_DECLS

#endif
