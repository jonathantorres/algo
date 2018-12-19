#include <stdlib.h>
#include <stdio.h>
#include "htable.h"

htable *htable_create(htable_compare cmp)
{
    htable *_htable = malloc(sizeof(htable));

    if (!_htable) {
        fputs("Not enough memory.", stderr);
        exit(EXIT_FAILURE);
    }

    _htable->cmp = cmp;
    _htable->buckets = array_create(NUM_OF_BUCKETS, sizeof(array*));

    return _htable;
}
