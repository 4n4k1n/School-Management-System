#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include "structs.h"

int fcountl(FILE *file);
int get_lens(Structs *structs);
int alloc_structs(Structs *structs);
int alloc_grades(Structs *structs, int index);
int read_files(Structs *structs);
void free_struct(Structs *structs);
int load_data(Structs *structs);
int restore_data(Structs *structs);

#endif