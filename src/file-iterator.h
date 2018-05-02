#ifndef ZIM_FILE_ITERATOR_GLIB_H
#define ZIM_FILE_ITERATOR_GLIB_H

#include <glib-object.h>
#include "file.h"

G_BEGIN_DECLS

#define ZIM_TYPE_FILE_ITERATOR \
    (zim_file_iterator_get_type())
#define ZIM_FILE_ITERATOR(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST((obj), ZIM_TYPE_FILE_ITERATOR, ZimFileIterator))
#define ZIM_FILE_ITERATOR_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST((klass), ZIM_TYPE_FILE_ITERATOR, ZimFileIteratorClass))
#define ZIM_IS_FILE_ITERATOR(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE((obj), ZIM_TYPE_FILE_ITERATOR))
#define ZIM_IS_FILE_ITERATOR_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE((klass), ZIM_TYPE_FILE_ITERATOR))
#define ZIM_FILE_ITERATOR_GET_CLASS(obj) \
    (G_TYPE_INSTANCE_GET_CLASS((obj), ZIM_TYPE_FILE_ITERATOR, ZimFileIteratorClass))

typedef struct _ZimFileIterator      ZimFileIterator;
typedef struct _ZimFileIteratorClass ZimFileIteratorClass;

struct _ZimFileIterator
{
    GObject parent_instance;
};

struct _ZimFileIteratorClass
{
    GObjectClass parent_class;
};

GType             zim_file_iterator_get_type (void);
ZimFileIterator * zim_file_iterator_new (void);
ZimArticle *      zim_file_iterator_get_article (ZimFileIterator *file_iterator);
gboolean          zim_file_iterator_next (ZimFileIterator *file_iterator);

G_END_DECLS

#endif
