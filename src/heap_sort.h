#ifndef _heap_sort_h
#define _heap_sort_h

#include "array.h"
#include "p_queue.h"

typedef int(*cmp_f)(void *a, void *b);
void heap_sort(array *_array, cmp_f cmp);

#endif
