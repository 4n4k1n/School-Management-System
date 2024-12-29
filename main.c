#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "students.h"
#include "data.h"

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
