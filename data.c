#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "read_files.h"
#include "write_files.h"

int fcountl(FILE *file)
{
    int count;
    char ch;

    count = 0;
    while ((ch = getc(file)) != EOF)
    {
        if (ch == '\n')
            count++;
    }
    return (count);
}

int get_lens(Structs *structs)
{
    FILE *file;

    file = fopen("students.txt", "r");
    if (!file)
        return (0);
    structs->lengths[0] = fcountl(file);
    fclose(file);
    file = fopen("courses.txt", "r");
    if (!file)
        return (0);
    structs->lengths[1] = fcountl(file);
    fclose(file);
    return (1);
}

int alloc_structs(Structs *structs)
{
    structs->students = (Student *)malloc(sizeof(Student) * structs->lengths[0]);
    if (!structs->students)
        return (0);
    structs->courses = (Course *)malloc(sizeof(Course) * structs->lengths[1]);
    if (!structs->courses)
    {
        free(structs->students);
        return (0);
    }
    return (1);
}

void free_struct(Structs *structs)
{
    if (structs->students)
    {
        for (int i = 0; i < structs->lengths[0]; i++)
        {
            if (structs->students[i].grades)
            {
                for (int j = 0; j < structs->students[i].count_courses; j++)
                    free(structs->students[i].grades[j].grade);
                free(structs->students[i].grades);
            }
        }
        free(structs->students);
    }
    free(structs->courses);
}

int load_data(Structs *structs)
{
    if (!get_lens(structs))
    {
        printf("Cant get the lens\n");
        return (0);
    }
    if (!alloc_structs(structs))
    {
        printf("Allocation failed\n");
        return (0);
    }
    if (!read_files(structs))
    {
        printf("Read files failed\n");
        return (0);
    }
    return (1);
}

int restore_data(Structs *structs)
{
    if (!write_courses(structs))
    {
        printf("Course data could not be saved!\n");
        return (0);
    }
    if (!write_students(structs))
    {
        printf("Student data could not be saved!\n");
        return (0);
    }
    return (1);
}
