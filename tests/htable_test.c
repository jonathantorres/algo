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

char *test_set()
{
    htable *_htable = htable_create(htable_compare_fn);
    unsigned int rc = htable_set(_htable, "john", "Jonathan Torres");
    assert(rc == 0, "The 'john' key could not be set");
    rc = htable_set(_htable, "luis", "Jorge L Torres");
    assert(rc == 0, "The 'luis' key could not be set");
    rc = htable_set(_htable, "mar", "Marjory Torres");
    assert(rc == 0, "The 'mar' key could not be set");
    rc = htable_set(_htable, "chris", "Christopher Torres");
    assert(rc == 0, "The 'chris' key could not be set");
    htable_destroy(_htable);

    return NULL;
}

char *test_get()
{
    char *first_key = "john";
    char *second_key = "luis";
    char *first_value = "Jonathan Torres";
    char *second_value = "Jorge L Torres";

    htable *_htable = htable_create(htable_compare_fn);
    unsigned int rc = htable_set(_htable, first_key, first_value);
    assert(rc == 0, "The 'john' key could not be set");
    rc = htable_set(_htable, second_key, second_value);
    assert(rc == 0, "The 'luis' key could not be set");

    char *value = htable_get(_htable, first_key);
    assert(value != NULL, "Value for key 'john' shouldn't be NULL");
    assert(strcmp(value, first_value) == 0, "Value for key 'john' should be 'Jonathan Torres'");
    value = htable_get(_htable, second_key);
    assert(value != NULL, "Value for key 'luis' shouldn't be NULL");
    assert(strcmp(value, second_value) == 0, "Value for key 'luis' should be 'Jorge L Torres'");
    value = htable_get(_htable, "foo");
    assert(value == NULL, "Value for key 'foo' should be NULL");
    htable_destroy(_htable);

    return NULL;
}

char *test_remove()
{
    char *first_key = "john";
    char *second_key = "luis";
    char *first_value = "Jonathan Torres";
    char *second_value = "Jorge L Torres";

    htable *_htable = htable_create(htable_compare_fn);
    htable_set(_htable, first_key, first_value);
    htable_set(_htable, second_key, second_value);
    char *value = htable_remove(_htable, first_key);
    assert(value != NULL, "Value for key 'john' could not be removed");
    assert(strcmp(value, first_value) == 0, "Value for the removed key 'john' should be 'Jonathan Torres'");
    value = htable_get(_htable, first_key);
    assert(value == NULL, "Value for the removed key 'john' should be NULL");
    htable_destroy(_htable);

    return NULL;
}

int main()
{
    start_tests("hash table tests");
    run_test(test_create);
    run_test(test_destroy);
    run_test(test_set);
    run_test(test_get);
    run_test(test_remove);
    end_tests();

    return 0;
}
