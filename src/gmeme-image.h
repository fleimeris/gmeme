//
// Created by benas on 7/11/23.
//

#ifndef GMEME_GMEME_IMAGE_H
#define GMEME_GMEME_IMAGE_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GMEME_IMAGE_TYPE gmeme_image_get_type()
G_DECLARE_FINAL_TYPE(GMemeImage, gmeme_image, GMEME, IMAGE, GtkWidget)

GtkWidget *gmeme_image_new(void);
GtkWidget *gmeme_image_new_from_filepath(const char* filename);
GtkWidget *gmeme_image_get_image(GtkWidget *gMemeImage);

G_END_DECLS

#endif //GMEME_GMEME_IMAGE_H
