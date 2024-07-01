#ifndef _quick_sort_h
#define _quick_sort_h

#include "array.h"

typedef int(*cmp_f)(void *a, void *b);
void quick_sort(array *_array, cmp_f cmp);

#endif
