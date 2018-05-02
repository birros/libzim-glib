#ifndef ZIM_ARTICLE_PRIVATE_GLIB_H
#define ZIM_ARTICLE_PRIVATE_GLIB_H

#include <zim/article.h>
#include "article.h"

void zim_article_set_internal_article (ZimArticle *article, ZimFile *zim_file, const zim::Article article_cpp);

#endif
