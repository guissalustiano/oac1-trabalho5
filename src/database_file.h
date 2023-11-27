#include <string.h>
#include "database_t.h"

#ifndef DATABASE_FILE_H
#define DATABASE_FILE_H

#define DB_DIR "db"

void init();
db_data_t file_get(db_key_t key);
void file_put(db_key_t key, db_data_t data);

#endif
