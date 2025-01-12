#ifndef DB_SETUP_H
#define DB_SETUP_H

#include <sqlite3.h>

int setup_db(sqlite3 *db, char *ErrMsg);

#endif