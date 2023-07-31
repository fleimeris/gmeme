//
// Created by benas on 7/31/23.
//

#include "gmeme-info-dialog.h"

struct _GMemeInfoDialog
{
    GObject parent;
    Image *meme;


};

G_DEFINE_FINAL_TYPE(GMemeInfoDialog, gmeme_info_dialog, GTK_TYPE_DIALOG);

static void gmeme_info_dialog_dispose(GObject *object)
{
    GMemeInfoDialog *self = GMEME_INFO_DIALOG(object);

    G_OBJECT_CLASS(gmeme_info_dialog_parent_class)->dispose(object);
}

static void gmeme_info_dialog_init(GMemeInfoDialog *infoDialog)
{
    g_object_unref(builder);
}

static void gmeme_info_dialog_class_init(GMemeInfoDialogClass *class)
{
    GObjectClass *objClass = G_OBJECT_CLASS(class);

    objClass->dispose = gmeme_info_dialog_dispose;
}

GtkWidget *gmeme_info_dialog_new_from_meme(Image *meme)
{
    GMemeInfoDialog *infoDialog = GMEME_INFO_DIALOG(g_object_new(GMEME_TYPE_INFO_DIALOG, NULL));

    infoDialog->meme = meme;

    GTK_WIDGET(infoDialog);
}
