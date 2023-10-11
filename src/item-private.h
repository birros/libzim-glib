#ifndef ZIM_ITEM_PRIVATE_GLIB_H
#define ZIM_ITEM_PRIVATE_GLIB_H

#include <zim/item.h>
#include "archive.h"
#include "item.h"

void zim_item_set_internal_item (ZimItem *item, ZimArchive *zim_archive, const zim::Item item_cpp);

#endif
