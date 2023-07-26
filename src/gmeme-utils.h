//
// Created by benas on 7/25/23.
//

#ifndef GMEME_GMEME_UTILS_H
#define GMEME_GMEME_UTILS_H

#include <gtk/gtk.h>
#include "gmeme-gui.h"

gboolean gmeme_utils_open_file_manager(const char *path);
gboolean gmeme_utils_copy_image_to_clipboard(const char *path);

#endif //GMEME_GMEME_UTILS_H
