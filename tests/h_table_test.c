#include <string.h>
#include "unittest.h"
#include "h_table.h"

int h_table_compare_fn(void *a, void *b)
{
    return strcmp((char*)a, (char*)b);
}

void h_table_traverse_fn(h_table_node *node)
{
    if (node && node->key && node->value) {
        printf("%s:%s,", (char*)node->key, (char*)node->value);
    }
}

void h_table_free_fn(h_table_node *node)
{
    if (node) {
        // nothing to free here
    }
}

char *test_create()
{
    h_table *_h_table = h_table_new(h_table_compare_fn);
    assert(_h_table != NULL, "Hash_table cannot be NULL");
    assert(_h_table->cmp == h_table_compare_fn, "Hash_table must use the correct compare function");
    assert(_h_table->buckets != NULL, "Hash_table buckets cannot be NULL");
    h_table_free(_h_table, NULL);
    return NULL;
}

char *test_free()
{
    h_table *_h_table = h_table_new(h_table_compare_fn);
    h_table_free(_h_table, NULL);
    return NULL;
}

char *test_set()
{
    h_table *_h_table = h_table_new(h_table_compare_fn);
    h_table_set(_h_table, "john", "Jonathan Torres");
    h_table_set(_h_table, "luis", "Jorge L Torres");
    h_table_set(_h_table, "mar", "Marjory Torres");
    h_table_set(_h_table, "chris", "Christopher Torres");
    h_table_set(_h_table, "chris", "Christopher Torres");

    assert(h_table_get(_h_table, "john") != NULL, "Item john should be on the table");
    assert(h_table_get(_h_table, "luis") != NULL, "Item luis should be on the table");
    assert(h_table_get(_h_table, "mar") != NULL, "Item mar should be on the table");
    assert(h_table_get(_h_table, "chris") != NULL, "Item chris should be on the table");
    h_table_free(_h_table, NULL);

    return NULL;
}

char *test_get()
{
    char *first_key = "john";
    char *second_key = "luis";
    char *first_value = "Jonathan Torres";
    char *second_value = "Jorge L Torres";

    h_table *_h_table = h_table_new(h_table_compare_fn);
    h_table_set(_h_table, first_key, first_value);
    h_table_set(_h_table, second_key, second_value);

    char *value = h_table_get(_h_table, first_key);
    assert(value != NULL, "Value for key 'john' shouldn't be NULL");
    assert(strcmp(value, first_value) == 0, "Value for key 'john' should be 'Jonathan Torres'");
    value = h_table_get(_h_table, second_key);
    assert(value != NULL, "Value for key 'luis' shouldn't be NULL");
    assert(strcmp(value, second_value) == 0, "Value for key 'luis' should be 'Jorge L Torres'");
    value = h_table_get(_h_table, "foo");
    assert(value == NULL, "Value for key 'foo' should be NULL");
    h_table_free(_h_table, NULL);

    return NULL;
}

char *test_remove()
{
    char *first_key = "john";
    char *second_key = "luis";
    char *first_value = "Jonathan Torres";
    char *second_value = "Jorge L Torres";

    h_table *_h_table = h_table_new(h_table_compare_fn);
    h_table_set(_h_table, first_key, first_value);
    h_table_set(_h_table, second_key, second_value);
    char *value = h_table_remove(_h_table, first_key, NULL);
    assert(value != NULL, "Value for key 'john' could not be removed");
    assert(strcmp(value, first_value) == 0, "Value for the removed key 'john' should be 'Jonathan Torres'");
    value = h_table_get(_h_table, first_key);
    assert(value == NULL, "Value for the removed key 'john' should be NULL");
    h_table_free(_h_table, NULL);

    return NULL;
}

char *test_traverse()
{
    char *first_key = "john";
    char *second_key = "luis";
    char *first_value = "Jonathan Torres";
    char *second_value = "Jorge L Torres";

    h_table *_h_table = h_table_new(h_table_compare_fn);
    h_table_set(_h_table, first_key, first_value);
    h_table_set(_h_table, second_key, second_value);
    h_table_traverse(_h_table, h_table_traverse_fn);
    h_table_free(_h_table, NULL);

    return NULL;
}

int main()
{
    start_tests("hash table tests");
    run_test(test_create);
    run_test(test_free);
    run_test(test_set);
    run_test(test_get);
    run_test(test_remove);
    run_test(test_traverse);
    end_tests();

    return 0;
}
