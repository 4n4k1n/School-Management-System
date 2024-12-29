#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "students.h"

int get_lens(Structs *structs)
{
    FILE *files[3];

    files[0] = fopen("students.txt", "r");
    if (!files[0])
        return (0);
    files[1] = fopen("courses.txt", "r");
    if (!files[1])
    {
        fclose(files[0]);
        return (0);
    }
    files[2] = fopen("schools.txt", "r");
    if (!files[2])
    {
        fclose(files[0]);
        fclose(files[1]);
        return (0);
    }
    structs->lengths[0] = fcountl(files[0]);
    structs->lengths[1] = fcountl(files[1]);
    structs->lengths[2] = fcountl(files[2]);
    fclose(files[0]);
    fclose(files[1]);
    fclose(files[2]);
    return (1);
}

int alloc_structs(Structs *structs)
{
    structs->students = (Student *)malloc(sizeof(Student) * structs->lengths[0]);
    if (!structs->students)
        return (0);
    structs->courses = (Course *)malloc(sizeof(Course) * structs->lengths[1]);
    if (!structs->courses)
    {
        free(structs->students);
        return (0);
    }
    structs->schools = (School *)malloc(sizeof(School) * structs->lengths[2]);
    if (!structs->schools)
    {
        free(structs->students);
        free(structs->courses);
        return (0);
    }
    return (1);
}

int alloc_grades(Structs *structs, int index)
{
    structs->students[index].grades = (Grade *)malloc(sizeof(Grade) * structs->students[index].count_courses);
    if (!structs->students[index].grades)
    {
        for (int i = index - 1; i >= 0; i--)
            free(structs->students[i].grades);
        return (0);
    }
    for (int i = 0; i < structs->students[index].count_courses; i++)
        structs->students[index].grades[i].grade = NULL;
    return (1);
}

int read_files(Structs *structs)
{
    FILE *file;

    file = fopen("students.txt", "r");
    if (!file)
        return (0);
    for (int i = 0; i < structs->lengths[0]; i++)
    {
        if (fscanf(file, "%d,%49[^,],%d,%d", 
                   &structs->students[i].student_id, structs->students[i].name,
                   &structs->students[i].age, &structs->students[i].count_courses) != 4)
        {
            fclose(file);
            for (int j = 0; j < i; j++)
                free(structs->students[j].grades);
            return (0);
        }
        if (!alloc_grades(structs, i))
        {
            fclose(file);
            return (0);
        }
    }
    fclose(file);
    return (1);
}

void free_struct(Structs *structs)
{
    if (structs->students)
    {
        for (int i = 0; i < structs->lengths[0]; i++)
        {
            if (structs->students[i].grades)
            {
                for (int j = 0; j < structs->students[i].count_courses; j++)
                    free(structs->students[i].grades[j].grade);
                free(structs->students[i].grades);
            }
        }
        free(structs->students);
    }
    free(structs->courses);
    free(structs->schools);
}

void print_student(const Student *student)
{
    if (!student)
        return;
    printf("ID: %d\n", student->student_id);
    printf("NAME: %s\n", student->name);
    printf("AGE: %d\n", student->age);
    printf("COURSES: %d\n\n", student->count_courses);
}

int main(void)
{
    Structs structs = {0};
    
    if (!load_data(&structs))
        return (1);
    if (structs.lengths[0] > 0)
    {
        for (int i = 0; i < structs.lengths[0]; i++)
            print_student(&structs.students[0]);
    }
    free_struct(&structs);
    return (0);
}
