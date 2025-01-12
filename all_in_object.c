#include <stdio.h>
#include <sqlite3.h>

static int print_callback(void *unused, int ac, char **av, char **columns)
{
    static int header = 1;

    if (header)
    {
        for (int i = 0; i < ac; i++)
            printf("%-15s", columns[i]);
        printf("\n");
        for (int i = 0; i < ac * 15; i++)
            printf("-");
        printf("\n");
        header = 0;
    }
    for (int i = 0; i < ac; i++)
        printf("%-15s", av[i] ? av[i] : "---");
    printf("\n");
    return (0);
}
int print_students_in_subjects(sqlite3 *db)
{
    char *errMsg = NULL;
    char *sql;
    int rc;

    sql = sqlite3_mprintf(
        "SELECT DISTINCT "
        "   Students.name as Students "
        "From Students "
        "JOIN Grades ON ")
}
