//
// Created by benas on 7/16/23.
//

#include "gmeme-app-data.h"
#include <glib/gstdio.h>
#include <sqlite3.h>

gchar* configFilePath;
sqlite3 *db;

gboolean gmeme_app_data_insert_image(gchar *title, gchar *filePath, gchar *keyword)
{
    const gchar *insertImage = "INSERT INTO images (\"Title\", \"AbsolutePath\", \"Keywords\") "
                               "VALUES (?, ?, ?)";
    sqlite3_stmt *stmt;

    if(sqlite3_prepare_v2(db, insertImage, -1, &stmt, 0) != SQLITE_OK)
    {
        g_print("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return FALSE;
    }

    sqlite3_bind_text(stmt, 1, title, -1, NULL);
    sqlite3_bind_text(stmt, 2, filePath, -1, NULL);
    sqlite3_bind_text(stmt, 3, keyword, -1, NULL);

    if(sqlite3_step(stmt) != SQLITE_DONE)
    {
        g_print("Failed to step: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return FALSE;
    }

    sqlite3_finalize(stmt);

    return TRUE;
}

GalleryImages *gmeme_app_data_get_all_images(void)
{
    const gchar *getAllImages = "select \"Id\", \"Title\", \"AbsolutePath\", \"Keywords\""
                                "from images";
    sqlite3_stmt *stmt;

    if(sqlite3_prepare_v2(db, getAllImages, -1, &stmt, 0) != SQLITE_OK)
    {
        g_print("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    int allocRows = 10;

    GalleryImages *result = g_malloc(sizeof(GalleryImages));
    result->count = 0;
    result->images = g_malloc(allocRows * sizeof(Image));

    while(sqlite3_step(stmt) == SQLITE_ROW)
    {
        if(result->count >= allocRows)
        {
            allocRows += 3;
            result->images = g_realloc(result->images, allocRows * sizeof(Image));
        }

        result->images[result->count].id = sqlite3_column_int(stmt, 0);
        result->images[result->count].title = g_strdup((char*)sqlite3_column_text(stmt, 1));
        result->images[result->count].absolutePath = g_strdup((char*)sqlite3_column_text(stmt, 2));
        result->images[result->count].keywords = g_strdup((char*)sqlite3_column_text(stmt, 3));

        result->count++;
    }

    sqlite3_finalize(stmt);

    return result;
}

void apply_migrations(void)
{
    gchar *errMsg = 0;
    const gchar *createMetadataTable = "CREATE TABLE IF NOT EXISTS metadata"
                                     "(db_schema_version TEXT);";
    sqlite3_exec(db, createMetadataTable, 0, 0, &errMsg);

    const char *insertSchemaVersion = "INSERT INTO metadata"
                                      "(db_schema_version)"
                                      "VALUES ('1.0')";
    sqlite3_exec(db, insertSchemaVersion, 0, 0, &errMsg);

    const char *insertImagesTable = "CREATE TABLE IF NOT EXISTS images "
                                    "(Id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                    "Title TEXT,"
                                    "AbsolutePath INTEGER,"
                                    "Keywords TEXT);";
    sqlite3_exec(db, insertImagesTable, 0, 0, &errMsg);
}

int create_db(gboolean applyMigrations)
{
    if(sqlite3_open(configFilePath, &db) != SQLITE_OK)
    {
        g_print("Failed to create sqlite3 db: %s\n", sqlite3_errmsg(db));
        gmeme_app_data_dispose();
        return -1;
    }

    if(applyMigrations)
        apply_migrations();

    return 1;
}

int gmeme_app_data_init(void)
{
    const gchar *configFolderName = "gmeme";
    const gchar *configFileName = "gmeme.db";
    const gchar *userDataPath = g_get_user_data_dir();

    gchar *configFolderPath = g_build_path(G_DIR_SEPARATOR_S, userDataPath, configFolderName, NULL);

    if(!g_file_test(configFolderPath, G_FILE_TEST_IS_DIR))
    {
        gint err = g_mkdir(configFolderPath, 0755);

        if(err == -1)
        {
            g_print("Failed to create a file: %s\n", g_strerror(errno));
            g_free(configFolderPath);
            return -1;
        }
    }

    configFilePath = g_build_filename(configFolderPath, configFileName, NULL);

    int succ;

    if(!g_file_test(configFilePath, G_FILE_TEST_IS_REGULAR))
        succ = create_db(TRUE);
    else
        succ = create_db(FALSE);

    if(succ == -1)
        return succ;

    g_free(configFolderPath);

    return 1;
}

void gmeme_app_data_dispose(void)
{
    g_free(configFilePath);
    sqlite3_close(db);
}

void gmeme_app_data_gallery_images_dispose(GalleryImages *galleryImages)
{
    for(size_t i = 0; i < galleryImages->count; i++)
    {
        g_free(galleryImages->images[i].title);
        g_free(galleryImages->images[i].absolutePath);
        g_free(galleryImages->images[i].keywords);
    }

    g_free(galleryImages->images);
    g_free(galleryImages);
}

void gmeme_app_data_gallery_images_dispose_safe(GalleryImages *galleryImages)
{
    g_free(galleryImages->images);
    g_free(galleryImages);
}