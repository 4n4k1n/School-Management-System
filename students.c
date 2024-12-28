#include <stdlib.h>
#include <stdio.h>
#include "student_struct.h"

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

void print_student_by_id(Student student)
{
    printf("ID  : %d\n", student.student_id);
    printf("NAME: %s\n", student.name);
    printf("AGE : %d\n\n", student.age);
}

void get_student_data(Student *student, int size)
{
    student[size - 1].student_id = size;
    printf("Enter student name: ");
    scanf(" %49[^\n]", student[size - 1].name);
    printf("Enter student age: ");
    scanf("%d", &student[size - 1].age);
}

void f_put_student_data(Student *student, int size)
{
    FILE *file;

    file = fopen("students.txt", "a");
    fprintf(file, "%d,%s,%d\n", (student[size - 1]).student_id, (student[size - 1]).name, (student[size - 1]).age);
    fclose(file);
}

Student *add_student(Student *students, int *size)
{
    (*size)++;
    Student *new_students = (Student *)realloc(students, sizeof(Student) * (*size));
    if (new_students == NULL)
        return students;
    get_student_data(new_students, *size);
    f_put_student_data(new_students, (*size));
    return new_students;
}
