#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

void read_str(char *str, FILE *file, char search)
{
    int j;
    char ch;

    j = 0;
    while ((ch = fgetc(file)) != search)
        str[j++] = ch;
    str[j] = '\0';
}


void read_int(int *var, FILE *file)
{
    int num;
    char ch;

    num = 0;
    while ((ch = fgetc(file)) != ',')
        num = ((num * 10) + (ch - '0'));
    *var = num;
}

void read_grades(Grade *grades, FILE *file)
{
    char ch;
    float grade;

    for (int i = 0; i < grades->count_grades; i++)
    {
        grade = 0.0;
        while (((ch = fgetc(file)) != ','))
        {
            if (ch != '.')
                grade = ((grade * 10) + (ch - '0'));
        }
        grade = grade / 10;
        grades->grade[i] = grade;
    }
}

void fill_grades(Structs *structs, FILE *file, int i, int k)
{
    int num;

    read_int(&num, file);
    structs->students[i].grades[k].course_id = num;
    structs->courses[num].students_ids[structs->courses[num].i] = structs->students[i].student_id;
    structs->courses[num].i++;
    read_int(&structs->students[i].grades[k].count_grades, file);
    if (structs->students[i].grades[k].count_grades > 0)
        structs->students[i].grades[k].grade = (float *)malloc(sizeof(float) * structs->students[i].grades[k].count_grades);
    else
        structs->students[i].grades[k].grade = NULL;
    read_grades(&structs->students[i].grades[k], file);
}

int read_students(Structs *structs)
{
    FILE *file;
    char ch;

    file = fopen("students.txt", "r");
    if (!file)
        return 0;
    for (int i = 0; i < structs->lengths[0]; i++)
    {
        read_int(&structs->students[i].student_id, file);
        read_str(structs->students[i].name, file, ',');
        read_int(&structs->students[i].age, file);
        read_int(&structs->students[i].count_courses, file);
        structs->students[i].grades = (Grade *)malloc(sizeof(Grade) * structs->students[i].count_courses);
        if (!structs->students[i].grades)
        {
            fclose(file);
            return 0;
        }
        for (int k = 0; k < structs->students[i].count_courses; k++)
            fill_grades(structs, file, i, k);
        while ((ch = fgetc(file)) != '\n' && ch != EOF);
    }
    fclose(file);
    return 1;
}


int read_courses(Structs *structs)
{
    FILE *file;

    file = fopen("courses.txt", "r");
    if (!file)
    {
        return (0);
    }
    for (int i = 0; i < structs->lengths[1]; i++)
    {
        if (fscanf(file, "%d,%49[^,],%f,%d", 
                   &structs->courses[i].course_id,
                   structs->courses[i].name,
                   &structs->courses[i].average_grade,
                   &structs->courses[i].count_students) != 4)
            return (0);
        structs->courses[i].i = 0;
    }
    fclose(file);
    return (1);
}

int read_files(Structs *structs)
{
    if (!read_courses(structs))
        return (0);
    else if (!read_students(structs))
        return (0);
    return (1);
}
