#include <string.h>
#include <stdbool.h>
#include "unittest.h"
#include "trie.h"

int trie_cmp_fn(void *a, void *b)
{
    return strcmp((char*)a, (char*)b);
}

char *test_create()
{
    trie *_trie = trie_new(trie_cmp_fn);
    assert(_trie != NULL, "The trie should not be NULL");
    assert(_trie->root != NULL, "The root of the trie should not be NULL");
    assert(_trie->cmp == trie_cmp_fn, "The comparison function for the trie cannot be set");
    trie_free(_trie);

    return NULL;
}

char *test_destroy()
{
    trie *_trie = trie_new(trie_cmp_fn);
    trie_insert(_trie, "john", "Jonathan Torres");
    trie_insert(_trie, "luis", "Jorge L Torres");
    trie_insert(_trie, "chris", "Christopher Torres");
    trie_insert(_trie, "mar", "Marjory Torres");
    trie_free(_trie);

    return NULL;
}

char *test_insert()
{
    trie *_trie = trie_new(trie_cmp_fn);
    bool success = trie_insert(_trie, "john", "Jonathan Torres");
    assert(success == true, "They key 'john' was not inserted succesfully");
    success = trie_insert(_trie, "luis", "Jorge L Torres");
    assert(success == true, "They key 'luis' was not inserted succesfully");
    success = trie_insert(_trie, "chris", "Christopher Torres");
    assert(success == true, "They key 'chris' was not inserted succesfully");
    success = trie_insert(_trie, "mar", "Marjory Torres");
    assert(success == true, "They key 'mar' was not inserted succesfully");
    trie_free(_trie);

    return NULL;
}

int main()
{
    start_tests("trie tests");
    run_test(test_create);
    run_test(test_destroy);
    run_test(test_insert);
    end_tests();

    return 0;
}
