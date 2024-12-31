#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include <string.h>

void print_course(Course *course)
{
    if (!course)
        return;
    printf("ID            : %d\n", course->course_id);
    printf("NAME          : %s\n", course->name);
    printf("AVERAGE GRADE : %.2f\n", course->average_grade);
    printf("STUDENTS      : %d\n\n", course->count_students);
}

void print_one_course(Structs *structs)
{
    char name[50];
    int found;

    found = 0;
    printf("Enter course name: ");
    scanf(" %49[^\n]", name); 
    for (int i = 0; i < structs->lengths[1]; i++)
    {
        if (strcmp(name, structs->courses[i].name) == 0 && structs->courses[i].course_id >= 0)
        {
            found = 1;
            print_course(&structs->courses[i]);
            break;
        }
    }
    if (!found)
        printf("Course not found!\n\n");
    printf("Press any key to continue...\n");
    getchar();
    getchar();
}

void get_course_data(Structs *structs)
{
    structs->courses[structs->lengths[1] - 1].course_id = structs->lengths[1] - 1;
    structs->courses[structs->lengths[1] - 1].count_students = 0;
    structs->courses[structs->lengths[1] - 1].average_grade  = 0;
    printf("Enter course name: ");
    scanf(" %49[^\n]", structs->courses[structs->lengths[1] - 1].name);
}

void add_course(Structs *structs)
{
    structs->lengths[1]++;
    structs->courses = (Course *)realloc(structs->courses, sizeof(Course) * structs->lengths[1]);
    if (structs->courses == NULL)
    {
        printf("Course creation failed!\n");
        return;
    }
    get_course_data(structs);
    printf("Course was added successfully\n");
    printf("Press any key to continue...\n");
    getchar();
    getchar();
}

void remove_student_from_course(Student *student, int course_id)
{
    for (int i = 0; i < student->count_courses; i++)
    {
        if (student->grades[i].course_id == course_id)
        {
            student->grades[i].grade_id = -1;
            for (int j = 1;  i + j < student->count_courses; j++)
            {
                if (student->grades[i + j].grade_id >= 0)
                    student->grades[i + j].grade_id--;
            }
            break;
        }
    }
}

void remove_course(Structs *structs)
{
    char name[50];
    int found;

    found = 0;
    printf("Enter course name: ");
    scanf(" %49[^\n]", name); 
    for (int i = 0; i < structs->lengths[1]; i++)
    {
        if (strcmp(name, structs->courses[i].name) == 0 && structs->courses[i].course_id >= 0)
        {
            found = 1;
            for (int k = 0; k < structs->courses->count_students; k++)
                remove_student_from_course(&structs->students[structs->courses[i].students_ids[k]], structs->courses[i].course_id);
            structs->courses[i].course_id = -1;
            for (int j = 1;  i + j < structs->lengths[1]; j++)
            {
                if (structs->courses[i + j].course_id >= 0)
                    structs->courses[i + j].course_id--;
            }
            printf("Course removed!\n\n");
            break;
        }
    }
    if (!found)
        printf("Course not found!\n\n");
    printf("Press any key to continue...\n");
    getchar();
    getchar();
}

void print_all_courses(Structs *structs)
{
    int count;

    count = 0;
    if (structs->lengths[1] > 0)
    {
        for (int i = 0; i < structs->lengths[1]; i++)
        {
            if (structs->courses[i].course_id >= 0)
            {
                count++;
                print_course(&structs->courses[i]);
            }
        }
    }
    else if (count > 0)
        printf("No Courses to print!\n");
    printf("Press any key to continue...\n");
    getchar();
    getchar();
}
