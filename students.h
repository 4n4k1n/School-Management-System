#ifndef STUDENTS_H
#define STUDENTS_H

#include "structs.h"
#include <stdio.h>

Student *alloc_students_struct(int size);
void load_student_data(FILE *file, Student *students, int size);
void print_student(const Student *student);
void get_student_data(Student *student, int size);
void f_put_student_data(Student *student, int size);
Student *add_student(Student *students, int *size);

#endif