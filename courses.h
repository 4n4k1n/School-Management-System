#ifndef COURSES_H
#define COURSES_H

#include "structs.h"

void print_course(Course *course);
void print_one_course(Structs *structs);
void get_course_data(Structs *structs);
void add_course(Structs *structs);
void remove_student_from_course(Student *student, int course_id);
void remove_course(Structs *structs);
void print_all_courses(Structs *structs);

#endif