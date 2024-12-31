#include <stdlib.h>
#include <stdio.h>
#include "structs.h"

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
    FILE *files[3];

    files[0] = fopen("students.txt", "r");
    if (!files[0])
    
        return (0);
    files[1] = fopen("courses.txt", "r");
    if (!files[1])
    {
        fclose(files[0]);
        return (0);
    }
    files[2] = fopen("schools.txt", "r");
    if (!files[2])
    {
        fclose(files[0]);
        fclose(files[1]);
        return (0);
    }
    structs->lengths[0] = fcountl(files[0]);
    structs->lengths[1] = fcountl(files[1]);
    structs->lengths[2] = fcountl(files[2]);
    fclose(files[0]);
    fclose(files[1]);
    fclose(files[2]);
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
    structs->schools = (School *)malloc(sizeof(School) * structs->lengths[2]);
    if (!structs->schools)
    {
        free(structs->students);
        free(structs->courses);
        return (0);
    }
    return (1);
}

int alloc_grades(Structs *structs, int index)
{
    structs->students[index].grades = (Grade *)malloc(sizeof(Grade) * structs->students[index].count_courses);
    if (!structs->students[index].grades)
    {
        for (int i = index - 1; i >= 0; i--)
            free(structs->students[i].grades);
        return (0);
    }
    for (int i = 0; i < structs->students[index].count_courses; i++)
        structs->students[index].grades[i].grade = NULL;
    return (1);
}

int read_files(Structs *structs)
{
    FILE *file;

    file = fopen("students.txt", "r");
    if (!file)
        return (0);
    for (int i = 0; i < structs->lengths[0]; i++)
    {
        if (fscanf(file, "%d,%49[^,],%d,%d", 
                   &structs->students[i].student_id,
                   structs->students[i].name,
                   &structs->students[i].age,
                   &structs->students[i].count_courses) != 4)
        {
            fclose(file);
            for (int j = 0; j < i; j++)
                free(structs->students[j].grades);
            return (0);
        }
        if (!alloc_grades(structs, i))
        {
            fclose(file);
            return (0);
        }
    }
    fclose(file);
    file = fopen("courses.txt", "r");
    if (!file)
        return (0);
    for (int i = 0; i < structs->lengths[1]; i++)
    {
        if (fscanf(file, "%d,%49[^,],%f,%d", 
                   &structs->courses[i].course_id,
                   structs->courses[i].name,
                   &structs->courses[i].average_grade,
                   &structs->courses[i].count_students) != 4)
            return (0);
    }
    fclose(file);
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
    free(structs->schools);
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
        printf("allocation failed\n");
        return (0);
    }
    if (!read_files(structs))
    {
        printf("read files failed\n");
        return (0);
    }
    return (1);
}

int restore_data(Structs *structs)
{
    FILE *file;

    file = fopen("students.txt", "w");
    if (!file)
        return (0);
    for (int i = 0; i < structs->lengths[0]; i++)
    {
        if (structs->students[i].student_id >= 0)
        {
            fprintf(file, "%d,%s,%d,%d\n",
            structs->students[i].student_id,
            structs->students[i].name,
            structs->students[i].age,
            structs->students[i].count_courses);
        }
    }
    fclose(file);
    file = fopen("courses.txt", "w");
    if (!file)
        return (0);
    for (int i = 0; i < structs->lengths[1]; i++)
    {
        if (structs->courses[i].course_id >= 0)
        {
            fprintf(file, "%d,%s,%f,%d\n",
            structs->courses[i].course_id,
            structs->courses[i].name,
            structs->courses[i].average_grade,
            structs->courses[i].count_students);
        }
    }
    fclose(file);
    return (1);
}
