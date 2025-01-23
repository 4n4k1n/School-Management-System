#include <stdio.h>
#include <sqlite3.h>
#include "create_table.h"

int main(int ac, char **av)
{
    sqlite3 *db;

    if (ac != 2)
    {
        fprintf(stderr, "./school <option>\n\n");
        return (1);
    }
    if (!setup_database(db))
        return (1);
    return (0);
}
