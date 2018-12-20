#include <string.h>
#include "unittest.h"
#include "htable.h"

int htable_compare_fn(void *a, void *b)
{
    return strcmp((char*)a, (char*)b);
}

char *test_create()
{
    htable *_htable = htable_create(htable_compare_fn);
    assert(_htable != NULL, "Hashtable cannot be NULL");
    assert(_htable->cmp == htable_compare_fn, "Hashtable must use the correct compare function");
    assert(_htable->buckets != NULL, "Hashtable buckets cannot be NULL");
    htable_destroy(_htable);

    return NULL;
}

char *test_destroy()
{
    htable *_htable = htable_create(htable_compare_fn);
    htable_destroy(_htable);

    return NULL;
}

int main()
{
    start_tests("hash table tests");
    run_test(test_create);
    run_test(test_destroy);
    end_tests();

    return 0;
}
