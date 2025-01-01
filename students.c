#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include <string.h>

void print_student(Student *student)
{
    if (!student)
        return;
    printf("ID      : %d\n", student->student_id);
    printf("NAME    : %s\n", student->name);
    printf("AGE     : %d\n", student->age);
    printf("COURSES : %d\n\n", student->count_courses);
}

void print_one_student(Structs *structs)
{
    char name[50];
    int found;

    found = 0;
    printf("Enter student name: ");
    scanf(" %49[^\n]", name); 
    for (int i = 0; i < structs->lengths[0]; i++)
    {
        if (strcmp(name, structs->students[i].name) == 0 && structs->students[i].student_id >= 0)
        {
            found = 1;
            print_student(&structs->students[i]);
            break;
        }
    }
    if (!found)
        printf("Student not found!\n\n");
    printf("Press any key to continue...\n");
    getchar();
    getchar();
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

void add_student(Structs *structs)
{
    FILE *file;
    char file_name[30];

    structs->lengths[0]++;
    structs->students = (Student *)realloc(structs->students, sizeof(Student) * structs->lengths[0]);
    if (structs->students == NULL)
        return;
    get_student_data(structs);
    sprintf(file_name, "grades/%d.txt", (structs->lengths[0] - 1));
    file = fopen(file_name, "w");
    fclose(file);
    printf("Student was added successfully\n");
    printf("Press any key to continue...\n");
    getchar();
    getchar();
}

void remove_student_file(Structs *structs, int index)
{
    char filename[30];
    char new_filename[30];

    snprintf(filename, sizeof(filename), "grades/%d.txt", index);
    if (remove(filename) != 0)
    {
        printf("Error deleting file\n");
        return;
    }
    for (int i = index + 1; i < structs->lengths[0]; i++)
    {
        snprintf(filename, sizeof(filename), "grades/%d.txt", i);
        snprintf(new_filename, sizeof(new_filename), "grades/%d.txt", i - 1);
        if (rename(filename, new_filename) != 0)
            printf("Error renaming file!\n");
    }
}

void remove_student(Structs *structs)
{
    char name[50];
    int found = 0;

    printf("Enter student name: ");
    scanf(" %49[^\n]", name);
    for (int i = 0; i < structs->lengths[0]; i++)
    {
        if (strcmp(name, structs->students[i].name) == 0 && structs->students[i].student_id >= 0)
        {
            found = 1;
            remove_student_file(structs, i);
            structs->students[i].student_id = -1;
            for (int j = i + 1; j < structs->lengths[0]; j++)
            {
                if (structs->students[j].student_id >= 0)
                    structs->students[j].student_id--;
            }
            break;
        }
    }
    if (!found)
        printf("Student not found!\n");
    else
        printf("Student removed successfully.\n");
    printf("Press Enter to continue...");
    getchar();
    getchar();
}


void print_all_students(Structs *structs)
{
    int count;

    count = 0;
    if (structs->lengths[0] > 0)
    {
        for (int i = 0; i < structs->lengths[0]; i++)
        {
            if (structs->students[i].student_id >= 0)
            {
                count++;
                print_student(&structs->students[i]);
            }
        }
    }
    else if (count > 0)
        printf("No students to print!\n");
    printf("Press any key to continue...\n");
    getchar();
    getchar();
}
