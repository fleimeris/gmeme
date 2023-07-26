//
// Created by benas on 7/25/23.
//

#include "gmeme-utils.h"

//Just found out that you cannot copy GIFs to clipboard
//So program should just open it in default file manager

gboolean gmeme_utils_copy_image_to_clipboard(const char *path)
{
    GUri *uri = g_uri_build(G_URI_FLAGS_NONE, "file", NULL, NULL, -1, path, NULL, NULL);
    char *uriString = g_uri_to_string(uri);
    GAppInfo *defaultApp = g_app_info_get_default_for_type("inode/directory", TRUE);

    if(!defaultApp)
    {
        g_print("Failed to get default file manager\n");
        return FALSE;
    }

    GList *uriList = NULL;
    uriList = g_list_append(uriList, uriString);

    GError *err = NULL;
    if(!g_app_info_launch_uris(defaultApp, uriList, NULL, &err))
    {
        g_print("Failed to launch default file manager: %s\n", err->message);
        g_free(uriString);
        g_uri_unref(uri);
        g_list_free(uriList);
        return FALSE;
    }

    g_free(uriString);
    g_uri_unref(uri);
    g_list_free(uriList);

    return TRUE;
}

gboolean gmeme_utils_open_file_manager(const char *path)
{
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(path, NULL);

    if(!pixbuf)
    {
        g_print("Failed to create pixbuf\n");
        return FALSE;
    }

    GdkDisplay *display = gdk_display_get_default();

    if(!display)
    {
        g_print("Failed to create pixbuf\n");
        g_object_unref(pixbuf);
        return FALSE;
    }

    GdkClipboard *clipboard = gdk_display_get_clipboard(display);
    gdk_clipboard_set(clipboard, GDK_TYPE_PIXBUF, pixbuf);
    g_object_unref(pixbuf);

    return TRUE;
}