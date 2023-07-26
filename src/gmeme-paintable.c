//
// Created by benas on 7/16/23.
//

#include "gmeme-paintable.h"

struct _GMemePaintable
{
    GObject parent;

    GdkPixbufAnimation *anim;
    GdkPixbufAnimationIter *iter;
    gboolean isStatic;

    guint timeoutHandle;
};

static void gmeme_paintable_snapshot(GdkPaintable *paintable, GdkSnapshot *snapshot, double width, double height)
{
    GMemePaintable *self = GMEME_PAINTABLE(paintable);

    GdkPixbuf *pixbuf;
    GdkTexture *texture;

    if(self->isStatic)
    {
        pixbuf = gdk_pixbuf_animation_get_static_image(self->anim);
        texture = gdk_texture_new_for_pixbuf(pixbuf);
    }
    else
    {
        gdk_pixbuf_animation_iter_advance(self->iter, NULL);
        pixbuf = gdk_pixbuf_animation_iter_get_pixbuf (self->iter);
        texture = gdk_texture_new_for_pixbuf (pixbuf);
    }

    gdk_paintable_snapshot (GDK_PAINTABLE (texture), snapshot, width, height);

    g_object_unref (texture);
}

static int gmeme_paintable_get_intrinsic_width(GdkPaintable *paintable)
{
    GMemePaintable *self = GMEME_PAINTABLE(paintable);

    return gdk_pixbuf_animation_get_width(self->anim);
}

static int gmeme_paintable_get_intrinsic_height(GdkPaintable *paintable)
{
    GMemePaintable *self = GMEME_PAINTABLE(paintable);

    return gdk_pixbuf_animation_get_height(self->anim);
}

static void gmeme_paintable_init_interface(GdkPaintableInterface *interface)
{
    interface->snapshot = gmeme_paintable_snapshot;
    interface->get_intrinsic_width = gmeme_paintable_get_intrinsic_width;
    interface->get_intrinsic_height = gmeme_paintable_get_intrinsic_height;
}

G_DEFINE_TYPE_WITH_CODE(GMemePaintable, gmeme_paintable, G_TYPE_OBJECT,
                        G_IMPLEMENT_INTERFACE(GDK_TYPE_PAINTABLE, gmeme_paintable_init_interface))

static void gmeme_paintable_dispose(GObject *object)
{
    GMemePaintable *self = GMEME_PAINTABLE(object);

    g_clear_object(&self->anim);
    g_clear_object(&self->iter);

    if(self->timeoutHandle)
    {
        g_source_remove(self->timeoutHandle);
        self->timeoutHandle = 0;
    }

    G_OBJECT_CLASS(gmeme_paintable_parent_class)->dispose(object);
}

static void gmeme_paintable_class_init(GMemePaintableClass *class)
{
    GObjectClass *obj_class = G_OBJECT_CLASS(class);

    obj_class->dispose = gmeme_paintable_dispose;
}

static void gmeme_paintable_init(GMemePaintable *paintable) {}

static gboolean animate(gpointer data)
{
    GMemePaintable *self = data;

    int delay = gdk_pixbuf_animation_iter_get_delay_time(self->iter);
    self->timeoutHandle = g_timeout_add(delay, animate, self);

    gdk_paintable_invalidate_contents(GDK_PAINTABLE(self));

    return G_SOURCE_REMOVE;
}

GdkPaintable *gmeme_paintable_new_from_filepath(const char *filePath)
{
    GMemePaintable *self = GMEME_PAINTABLE(g_object_new(GMEME_TYPE_PAINTABLE, NULL));

    self->anim = gdk_pixbuf_animation_new_from_file(filePath, NULL);
    self->isStatic = gdk_pixbuf_animation_is_static_image(self->anim);

    if(!self->isStatic)
    {
        self->iter = gdk_pixbuf_animation_get_iter(self->anim, NULL);

        int delay = gdk_pixbuf_animation_iter_get_delay_time(self->iter);
        self->timeoutHandle = g_timeout_add(delay, animate, self);

        gdk_paintable_invalidate_contents(GDK_PAINTABLE(self));
    }

    return GDK_PAINTABLE(self);
}

gboolean gmeme_paintable_is_static(GdkPaintable *paintable)
{
    GMemePaintable *self = GMEME_PAINTABLE(paintable);

    return self->isStatic;
}