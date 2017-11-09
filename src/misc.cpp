#include <zim/file.h>
#include "misc.h"

/**
 * zim_urldecode:
 * @url: the url encoded to decode
 *
 * Decode an url that is percent-encoded.
 *
 * Returns: (transfer full): the decoded url
 */
char *
zim_urldecode (const char *url)
{
    std::string url_decoded = zim::urldecode (url);
    return g_strdup (url_decoded.c_str ());
}
