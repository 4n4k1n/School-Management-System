#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

int write_students(Structs *structs)
{
    FILE *file;

    file = fopen("students.txt", "w");
    if (!file)
        return 0;
    for (int i = 0; i < structs->lengths[0]; i++)
    {
        if (structs->students[i].student_id >= 0)
        {
            if (fprintf(file, "%d,%s,%d,%d,",
                        structs->students[i].student_id,
                        structs->students[i].name,
                        structs->students[i].age,
                        structs->students[i].count_courses) < 0)
            {
                fclose(file);
                return 0;
            }
            for (int j = 0; j < structs->students[i].count_courses; j++)
            {
                if (fprintf(file, "%d,%d,",
                            structs->students[i].grades[j].course_id,
                            structs->students[i].grades[j].count_grades) < 0)
                {
                    fclose(file);
                    return 0;
                }
                for (int k = 0; k < structs->students[i].grades[j].count_grades; k++)
                {
                    if (fprintf(file, "%.1f,", structs->students[i].grades[j].grade[k]) < 0)
                    {
                        fclose(file);
                        return 0;
                    }
                }
            }
            fprintf(file, "\n");
        }
    }
    fclose(file);
    return 1;
}

int write_courses(Structs *structs)
{
    FILE *file;

    file = fopen("courses.txt", "w");
    if (!file)
        return 0;
    for (int i = 0; i < structs->lengths[1]; i++)
    {
        if (structs->courses[i].course_id >= 0)
        {
            if (fprintf(file, "%d,%s,%.2f,%d\n",
                        structs->courses[i].course_id,
                        structs->courses[i].name,
                        structs->courses[i].average_grade,
                        structs->courses[i].count_students) < 0)
            {
                fclose(file);
                return 0;
            }
        }
    }
    fclose(file);
    return 1;
}
