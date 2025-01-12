#include <stdio.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    for(int i = 0; i<argc; i++)
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    printf("\n");
    return 0;
}

int setup_student(sqlite3 *db, char *errMsg)
{
    int rc;
    char *create_students_table = 
        "CREATE TABLE IF NOT EXISTS Students ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "age INTEGER,"
        "email TEXT UNIQUE);";

    rc = sqlite3_exec(db, create_students_table, callback, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s", errMsg);
        sqlite3_free(errMsg);
        return (0);
    }
    return (1);
}

int setup_subject(sqlite3 *db, char *errMsg)
{
    int rc;
    char *create_subjects_table =
        "CREATE TABLE IF NOT EXISTS Subjects ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL UNIQUE);";

    rc = sqlite3_exec(db, create_subjects_table, callback, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s", errMsg);
        sqlite3_free(errMsg);
        return (0);
    }
    return (1);
}

int setup_grades(sqlite3 *db, char *errMsg)
{
    int rc;
    char *create_grades_table =
        "CREATE TABLE IF NOT EXISTS Grades ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "student_id INTEGER,"
        "subject_id INTEGER,"
        "grade REAL,"
        "date TEXT,"
        "FOREIGN KEY (student_id) REFERENCES Students(id) ON DELETE CASCADE,"
        "FOREIGN KEY (subject_id) REFERENCES Subjects(id) ON DELETE CASCADE);";

    rc = sqlite3_exec(db, create_grades_table, callback, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s", errMsg);
        sqlite3_free(errMsg);
        return (0);
    }
    return (1);
}

int setup_db(sqlite3 *db, char *errMsg)
{
    if (!setup_student(db, errMsg))
        return (0);
    if (!setup_subject(db, errMsg))
        return (0);
    if (!setup_grades(db, errMsg))
        return (0);
    fprintf(stdout, "Tables created succesfully!\n");
    return (1);
}
