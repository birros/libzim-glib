#ifndef ZIM_FILE_ITERATOR_PRIVATE_GLIB_H
#define ZIM_FILE_ITERATOR_PRIVATE_GLIB_H

#include "file.h"

void zim_file_iterator_set_internal_file_iterator (ZimFileIterator *file_iterator, ZimFile *file, zim::File::const_iterator file_iterator_cpp);

#endif
