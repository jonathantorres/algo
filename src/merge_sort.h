#ifndef _merge_sort_h
#define _merge_sort_h

#include "array.h"

typedef int(*cmp_f)(void *a, void *b);
void merge_sort(array *_array, cmp_f cmp);

#endif
