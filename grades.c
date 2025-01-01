#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

int load_grades(Structs *structs)
{
    FILE *file;
    char filename[30];
    char ch;
    int num;
    int grade_index;
    int course_index;

    course_index = 0;
    grade_index = 0;
    for (int i = 0; i < structs->lengths[0]; i++)
    {
        num = 0;
        if (!sprintf(filename, "grades/%d.txt", i) == 0)
            return (0);
        file = fopen(filename, "r");
        while ((ch = fgetc(file)) != EOF)
        {
            if (ch == 'X')
            {
                while ((ch =fgetc(file)) != ',' || ch != '\n' || ch != EOF)
                {
                    num += ((num * 10) + (ch - '0'));
                }
                if (ch == ',' || ch == '\n')
                {
                    structs->students[i].grades[course_index].course_id;
                    num = 0;
                    if (ch == '\n')
                        course_index++;
                }
            }
            else if (ch >= '0' && ch <= '9')
                num += ((num * 10) + (ch - '0'));
            else if (ch == ',' || ch == '\n')
            {
                structs->students[i].grades[course_index].grade[grade_index] = num;
                num = 0;
                grade_index++;
                if (ch == '\n')
                {
                    course_index++;
                    grade_index = 0;
                }
            }
        }
        fclose(file);
    }
    return (1);
}

int restore_grades(Structs *structs)
{
    FILE *file;
    char filename[30];

    for (int i = 0; i < structs->lengths[0]; i++)
    {
        sprintf(filename, "grades/%d.txt", structs->students[i].student_id);
        file = fopen(filename, "w");
        if (!file)
            return (0);
        for (int j = 0; j < structs->students[i].count_courses; j++)
        {
            if (!fprintf(file, "X%d", structs->students[i].grades[j].course_id))
            {
                fclose(file);
                return (0);
            }
            for (int k = 0; k < structs->students[i].grades[j].count_grades; k++)
            {
                if (!fprintf(file, ",%d", structs->students[i].grades[j].grade[k]))
                {
                    fclose(file);
                    return (0);
                }
            }
            if (!fprintf(file, "\n"))
            {
                fclose(file);
                return (0);
            }
        }
        fclose(file);
    }
    return (1);
}
