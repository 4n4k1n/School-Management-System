#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct
{
    int grade_id;
    int course_id;
    float *grade;
    int count_grades;
    float average_grade;
} Grade;

typedef struct
{
    int student_id;
    char name[50];
    int age;
    int count_courses;
    Grade *grades;
} Student;

typedef struct
{
    int course_id;
    char name[50];
    float average_grade;
    int count_students;
    int *students_ids;
} Course;

typedef struct
{
    Student *students;
    Course *courses;
    int lengths[2];
} Structs;

#endif
