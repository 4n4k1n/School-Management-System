#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "structs.h"
#include "students.h"
#include "courses.h"
#include "data.h"
#include "logic.h"
#include "fail.h"

int main(void)
{
    Structs structs = {0};
    int input;
    
    if (!load_data(&structs))
    {
        fail_protocol(&structs);
        return (1);
    }
    input = -1;
    while (input != 0)
    {
        print_menu();
        printf("\nEnter acitivity: ");
        scanf("%d", &input);
        do_input(input, &structs);
    }
    free_struct(&structs);
    return (0);
}
