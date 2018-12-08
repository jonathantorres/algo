#ifndef _insertion_sort_h
#define _insertion_sort_h

#include "array.h"

typedef int(*cmp_f)(void *a, void *b);
void insertion_sort(array *_array, cmp_f cmp);

#endif
