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
        fclose(files[0]);
    files[2] = fopen("schools.txt", "r");
    if (!files[2])
    {
        fclose(files[0]);
        fclose(files[1]);
    }
    if (!files[0] || !files[1] || !files[2])
        return (0);
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
        free(structs->students);
    structs->schools = (School *)malloc(sizeof(School) * structs->lengths[2]);
    if (!structs->schools)
    {
        free(structs->students);
        free(structs->courses);
    }
    if (!structs->students || !structs->courses || !structs->schools)
        return (0);
    return (1);
}

int alloc_grades(Structs *structs, int index)
{
    structs->students[index].grades = (Grade *)malloc(sizeof(Grade) * structs->students->count_courses);
    if (!structs->students[index].grades)
    {
        for (int i = index - 1; i >= 0; i--)
            free(structs->students[i].grades);
        return (0);
    }
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
        if (fscanf(file, "%d,%49[^,],%d,%d", &structs->students[i].student_id, structs->students[i].name, &structs->students[i].age, &structs->students[i].count_courses) != 4)
            return (0);
        if (!alloc_grades(structs, i))
            return (0);
    }
}

int load_data(Structs *structs)
{
    if (!get_lens(structs))
        return (0);
    if (!alloc_structs(structs))
        return (0);
    if (!read_files(structs))
        return (0);
    retrun (1);
}

void free_struct(Structs *structs)
{
    for (int i = 0; i < structs->lengths[0]; i++)
    {
        if (structs->students[grades->grade)
            free(structs->students->grades->grade);
        if (structs->students->grades)
            free(structs->students->grades);
        if (structs->students)
    }
}

int main(void)
{
    Structs structs;

    if (!load_data(&structs))
        return (1);
    return 0;
}
