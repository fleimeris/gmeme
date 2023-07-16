#include "gmeme-image.h"

GdkPixbufAnimation *pixbufAnin;

GtkWidget* load_image(const char *filename)
{
    pixbufAnin = gdk_pixbuf_animation_new_from_file(filename, NULL);

    return gtk_image_new_from_pixbuf(gdk_pixbuf_animation_get_static_image(pixbufAnin));
}

static void app_activate(GApplication *app)
{
    GtkWidget *win;
    GtkWidget *box;
    GtkWidget *img;
    GtkWidget *btn;

    GtkWidget *test = gmeme_image_new_from_filepath("/home/benas/CLionProjects/gmeme/cmake-build-debug/funnyxd.gif");

    win = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(win), "gMeme");
    gtk_window_set_default_size(GTK_WINDOW(win), 600, 400);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_set_homogeneous(GTK_BOX(box), TRUE);

    img = load_image("/home/benas/CLionProjects/gmeme/cmake-build-debug/funnyxd.gif");

    btn = gtk_button_new_with_label("Fetus deletus xd");

    gtk_box_append(GTK_BOX(box), img);
    gtk_box_append(GTK_BOX(box), btn);
    gtk_box_append(GTK_BOX(box), gmeme_image_get_image(test));

    gtk_window_set_child(GTK_WINDOW(win), box);

    gtk_window_present(GTK_WINDOW(win));
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int stat;

    app = gtk_application_new("com.github.fleimeris.gmeme", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
    stat = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return stat;
}