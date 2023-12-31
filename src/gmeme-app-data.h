//
// Created by benas on 7/16/23.
//

#ifndef GMEME_GMEME_APP_DATA_H
#define GMEME_GMEME_APP_DATA_H

#include <glib.h>

struct Image
{
    guint id;
    gchar *title;
    gchar *absolutePath;
    gchar *keywords;
} typedef Image;

struct GalleryImages
{
    size_t count;
    Image *images;
} typedef GalleryImages;

int gmeme_app_data_init(void);
void gmeme_app_data_dispose(void);

gboolean gmeme_app_data_insert_image(gchar *title, gchar *filePath, gchar *keyword);
GalleryImages *gmeme_app_data_get_all_images(void);
void gmeme_app_data_gallery_images_dispose(GalleryImages *galleryImages);
void gmeme_app_data_gallery_images_dispose_safe(GalleryImages *galleryImages);

#endif //GMEME_GMEME_APP_DATA_H
