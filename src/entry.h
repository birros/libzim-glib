#ifndef ZIM_ENTRY_GLIB_H
#define ZIM_ENTRY_GLIB_H

#include <glib-object.h>
#include "item.h"

G_BEGIN_DECLS

#define ZIM_TYPE_ENTRY \
    (zim_entry_get_type())
#define ZIM_ENTRY(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST((obj), ZIM_TYPE_ENTRY, ZimEntry))
#define ZIM_ENTRY_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST((klass), ZIM_TYPE_ENTRY, ZimEntryClass))
#define ZIM_IS_ENTRY(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE((obj), ZIM_TYPE_ENTRY))
#define ZIM_IS_ENTRY_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE((klass), ZIM_TYPE_ENTRY))
#define ZIM_ENTRY_GET_CLASS(obj) \
    (G_TYPE_INSTANCE_GET_CLASS((obj), ZIM_TYPE_ENTRY, ZimEntryClass))

typedef struct _ZimEntry      ZimEntry;
typedef struct _ZimEntryClass ZimEntryClass;

struct _ZimEntry
{
    GObject parent_instance;
};

struct _ZimEntryClass
{
    GObjectClass parent_class;
};

GType        zim_entry_get_type (void);
ZimEntry * zim_entry_new (void);
const char * zim_entry_get_title (ZimEntry *entry);
const char * zim_entry_get_path (ZimEntry *entry);
ZimItem * zim_entry_get_item (ZimEntry *entry, gboolean follow);
// const char * zim_entry_get_url (ZimEntry *entry);
// const char * zim_entry_get_mime_type (ZimEntry *entry);
// const char   zim_entry_get_namespace (ZimEntry *entry);
// const char * zim_entry_get_data (ZimEntry *entry, gsize *size);
// gsize        zim_entry_get_data_size (ZimEntry *entry);
// gsize        zim_entry_get_offset (ZimEntry *entry);
// gboolean     zim_entry_good (ZimEntry *entry);
// gboolean     zim_entry_is_redirect (ZimEntry *entry);
// ZimEntry * zim_entry_get_redirect_entry (ZimEntry *entry);

G_END_DECLS

#endif
