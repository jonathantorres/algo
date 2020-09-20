#include <string.h>
#include <stdbool.h>
#include "unittest.h"
#include "trie.h"

void trie_traverse_cb(void *value)
{
    printf("%s\n", (char*)value);
}

char *test_create()
{
    trie *_trie = trie_new();
    assert(_trie != NULL, "The trie should not be NULL");
    assert(_trie->root != NULL, "The root of the trie should not be NULL");
    trie_free(_trie, NULL);

    return NULL;
}

char *test_destroy()
{
    trie *_trie = trie_new();
    trie_insert(_trie, "john", "Jonathan Torres");
    trie_insert(_trie, "luis", "Jorge L Torres");
    trie_insert(_trie, "chris", "Christopher Torres");
    trie_insert(_trie, "mar", "Marjory Torres");
    trie_free(_trie, NULL);

    return NULL;
}

char *test_insert()
{
    trie *_trie = trie_new();
    bool success = trie_insert(_trie, "john", "Jonathan Torres");
    assert(success == true, "They key 'john' was not inserted succesfully");
    success = trie_insert(_trie, "luis", "Jorge L Torres");
    assert(success == true, "They key 'luis' was not inserted succesfully");
    success = trie_insert(_trie, "chris", "Christopher Torres");
    assert(success == true, "They key 'chris' was not inserted succesfully");
    success = trie_insert(_trie, "mar", "Marjory Torres");
    assert(success == true, "They key 'mar' was not inserted succesfully");
    trie_free(_trie, NULL);

    return NULL;
}

char *test_get_strings()
{
    trie *_trie = trie_new();
    trie_insert(_trie, "basket", "This is a string");
    trie_insert(_trie, "basketball", "This is another string");
    trie_insert(_trie, "wastebasket", "Wastebasket stuff");
    trie_insert(_trie, "baskets", "A lot of baskets");

    char *res1 = trie_get(_trie, "basket");
    assert(strcmp(res1, "This is a string") == 0, "Strings are not the same for res1");
    char *res2 = trie_get(_trie, "basketball");
    assert(strcmp(res2, "This is another string") == 0, "Strings are not the same for res2");
    char *res3 = trie_get(_trie, "wastebasket");
    assert(strcmp(res3, "Wastebasket stuff") == 0, "Strings are not the same for res3");
    char *res4 = trie_get(_trie, "baskets");
    assert(strcmp(res4, "A lot of baskets") == 0, "Strings are not the same for res4");
    trie_free(_trie, NULL);

    return NULL;
}

char *test_get_ints()
{
    int val1 = 1;
    int val2 = 2;
    int val3 = 3;
    int val4 = 4;
    trie *_trie = trie_new();
    trie_insert(_trie, "master", &val1);
    trie_insert(_trie, "masters", &val2);
    trie_insert(_trie, "mastErinG", &val3);
    trie_insert(_trie, "Mastered", &val4);

    int *res1 = trie_get(_trie, "master");
    assert(*res1 == val1, "Numbers are not the same for res1");
    int *res2 = trie_get(_trie, "masters");
    assert(*res2 == val2, "Numbers are not the same for res2");
    int *res3 = trie_get(_trie, "mastErinG");
    assert(*res3 == val3, "Numbers are not the same for res3");
    int *res4 = trie_get(_trie, "Mastered");
    assert(*res4 == val4, "Numbers are not the same for res4");
    int *notfound = trie_get(_trie, "nothere");
    assert(notfound == NULL, "notfound should be NULL");
    trie_free(_trie, NULL);

    return NULL;
}

char *test_traversal()
{
    trie *_trie = trie_new();
    trie_insert(_trie, "basket", "My basket");
    trie_insert(_trie, "basketball", "Basketball for playing hoops");
    trie_insert(_trie, "wastebasket", "Wastebasket for the dirty clothes");
    trie_insert(_trie, "baskets", "Many baskets for organizing things");
    trie_traverse(_trie, trie_traverse_cb);
    trie_free(_trie, NULL);

    return NULL;
}

int main()
{
    start_tests("trie tests");
    run_test(test_create);
    run_test(test_destroy);
    run_test(test_insert);
    run_test(test_get_strings);
    run_test(test_get_ints);
    run_test(test_traversal);
    end_tests();

    return 0;
}
