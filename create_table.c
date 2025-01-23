#include <stdio.h>
#include <sqlite3.h>

int open_database(sqlite3 *db)
{
    if (sqlite3_open("database.db", &db) != SQLITE_OK)
    {
        fprintf(stderr, "Cant open the database: %s\n", sqlite3_errmsg(db));
        return (0);
    }
    return (1);
}

int create_student_table(sqlite3 *db)
{
    char *errMsg = NULL;
    char *sql = 
        "CREATE TABLE IF NOT EXITS Students("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "age INTEGER,"
        "email TEXT NOT NULL);";

    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return (0);
    }
    return (1);
}

int create_subject_table(sqlite3 *db)
{
    char *errMsg = NULL;
    char *sql =
        "CREATE TABLE IF NOT EXITS Subjects("
        "id PRIMARY KEY AUTOINCREMENT,"
        "name NOT NULL UNIQUE);";

    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return (0);
    }
    return (1);
}

int create_grades_table(sqlite3 *db)
{
    char *errMsg = NULL;
    char *sql =
        "CREATE TABLE IF NOT EXITS Grades("
        "id PRIMARY KEY AUTOINCREMENT,"
        "student_id INTEGER,"
        "subject_id INTEGER,"
        "grade REAL"
        "FOREIGN KEY (student_id) REFERENCES Students(id) ON DELETE CASCADE,"
        "FOREIGN KEY (subject_id) REFERENCES Subjects(id) ON DELETE CASCADE);";

    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return (0);
    }
    return (1);
}

int setup_database(sqlite3 *db)
{
    if (!open_database(db))
        return (0);
    else if (!create_student_table(db) || !create_subject_table(db) || !create_grades_table(db))
    {
        sqlite3_close(db);
        return (0);
    }
    return (1);
}
