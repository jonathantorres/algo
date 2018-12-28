#include <string.h>
#include "unittest.h"
#include "trie.h"

int trie_cmp_fn(void *a, void *b)
{
    return strcmp((char*)a, (char*)b);
}

char *test_create()
{
    trie *_trie = trie_create(trie_cmp_fn);
    assert(_trie != NULL, "The trie should not be NULL");
    assert(_trie->root != NULL, "The root of the trie should not be NULL");
    assert(_trie->cmp == trie_cmp_fn, "The comparison function for the trie cannot be set");
    trie_destroy(_trie);

    return NULL;
}

char *test_destroy()
{
    trie *_trie = trie_create(trie_cmp_fn);
    trie_insert(_trie, "john", "Jonathan Torres");
    trie_insert(_trie, "luis", "Jorge L Torres");
    trie_insert(_trie, "chris", "Christopher Torres");
    trie_insert(_trie, "mar", "Marjory Torres");
    trie_destroy(_trie);

    return NULL;
}

char *test_insert()
{
    trie *_trie = trie_create(trie_cmp_fn);
    unsigned int rc = trie_insert(_trie, "john", "Jonathan Torres");
    assert(rc == 0, "They key 'john' was not inserted succesfully");
    rc = trie_insert(_trie, "luis", "Jorge L Torres");
    assert(rc == 0, "They key 'luis' was not inserted succesfully");
    rc = trie_insert(_trie, "chris", "Christopher Torres");
    assert(rc == 0, "They key 'chris' was not inserted succesfully");
    rc = trie_insert(_trie, "mar", "Marjory Torres");
    assert(rc == 0, "They key 'mar' was not inserted succesfully");
    trie_destroy(_trie);

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
