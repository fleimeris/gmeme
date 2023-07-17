//
// Created by benas on 7/16/23.
//

#include "gmeme-app-data.h"
#include <glib.h>
#include <glib/gstdio.h>
#include <sqlite3.h>

gchar* configFilePath;
sqlite3 *db;

void apply_migrations(void)
{
    gchar *errMsg = 0;
    const gchar *createMetadataSql = "CREATE TABLE metadata"
                                     "(db_schema_version TEXT);";

    sqlite3_exec(db, createMetadataSql, 0, 0, &errMsg);

    const char *insertSchemaVersion = "INSERT INTO metadata"
                                      "(db_schema_version)"
                                      "VALUES ('1.0')";

    sqlite3_exec(db, insertSchemaVersion, 0, 0, &errMsg);
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