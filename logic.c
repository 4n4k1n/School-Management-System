#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "students.h"
#include "courses.h"
#include "data.h"

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
        print_one_student(structs);
        break;
    case (4):
        print_all_students(structs);
        break;
    case (5):
        add_course(structs);
        break;
    case (6):
        remove_course(structs);
        break;
    case (7):
        print_one_course(structs);
        break;
    case (8):
        print_all_courses(structs);
        break;
    default:
        break;
    }
}

void print_menu(void)
{
    system("clear");
    printf("0 >> End program\n");
    printf("1 >> Add student\n");
    printf("2 >> Remove student\n");
    printf("3 >> Print student\n");
    printf("4 >> Print all students\n");
    printf("5 >> Add course\n");
    printf("6 >> Remove course\n");
    printf("7 >> Print one course\n");
    printf("8 >> Print all courses\n");
}
