//
// Created by benas on 7/16/23.
//

#ifndef GMEME_GMEME_PAINTABLE_H
#define GMEME_GMEME_PAINTABLE_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GMEME_TYPE_PAINTABLE (gmeme_paintable_get_type())
G_DECLARE_FINAL_TYPE(GMemePaintable, gmeme_paintable, GMEME, PAINTABLE, GObject)

GdkPaintable *gmeme_paintable_new_from_filepath(const char *filePath);
gboolean gmeme_paintable_is_static(GdkPaintable *paintable);

G_END_DECLS

#endif //GMEME_GMEME_PAINTABLE_H
