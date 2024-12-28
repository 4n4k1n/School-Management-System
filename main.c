#include <stdlib.h>
#include <stdio.h>
#include "student_struct.h"
#include "students.h"

int main(void)
{
    Student *students;
    FILE *file;
    int lines;

    file = fopen("students.txt", "r");
    if (!file)
    {
        perror("Error opening file");
        return 1;
    }
    lines = fcountl(file);
    rewind(file);
    students = alloc_students_struct(lines);
    if (!students)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return 1;
    }
    load_student_data(file, students, lines);
    fclose(file);
    students = add_student(students, &lines);
    printf("%d", lines);
    for (int i = 0; i < lines; i++)
    {
        print_student_by_id(students[i]);
    }
    free(students);
    return 0;
}
