#ifndef ZIM_ITEM_PRIVATE_GLIB_H
#define ZIM_ITEM_PRIVATE_GLIB_H

#include <zim/item.h>
#include "archive.h"
#include "item.h"

ZimItem *zim_item_new(ZimArchive *archive, const zim::Item item_cpp);

#endif
