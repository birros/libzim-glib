#ifndef ZIM_SUGGESTION_SEARCH_PRIVATE_GLIB_H
#define ZIM_SUGGESTION_SEARCH_PRIVATE_GLIB_H

#include <zim/suggestion.h>
#include "suggestion-search.h"
#include "suggestion-searcher.h"

ZimSuggestionSearch *zim_suggestion_search_new(ZimArchive *archive, ZimSuggestionSearcher *suggestion_searcher, zim::SuggestionSearch *search_cpp);

#endif
