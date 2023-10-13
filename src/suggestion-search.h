#ifndef ZIM_SUGGESTION_SEARCH_GLIB_H
#define ZIM_SUGGESTION_SEARCH_GLIB_H

#include <glib-object.h>
#include "suggestion-result-iterator.h"

G_BEGIN_DECLS

#define ZIM_TYPE_SUGGESTION_SEARCH \
    (zim_suggestion_search_get_type())
#define ZIM_SUGGESTION_SEARCH(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST((obj), ZIM_TYPE_SUGGESTION_SEARCH, ZimSuggestionSearch))
#define ZIM_SUGGESTION_SEARCH_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST((klass), ZIM_TYPE_SUGGESTION_SEARCH, ZimSuggestionSearchClass))
#define ZIM_IS_SUGGESTION_SEARCH(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE((obj), ZIM_TYPE_SUGGESTION_SEARCH))
#define ZIM_IS_SUGGESTION_SEARCH_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE((klass), ZIM_TYPE_SUGGESTION_SEARCH))
#define ZIM_SUGGESTION_SEARCH_GET_CLASS(obj) \
    (G_TYPE_INSTANCE_GET_CLASS((obj), ZIM_TYPE_SUGGESTION_SEARCH, ZimSuggestionSearchClass))

typedef struct _ZimSuggestionSearch      ZimSuggestionSearch;
typedef struct _ZimSuggestionSearchClass ZimSuggestionSearchClass;

struct _ZimSuggestionSearch
{
    GObject parent_instance;
};

struct _ZimSuggestionSearchClass
{
    GObjectClass parent_class;
};

GType             zim_suggestion_search_get_type (void) G_GNUC_CONST;
ZimSuggestionResultIterator * zim_suggestion_search_get_results (ZimSuggestionSearch *suggestion_search, int start, int max_results);

G_END_DECLS

#endif
