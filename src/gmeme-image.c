//
// Created by benas on 7/11/23.
//

#include "gmeme-image.h"

struct _GMemeImage
{
    GtkWidget parent;

    GtkWidget *p_image;
    GdkPixbufAnimation *p_pixbufAnim;
    GdkPixbufAnimationIter *p_pixbufAnimIter;
};

G_DEFINE_TYPE(GMemeImage, gmeme_image, GTK_TYPE_WIDGET)

static void gmeme_image_dispose(GObject *object)
{
    GMemeImage *self = GMEME_IMAGE(object);

    G_OBJECT_CLASS(gmeme_image_parent_class)->dispose(object);
}

static void gmeme_image_finalize(GObject *object)
{
    G_OBJECT_CLASS(gmeme_image_parent_class)->finalize(object);
}

static void gmeme_image_class_init(GMemeImageClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);

    object_class->dispose = gmeme_image_dispose;
    object_class->finalize = gmeme_image_finalize;
}

static void gmeme_image_init(GMemeImage *self)
{

}

GtkWidget *gmeme_image_new(void)
{
    return GTK_WIDGET(g_object_new(GMEME_IMAGE_TYPE, NULL));
}

GtkWidget *gmeme_image_new_from_filepath(const char* filename)
{
    GMemeImage *p_gmemeImage = GMEME_IMAGE(gmeme_image_new());

    GdkPixbufAnimation *p_pixbufAnim = gdk_pixbuf_animation_new_from_file(filename, NULL);
    GdkPixbufAnimationIter *p_pixbufAnimIter = gdk_pixbuf_animation_get_iter(p_pixbufAnim, NULL);
    GtkWidget *p_image = gtk_image_new_from_pixbuf(gdk_pixbuf_animation_iter_get_pixbuf(p_pixbufAnimIter));

    p_gmemeImage->p_image = p_image;
    p_gmemeImage->p_pixbufAnim = p_pixbufAnim;
}

GtkWidget *gmeme_image_get_image(GtkWidget *gMemeImage)
{
    GMemeImage *self = GMEME_IMAGE(gMemeImage);

    return self->p_image;
}