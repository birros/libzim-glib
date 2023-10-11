#ifndef ZIM_ENTRY_PRIVATE_GLIB_H
#define ZIM_ENTRY_PRIVATE_GLIB_H

#include <zim/entry.h>
#include "archive.h"
#include "entry.h"

void zim_entry_set_internal_entry (ZimEntry *entry, ZimArchive *zim_archive, const zim::Entry entry_cpp);

#endif
