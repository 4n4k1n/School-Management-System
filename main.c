#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "students.h"
#include "data.h"
#include <unistd.h>

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
}

void remove_student(Structs *structs)
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
            printf("Student removed!\n\n");
            found = 1;
            structs->students[i].student_id = -1;
            for (int j = 1;  i + j < structs->lengths[0]; j++)
            {
                if (structs->students[i + j].student_id >= 0)
                    structs->students[i + j].student_id--;
            }
            break;
        }
    }
    if (!found)
        printf("Student not found!\n\n");
    printf("Press any key to continue...\n");
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
            fprintf(file, "%d,%s,%d,%d\n", structs->students[i].student_id, structs->students[i].name, structs->students[i].age, structs->students[i].count_courses);
    }
    return (1);
}

void do_input(int input, Structs *structs)
{
    system("clear");
    switch (input)
    {
    case (0):
        restore_data(structs);
        break;
    case (1):
        add_student(structs);
        break;
    case (2):
        remove_student(structs);
        break;
    case (3):
        print_all_students(structs);
        break;
    }
}

void print_menu(void)
{
    system("clear");
    printf("0 >> End program\n");
    printf("1 >> Add student\n");
    printf("2 >> Remove student\n");
    printf("3 >> Print all students\n");
}

int main(void)
{
    Structs structs = {0};
    int input;
    
    if (!load_data(&structs))
    {
        printf("data can not load\n");
        return (1);
    }
    input = -1;
    while (input != 0)
    {
        print_menu();
        printf("\nEnter acitivity:");
        scanf("%d", &input);
        do_input(input, &structs);
        getchar();
        getchar();
    }
    free_struct(&structs);
    return (0);
}
