#ifndef ZIM_SEARCH_GLIB_H
#define ZIM_SEARCH_GLIB_H

#include <glib-object.h>
#include "file.h"
#include "search-iterator.h"

G_BEGIN_DECLS

#define ZIM_TYPE_SEARCH \
    (zim_search_get_type())
#define ZIM_SEARCH(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST((obj), ZIM_TYPE_SEARCH, ZimSearch))
#define ZIM_SEARCH_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST((klass), ZIM_TYPE_SEARCH, ZimSearchClass))
#define ZIM_IS_SEARCH(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE((obj), ZIM_TYPE_SEARCH))
#define ZIM_IS_SEARCH_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE((klass), ZIM_TYPE_SEARCH))
#define ZIM_SEARCH_GET_CLASS(obj) \
    (G_TYPE_INSTANCE_GET_CLASS((obj), ZIM_TYPE_SEARCH, ZimSearchClass))

typedef struct _ZimSearch      ZimSearch;
typedef struct _ZimSearchClass ZimSearchClass;

struct _ZimSearch
{
    GObject parent_instance;
};

struct _ZimSearchClass
{
    GObjectClass parent_class;
};

GType               zim_search_get_type (void);
ZimSearch *         zim_search_new (ZimFile *zim_file);
void                zim_search_set_query (ZimSearch *search, const char *query);
void                zim_search_set_range (ZimSearch *search, unsigned int start, unsigned int end);
void                zim_search_set_suggestion_mode (ZimSearch *search, gboolean boolean);
unsigned int        zim_search_get_matches_estimated (ZimSearch *search);
ZimSearchIterator * zim_search_begin (ZimSearch *search);

G_END_DECLS

#endif
