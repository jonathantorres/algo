#include <string.h>
#include "str.h"
#include "unittest.h"

char *test_create_empty_string()
{
    str *_str = str_new("");
    assert(_str != NULL, "_str should not be NULL");
    assert(_str->len == 0, "The len of _str should be 0");
    assert(_str->string != NULL, "The string should not be NULL");
    assert(strcmp(_str->string, "") == 0, "The string should be empty");
    str_free(_str); 
    return NULL;
}

char *test_create_string()
{
    str *_str = str_new("Jonathan Torres");
    assert(_str->len == 15, "The length of _str should be 15");
    assert(strcmp(_str->string, "Jonathan Torres") == 0, "The strings do not match");
    str_free(_str);
    return NULL;
}

char *test_free()
{
    str *_str = str_new("");
    str_free(_str);
    return NULL;
}

char *test_len()
{
    str *_str = str_new("Jonathan");
    assert(_str->len == 8, "The len of the string should be 8");
    str_free(_str);
    return NULL;
}

char *test_get_string()
{
    str *_str = str_new("Jonathan");
    char *string = str_get_string(_str);
    assert(string != NULL, "The string should not be NULL");
    assert(strlen(string) == (unsigned long)_str->len, "The lengths of str and the string should be equal");
    str_free(_str);
    return NULL;
}

char *test_str_concat()
{
    str *_str = str_new("Jonathan");
    _str = str_concat(_str, " Torres");
    assert(_str != NULL, "The string should not be NULL");
    assert(_str->len == 15, "The len of the string should be 15");
    assert(strcmp(_str->string, "Jonathan Torres") == 0, "The strings should be equal");
    str_free(_str);
    return NULL;
}

char *test_concat_str()
{
    str *_str = str_new("Jonathan");
    str *new_chars = str_new(" Torres");
    _str = str_concat_str(_str, new_chars);
    assert(_str != NULL, "The string should not be NULL");
    assert(_str->len == 15, "The len of the string should be 15");
    assert(strcmp(_str->string, "Jonathan Torres") == 0, "The strings should be equal");
    str_free(_str);
    str_free(new_chars);
    return NULL;
}

char *test_str_contains()
{
    str *_str = str_new("Jonathan");
    bool found = str_contains(_str, "ona");
    assert(found == true, "Found should be true");
    found = str_contains(_str, "ola");
    assert(found == false, "Found should be false");
    str_free(_str);
    return NULL;
}

char *test_contains_str()
{
    str *_str1 = str_new("Jonathan");
    str *_str2 = str_new("ona");
    str *_str3 = str_new("ola");
    bool found = str_contains_str(_str1, _str2);
    assert(found == true, "Found should be true");
    found = str_contains_str(_str1, _str3);
    assert(found == false, "Found should be false");
    str_free(_str1);
    str_free(_str2);
    str_free(_str3);
    return NULL;
}

char *test_str_has_prefix()
{
    str *_str = str_new("Jonathan");
    bool haspre = str_has_prefix(_str, "Jon");
    assert(haspre == true, "Has prefix should be true");
    haspre = str_has_prefix(_str, "lola");
    assert(haspre == false, "The lola prefix should be false");
    haspre = str_has_prefix(_str, "nath");
    assert(haspre == false, "The nath prefix should be false");
    str_free(_str);
    return NULL;
}

char *test_str_has_prefix_str()
{
    str *_str1 = str_new("Jonathan");
    str *_str2 = str_new("Jon");
    str *_str3 = str_new("lola");
    str *_str4 = str_new("nath");
    bool haspre = str_has_prefix_str(_str1, _str2);
    assert(haspre == true, "Has prefix should be true");
    haspre = str_has_prefix_str(_str1, _str3);
    assert(haspre == false, "The lola prefix should be false");
    haspre = str_has_prefix_str(_str1, _str4);
    assert(haspre == false, "The nath prefix should be false");
    str_free(_str1);
    str_free(_str2);
    str_free(_str3);
    str_free(_str4);
    return NULL;
}

int main(void)
{
    start_tests("str tests");
    run_test(test_create_empty_string);
    run_test(test_create_string);
    run_test(test_free);
    run_test(test_len);
    run_test(test_get_string);
    run_test(test_str_concat);
    run_test(test_concat_str);
    run_test(test_str_contains);
    run_test(test_contains_str);
    run_test(test_str_has_prefix);
    run_test(test_str_has_prefix_str);
    end_tests();
    return 0;
}
