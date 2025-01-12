#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "db_setup.h"
#include "db_students.h"

int main(void)
{
    sqlite3 *db;
    char *errMsg = NULL;
    int rc;
    int input;

    rc = sqlite3_open("database.db", &db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cant open databse: %s!\n", sqlite3_errmsg(db));
        return (1);
    }
    fprintf(stdout, "Database opend succesfully!\n");
    setup_db(db, errMsg);
    while (1)
    {
        printf("Enter activity: ");
        scanf("%d", &input);
        if (input == 0)
            break;
        else if (input == 1)
            db_add_student(db);
        else if (input == 2)
            db_print_all_students(db);
        else if (input == 3)
            print_single_student(db);
    }
    sqlite3_close(db);
    return (0);
}
