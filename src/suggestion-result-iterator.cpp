#include <iostream>
#include <zim/suggestion.h>
#include "archive.h"
#include "entry-private.h"
#include "suggestion-search.h"
#include "suggestion-result-iterator.h"

/**
 * SECTION: zim-suggestion_result-iterator
 * @Title: ZimSuggestionResultIterator
 * @short_description: A zim suggestion_result_iterator
 *
 * #ZimSuggestionResultIterator represent a result of a #ZimSuggestionResult class.
 */

#define ZIM_SUGGESTION_RESULT_ITERATOR_GET_PRIVATE(obj) \
    ((ZimSuggestionResultIteratorPrivate *) zim_suggestion_result_iterator_get_instance_private ((ZimSuggestionResultIterator *) (obj)))

typedef struct _ZimSuggestionResultIteratorPrivate ZimSuggestionResultIteratorPrivate;
struct _ZimSuggestionResultIteratorPrivate
{
    ZimArchive *archive;
    ZimSuggestionSearch *suggestion_search;

    zim::SuggestionResultSet::iterator begin;
    zim::SuggestionResultSet::iterator current;
    zim::SuggestionResultSet::iterator end;
};

G_DEFINE_TYPE_WITH_PRIVATE (ZimSuggestionResultIterator, zim_suggestion_result_iterator, G_TYPE_OBJECT)

static void 
zim_suggestion_result_iterator_finalize (GObject *gobject)
{
    ZimSuggestionResultIteratorPrivate *priv = ZIM_SUGGESTION_RESULT_ITERATOR_GET_PRIVATE (gobject);

    g_object_unref (priv->archive);
    g_object_unref (priv->suggestion_search);

    G_OBJECT_CLASS (zim_suggestion_result_iterator_parent_class)->dispose (gobject);
}

static void
zim_suggestion_result_iterator_class_init (ZimSuggestionResultIteratorClass *klass)
{
    G_OBJECT_CLASS (klass)->finalize = zim_suggestion_result_iterator_finalize;
}

static void
zim_suggestion_result_iterator_init (ZimSuggestionResultIterator *object)
{
}

ZimSuggestionResultIterator *
zim_suggestion_result_iterator_new (ZimArchive* archive, ZimSuggestionSearch * suggestion_search, zim::SuggestionResultSet::iterator begin, zim::SuggestionResultSet::iterator end)
{
    ZimSuggestionResultIterator *suggestion_result_iterator = (ZimSuggestionResultIterator *) g_object_new (ZIM_TYPE_SUGGESTION_RESULT_ITERATOR, NULL);

    ZimSuggestionResultIteratorPrivate *priv = ZIM_SUGGESTION_RESULT_ITERATOR_GET_PRIVATE (suggestion_result_iterator);

    priv->archive = archive;
    priv->suggestion_search = suggestion_search;
    g_object_ref (priv->archive);
    g_object_ref (priv->suggestion_search);

    priv->begin = begin;
    priv->current = priv->begin;
    priv->end = end;

    return suggestion_result_iterator;
}

/**
 * zim_suggestion_result_iterator_get_entry:
 * @suggestion_result_iterator: A #ZimSuggestionResultIterator
 *
 * Get the url of the article.
 *
 * Returns: (transfer full): the url of the article
 */
ZimEntry *
zim_suggestion_result_iterator_get_entry (ZimSuggestionResultIterator *suggestion_result_iterator)
{
    ZimSuggestionResultIteratorPrivate *priv = ZIM_SUGGESTION_RESULT_ITERATOR_GET_PRIVATE (suggestion_result_iterator);

    try {
        zim::Entry entry_cpp = priv->current.getEntry();

        ZimEntry *entry = zim_entry_new ();
        zim_entry_set_internal_entry (entry, priv->archive, entry_cpp);

        return entry;
    } catch (std::runtime_error &e) {
        std::wcout << "WARNING: zim_suggestion_result_iterator_get_entry(): " << e.what () << std::endl;

        return NULL;
    }
}

/**
 * zim_suggestion_result_iterator_next:
 * @suggestion_result_iterator: A #ZimSuggestionResultIterator
 *
 * Go to the next result of a suggestion_result.
 *
 * Returns: TRUE if the next result exist, FALSE otherwise
 */
gboolean
zim_suggestion_result_iterator_next (ZimSuggestionResultIterator *suggestion_result_iterator)
{
    ZimSuggestionResultIteratorPrivate *priv = ZIM_SUGGESTION_RESULT_ITERATOR_GET_PRIVATE (suggestion_result_iterator);

    if (priv->current == priv->end) {
        return FALSE;
    }

    priv->current++;

    if (priv->current == priv->end) {
      return FALSE;
    } else {
      return TRUE;
    }
}
