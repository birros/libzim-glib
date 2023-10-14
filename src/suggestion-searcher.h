#ifndef ZIM_SUGGESTION_SEARCHER_GLIB_H
#define ZIM_SUGGESTION_SEARCHER_GLIB_H

#include <glib-object.h>
#include "archive.h"
#include "suggestion-search.h"

G_BEGIN_DECLS

#define ZIM_TYPE_SUGGESTION_SEARCHER \
    (zim_suggestion_searcher_get_type())
#define ZIM_SUGGESTION_SEARCHER(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST((obj), ZIM_TYPE_SUGGESTION_SEARCHER, ZimSuggestionSearcher))
#define ZIM_SUGGESTION_SEARCHER_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST((klass), ZIM_TYPE_SUGGESTION_SEARCHER, ZimSuggestionSearcherClass))
#define ZIM_IS_SUGGESTION_SEARCHER(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE((obj), ZIM_TYPE_SUGGESTION_SEARCHER))
#define ZIM_IS_SUGGESTION_SEARCHER_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE((klass), ZIM_TYPE_SUGGESTION_SEARCHER))
#define ZIM_SUGGESTION_SEARCHER_GET_CLASS(obj) \
    (G_TYPE_INSTANCE_GET_CLASS((obj), ZIM_TYPE_SUGGESTION_SEARCHER, ZimSuggestionSearcherClass))

typedef struct _ZimSuggestionSearcher ZimSuggestionSearcher;
typedef struct _ZimSuggestionSearcherClass ZimSuggestionSearcherClass;

struct _ZimSuggestionSearcher
{
    GObject parent_instance;
};

struct _ZimSuggestionSearcherClass
{
    GObjectClass parent_class;
};

GType zim_suggestion_searcher_get_type(void) G_GNUC_CONST;
ZimSuggestionSearcher *zim_suggestion_searcher_new(ZimArchive *zim_archive);
ZimSuggestionSearch *zim_suggestion_searcher_suggest(ZimSuggestionSearcher *zim_suggestion_searcher, const char *query);

G_END_DECLS

#endif
