#include "gmeme-app-data.h"

int main(int argc, char **argv)
{

    gmeme_app_data_init();

    GalleryImages *imgs = meme_app_data_get_all_images();

    for(size_t i = 0; i < imgs->count; i++)
    {
        g_print("Id: %d\nTitle: %s\nPath: %s\nKeywords: %s\n------------------------------\n",
                imgs->images[i].id, imgs->images[i].title, imgs->images[i].absolutePath, imgs->images[i].keyword);
    }

    meme_app_data_gallery_images_dispose(imgs);

    gmeme_app_data_dispose();

    return 0;
}