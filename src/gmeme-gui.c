//
// Created by benas on 7/16/23.
//
#include "gmeme-gui.h"
#include "gmeme-paintable.h"
#include "gmeme-app-data.h"

GuiMeme *memes;

static void clicked(GtkButton* self)
{
    gmeme_app_data_insert_image("test", "test", "test");
}

static void app_activate(GApplication *app)
{
    GtkWidget *win;
    GtkWidget *box;
    GtkWidget *btn;

    GalleryImages *images = gmeme_app_data_get_all_images();

    win = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(win), "gMeme");
    gtk_window_set_default_size(GTK_WINDOW(win), 600, 400);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_set_homogeneous(GTK_BOX(box), TRUE);

    memes = g_malloc(images->count * sizeof(GuiMeme));

/*    for(size_t i = 0; i < images->count; i++)
    {
        memes[i].image = &images->images[i];
        memes[i].gMemePaintable = gmeme_paintable_new_from_filepath(memes->image[i].absolutePath);
        memes[i].gImage = gtk_image_new_from_paintable(memes[i].gMemePaintable);
        gtk_box_append(GTK_BOX(box), memes[i].gImage);
    }*/

    gmeme_app_data_gallery_images_dispose_safe(images);

    btn = gtk_button_new_with_label("Test insert");
    g_signal_connect(btn, "clicked", G_CALLBACK(clicked), NULL);
    gtk_box_append(GTK_BOX(box), btn);

    gtk_window_set_child(GTK_WINDOW(win), box);

    gtk_window_present(GTK_WINDOW(win));

    GtkBuilder *builder = gtk_builder_new_from_resource("/org/github/fleimeris/gmeme/ui/gmeme-main.ui");
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "win"));
    g_print("Window title: %s\n", gtk_window_get_title(GTK_WINDOW(window)));
}

int gmeme_gui_run(int argc, char **argv)
{
    GtkApplication *app;
    int stat;

    app = gtk_application_new("com.github.fleimeris.gmeme", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
    stat = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return stat;
}