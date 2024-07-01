#ifndef _selection_sort_h
#define _selection_sort_h

#include "array.h"

typedef int(*cmp_f)(void *a, void *b);
void selection_sort(array *_array, cmp_f cmp);

#endif
