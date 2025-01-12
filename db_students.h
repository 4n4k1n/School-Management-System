#ifndef DB_STUDENTS_H
#define DB_STUDENTS_H

#include <sqlite3.h>

int db_add_student(sqlite3 *db);
int db_print_all_students(sqlite3 *db);
int print_single_student(sqlite3 *db);

#endif