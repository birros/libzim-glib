#ifndef ZIM_ENTRY_PRIVATE_GLIB_H
#define ZIM_ENTRY_PRIVATE_GLIB_H

#include <zim/entry.h>
#include "archive.h"
#include "entry.h"

ZimEntry *zim_entry_new(ZimArchive *zim_archive, const zim::Entry entry_cpp);

#endif
