#ifndef ZIM_SUGGESTION_SEARCH_PRIVATE_GLIB_H
#define ZIM_SUGGESTION_SEARCH_PRIVATE_GLIB_H

#include <zim/suggestion.h>
#include "archive.h"
#include "suggestion-search.h"
#include "suggestion-result-iterator.h"

ZimSuggestionResultIterator *zim_suggestion_result_iterator_new(ZimArchive *archive, ZimSuggestionSearch *suggestion_search, zim::SuggestionResultSet::iterator begin, zim::SuggestionResultSet::iterator end);

#endif
