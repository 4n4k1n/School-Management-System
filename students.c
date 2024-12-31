#include <stdlib.h>
#include <stdio.h>
#include "structs.h"

Student *alloc_students_struct(int size)
{
    Student *students;

    students = (Student *)malloc(sizeof(Student) * size);
    if (!students)
        return (NULL);
    return (students);
}

void load_student_data(FILE *file, Student *students, int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        if (fscanf(file, "%d,%49[^,],%d", &students[i].student_id, students[i].name, &students[i].age) != 3)
            return;
        i++;
    }
}

void print_student(Student *student)
{
    if (!student)
        return;
    printf("ID      : %d\n", student->student_id);
    printf("NAME    : %s\n", student->name);
    printf("AGE     : %d\n", student->age);
    printf("COURSES : %d\n\n", student->count_courses);
}

void get_student_data(Structs *structs)
{
    structs->students[structs->lengths[0] - 1].student_id = structs->lengths[0] - 1;
    structs->students[structs->lengths[0] - 1].count_courses = 0;
    structs->students[structs->lengths[0] - 1].grades = NULL;
    printf("Enter student name: ");
    scanf(" %49[^\n]", structs->students[structs->lengths[0] - 1].name);
    printf("Enter student age: ");
    scanf("%d", &structs->students[structs->lengths[0] - 1].age);
}

void f_put_student_data(Student *student, int size)
{
    FILE *file;

    file = fopen("students.txt", "a");
    fprintf(file, "%d,%s,%d,%d\n", (student[size - 1]).student_id, (student[size - 1]).name, (student[size - 1]).age, student[size - 1].count_courses);
    fclose(file);
}

void add_student(Structs *structs)
{
    structs->lengths[0]++;
    structs->students = (Student *)realloc(structs->students, sizeof(Student) * structs->lengths[0]);
    if (structs->students == NULL)
        return;
    get_student_data(structs);
}
