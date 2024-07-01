#ifndef _bubble_sort_h
#define _bubble_sort_h

#include "array.h"

typedef int(*cmp_f)(void *a, void *b);
void bubble_sort(array *_array, cmp_f cmp);

#endif
