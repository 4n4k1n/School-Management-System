#ifndef STUDENTS_H
#define STUDENTS_H

#include "structs.h"
#include <stdio.h>

void print_student(Student *student);
void print_one_student(Structs *structs);
void get_student_data(Student *student, int size);
Student *add_student(Structs *structs);
void remove_student(Structs *structs);
void print_all_students(Structs *structs);

#endif