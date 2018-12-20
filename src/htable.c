#include <stdlib.h>
#include <stdio.h>
#include "htable.h"

size_t fnv1a_hash(const char* cp)
{
    size_t hash = 0x811c9dc5;
    while (*cp) {
        hash ^= (unsigned char) *cp++;
        hash *= 0x01000193;
    }

    return hash;
}

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

void htable_destroy(htable *_htable)
{
    if (!_htable) {
        fputs("Must provide a hashtable.", stderr);
        exit(EXIT_FAILURE);
    }

    if (_htable->buckets) {
        for (unsigned int i = 0; i < _htable->buckets->length; i++) {
            void *bucket = array_get(_htable->buckets, i);
            if (bucket) {
                array_destroy(bucket);
            }
        }
        array_destroy(_htable->buckets);
    }
    free(_htable);
}

unsigned int htable_set(htable *_htable, void *key, void *value)
{
    if (!_htable) {
        fputs("Must provide a hashtable.", stderr);
        exit(EXIT_FAILURE);
    }

    unsigned int bucket_index = fnv1a_hash(key) % NUM_OF_BUCKETS;
    if (bucket_index >= NUM_OF_BUCKETS || bucket_index <= 0) {
        return 1;
    }

    void *bucket = array_get(_htable->buckets, bucket_index);
    if (!bucket) {
        bucket = array_create(NUM_OF_BUCKETS, sizeof(htable_node*));
        array_set(_htable->buckets, bucket, bucket_index);
    }
    // create the node
    // push the node into the bucket
}





