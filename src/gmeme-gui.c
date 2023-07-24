//
// Created by benas on 7/16/23.
//
#include "gmeme-gui.h"
#include "gmeme-paintable.h"
#include "gmeme-app-data.h"

GuiMeme *memes;

int nPresses = 0;

void stopped(GtkGestureClick* self, GuiMeme *meme)
{
    if(nPresses == 1)
    {
        //TODO: copy image to clipboard
        g_print("%s\n", "//TODO: copy image to clipboard");
    }
    else if(nPresses == 2)
    {
        //TODO: open dialog
        g_print("%s\n", "//TODO: open dialog");
    }

    nPresses = 0;
}

void released(GtkGestureClick* self, gint n_press, gdouble x, gdouble y, GuiMeme *meme)
{
    nPresses = n_press;
}

static void app_activate(GApplication *app)
{
    GtkBuilder *builder = gtk_builder_new_from_resource("/org/github/fleimeris/gmeme/ui/gmeme-main.ui");

    GtkWidget *win = GTK_WIDGET(gtk_builder_get_object(builder, "win"));
    GtkWidget *box = GTK_WIDGET(gtk_builder_get_object(builder, "box"));

    gtk_window_set_application(GTK_WINDOW(win), GTK_APPLICATION(app));

    GalleryImages *images = gmeme_app_data_get_all_images();
    memes = (GuiMeme *) g_malloc(images->count * sizeof(GuiMeme));

    for(size_t i = 0; i < images->count; i++)
    {
        memes[i].image = &images->images[i];
        memes[i].gMemePaintable = gmeme_paintable_new_from_filepath(memes->image[i].absolutePath);

        GtkGesture *gestureClick = gtk_gesture_click_new();
        g_signal_connect(gestureClick, "released", G_CALLBACK(released), &memes[i]);
        g_signal_connect(gestureClick, "stopped", G_CALLBACK(stopped), &memes[i]);
        memes[i].gImage = gtk_image_new_from_paintable(memes[i].gMemePaintable);
        gtk_widget_set_receives_default(memes[i].gImage, TRUE);
        gtk_widget_add_controller(memes[i].gImage, GTK_EVENT_CONTROLLER(gestureClick));

        gtk_box_append(GTK_BOX(box), memes[i].gImage);
    }

    gtk_window_set_child(GTK_WINDOW(win), box);
    gtk_window_present(GTK_WINDOW(win));

    g_object_unref(builder);
}

int gmeme_gui_run(int argc, char **argv)
{
    GtkApplication *app;
    int stat;

    app = gtk_application_new("com.github.fleimeris.gmeme", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
    stat = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    g_free(memes);

    return stat;
}