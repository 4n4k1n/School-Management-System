#include <stdio.h>
#include <sqlite3.h>

static int single_student_callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    printf("Student Details:\n");
    printf("ID    : %s\n", argv[0] ? argv[0] : "NULL");
    printf("Name  : %s\n", argv[1] ? argv[1] : "NULL");
    printf("Age   : %s\n", argv[2] ? argv[2] : "NULL");
    printf("Email : %s\n", argv[3] ? argv[3] : "NULL");
    printf("\n");
    return 0;
}

int print_single_student(sqlite3 *db)
{
    char *errMsg = NULL;
    int rc;
    char name_input[50];
    char *sql;

    printf("Student name: ");
    scanf(" %49s", name_input);
    sql = sqlite3_mprintf("SELECT * FROM Students WHERE name like '%%%q%%';", name_input);
    rc = sqlite3_exec(db, sql, single_student_callback, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_free(sql);
        return (0);
    }
    sqlite3_free(sql);
    return (1);
}

int db_add_student(sqlite3 *db)
{
    char *sql;
    char name[100];
    int age;
    char email[100];
    int rc;
    char *errMsg;

    errMsg = NULL;
    printf("Student name: ");
    scanf(" %99s", name);
    printf("Student age: ");
    scanf("%d", &age);
    printf("Student email: ");
    scanf(" %99s", email);
    sql = sqlite3_mprintf(
        "INSERT INTO Students (name, age, email) " \
        "VALUES ('%q', %d, '%q')", name, age, email);
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s", errMsg);
        sqlite3_free(errMsg);
        sqlite3_free(sql);
        return (0);
    }
    fprintf(stdout, "Student added succesfully!\n");
    sqlite3_free(sql);
    return (1);
}

int db_print_all_students(sqlite3 *db)
{
    sqlite3_stmt *stmt;
    int rc;
    char *sql = "SELECT * FROM Students;";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL statement failed: %s", sqlite3_errmsg(db));
        return (0);
    }
    printf("STUDENTS\n");
    printf("--------------------------------\n");
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        printf("\n  ID  : %d\n", sqlite3_column_int(stmt, 0));
        printf("NAME  : %s\n", sqlite3_column_text(stmt, 1));
        printf("AGE   : %d\n", sqlite3_column_int(stmt, 2));
        printf("EMAIL : %s\n", sqlite3_column_text(stmt, 3));
    }
    sqlite3_finalize(stmt);
    return (1);
}
