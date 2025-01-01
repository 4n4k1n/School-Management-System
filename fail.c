#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

void fail_protocol(Structs *structs)
{
    for (int i = 0; i < structs->lengths[0]; i++)
    {
        for (int j = 0; j < structs->students[i].count_courses; j++)
            free(structs->students[i].grades[j].grade);
        free(structs->students[i].grades);
    }
    free(structs->students);
    for (int i = 0; i < structs->lengths[1]; i++)
        free(structs->courses[i].students_ids);
    free(structs->courses);
}
