//
// Created by benas on 7/31/23.
//

#ifndef GMEME_GMEME_INFO_DIALOG_H
#define GMEME_GMEME_INFO_DIALOG_H

#include <gtk/gtk.h>
#include "gmeme-app-data.h"

G_BEGIN_DECLS

#define GMEME_TYPE_INFO_DIALOG (gmeme_info_dialog_get_type())
G_DECLARE_FINAL_TYPE(GMemeInfoDialog, gmeme_info_dialog, GMEME, INFO_DIALOG, GtkDialog)

GtkWidget *gmeme_info_dialog_new_from_meme(Image *meme);

G_END_DECLS

#endif //GMEME_GMEME_INFO_DIALOG_H
