#ifndef STUDENTS_H
#define STUDENTS_H

#include "structs.h"
#include <stdio.h>

int fcountl(FILE *file);
Student *alloc_students_struct(int size);
void load_student_data(FILE *file, Student *students, int size);
void print_student_by_id(Student student);
void get_student_data(Student *student, int size);
void f_put_student_data(Student *student, int size);
Student *add_student(Student *students, int *size);

#endif