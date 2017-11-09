#ifndef ZIM_FILEHEADER_GLIB_H
#define ZIM_FILEHEADER_GLIB_H

#include <glib-object.h>

G_BEGIN_DECLS

#define ZIM_TYPE_FILEHEADER \
    (zim_fileheader_get_type())
#define ZIM_FILEHEADER(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST((obj), ZIM_TYPE_FILEHEADER, ZimFileheader))
#define ZIM_FILEHEADER_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST((klass), ZIM_TYPE_FILEHEADER, ZimFileheaderClass))
#define ZIM_IS_FILEHEADER(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE((obj), ZIM_TYPE_FILEHEADER))
#define ZIM_IS_FILEHEADER_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE((klass), ZIM_TYPE_FILEHEADER))
#define ZIM_FILEHEADER_GET_CLASS(obj) \
    (G_TYPE_INSTANCE_GET_CLASS((obj), ZIM_TYPE_FILEHEADER, ZimFileheaderClass))

typedef struct _ZimFileheader      ZimFileheader;
typedef struct _ZimFileheaderClass ZimFileheaderClass;

struct _ZimFileheader
{
    GObject parent_instance;
};

struct _ZimFileheaderClass
{
    GObjectClass parent_class;
};

GType           zim_fileheader_get_type (void) G_GNUC_CONST;
ZimFileheader * zim_fileheader_new (void);
gboolean        zim_fileheader_has_main_page (ZimFileheader *fileheader);
unsigned int    zim_fileheader_get_main_page (ZimFileheader *fileheader);

G_END_DECLS

#endif
