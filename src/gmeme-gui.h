//
// Created by benas on 7/16/23.
//

#ifndef GMEME_GMEME_GUI_H
#define GMEME_GMEME_GUI_H

#include "gmeme-paintable.h"
#include "gmeme-app-data.h"

struct GuiMeme
{
    Image *image;
    GdkPaintable *gMemePaintable;
    GtkWidget *gImage;
} typedef GuiMeme;

int gmeme_gui_run(int argc, char **argv);

#endif //GMEME_GMEME_GUI_H
