#ifndef ZIM_SUGGESTION_RESULT_ITERATOR_GLIB_H
#define ZIM_SUGGESTION_RESULT_ITERATOR_GLIB_H

#include <glib-object.h>
#include "entry.h"

G_BEGIN_DECLS

#define ZIM_TYPE_SUGGESTION_RESULT_ITERATOR \
    (zim_suggestion_result_iterator_get_type())
#define ZIM_SUGGESTION_RESULT_ITERATOR(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST((obj), ZIM_TYPE_SUGGESTION_RESULT_ITERATOR, ZimSuggestionResultIterator))
#define ZIM_SUGGESTION_RESULT_ITERATOR_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST((klass), ZIM_TYPE_SUGGESTION_RESULT_ITERATOR, ZimSuggestionResultIteratorClass))
#define ZIM_IS_SUGGESTION_RESULT_ITERATOR(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE((obj), ZIM_TYPE_SUGGESTION_RESULT_ITERATOR))
#define ZIM_IS_SUGGESTION_RESULT_ITERATOR_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE((klass), ZIM_TYPE_SUGGESTION_RESULT_ITERATOR))
#define ZIM_SUGGESTION_RESULT_ITERATOR_GET_CLASS(obj) \
    (G_TYPE_INSTANCE_GET_CLASS((obj), ZIM_TYPE_SUGGESTION_RESULT_ITERATOR, ZimSuggestionResultIteratorClass))

typedef struct _ZimSuggestionResultIterator ZimSuggestionResultIterator;
typedef struct _ZimSuggestionResultIteratorClass ZimSuggestionResultIteratorClass;

struct _ZimSuggestionResultIterator
{
    GObject parent_instance;
};

struct _ZimSuggestionResultIteratorClass
{
    GObjectClass parent_class;
};

GType zim_suggestion_result_iterator_get_type(void) G_GNUC_CONST;
ZimEntry *zim_suggestion_result_iterator_get_entry(ZimSuggestionResultIterator *suggestion_result_iterator, GError **error);
gboolean zim_suggestion_result_iterator_next(ZimSuggestionResultIterator *suggestion_result_iterator);

G_END_DECLS

#endif
