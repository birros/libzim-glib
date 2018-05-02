#ifndef ZIM_SEARCH_ITERATOR_GLIB_H
#define ZIM_SEARCH_ITERATOR_GLIB_H

#include <glib-object.h>
#include "file.h"

G_BEGIN_DECLS

#define ZIM_TYPE_SEARCH_ITERATOR \
    (zim_search_iterator_get_type())
#define ZIM_SEARCH_ITERATOR(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST((obj), ZIM_TYPE_SEARCH_ITERATOR, ZimSearchIterator))
#define ZIM_SEARCH_ITERATOR_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST((klass), ZIM_TYPE_SEARCH_ITERATOR, ZimSearchIteratorClass))
#define ZIM_IS_SEARCH_ITERATOR(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE((obj), ZIM_TYPE_SEARCH_ITERATOR))
#define ZIM_IS_SEARCH_ITERATOR_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE((klass), ZIM_TYPE_SEARCH_ITERATOR))
#define ZIM_SEARCH_ITERATOR_GET_CLASS(obj) \
    (G_TYPE_INSTANCE_GET_CLASS((obj), ZIM_TYPE_SEARCH_ITERATOR, ZimSearchIteratorClass))

typedef struct _ZimSearchIterator      ZimSearchIterator;
typedef struct _ZimSearchIteratorClass ZimSearchIteratorClass;

struct _ZimSearchIterator
{
    GObject parent_instance;
};

struct _ZimSearchIteratorClass
{
    GObjectClass parent_class;
};

GType               zim_search_iterator_get_type (void);
ZimSearchIterator * zim_search_iterator_new (void);
const char *        zim_search_iterator_get_title (ZimSearchIterator *search_iterator);
const char *        zim_search_iterator_get_url (ZimSearchIterator *search_iterator);
gboolean            zim_search_iterator_next (ZimSearchIterator *search_iterator);

G_END_DECLS

#endif
