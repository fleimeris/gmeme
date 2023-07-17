//
// Created by benas on 7/16/23.
//

#include "gmeme-gui.h"
#include "gmeme-paintable.h"

static void app_activate(GApplication *app)
{
    GtkWidget *win;
    GtkWidget *box;

    GdkPaintable *pPaintable = gmeme_paintable_new_from_filepath("/home/benas/CLionProjects/gmeme/cmake-build-debug/funnyxd.gif");
    GtkWidget *paintableImage = gtk_image_new_from_paintable(pPaintable);

    GdkPaintable *pStatic = gmeme_paintable_new_from_filepath("/home/benas/CLionProjects/gmeme/cmake-build-debug/hello.jpg");
    GtkWidget *staticImage = gtk_image_new_from_paintable(pStatic);

    win = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(win), "gMeme");
    gtk_window_set_default_size(GTK_WINDOW(win), 600, 400);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_set_homogeneous(GTK_BOX(box), TRUE);

    gtk_box_append(GTK_BOX(box), staticImage);
    gtk_box_append(GTK_BOX(box), paintableImage);

    gtk_window_set_child(GTK_WINDOW(win), box);

    gtk_window_present(GTK_WINDOW(win));
}

int run_gui(int argc, char **argv)
{
    GtkApplication *app;
    int stat;

    app = gtk_application_new("com.github.fleimeris.gmeme", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
    stat = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return stat;
}