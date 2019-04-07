#ifndef _binary_search_h
#define _binary_search_h

#include "array.h"

typedef int(*cmp_f)(void *a, void *b);
void *binary_search(array *_array, void *key, cmp_f cmp);

#endif
