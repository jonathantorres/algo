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

int main(void)
{
    start_tests("str tests");
    run_test(test_create_empty_string);
    run_test(test_create_string);
    run_test(test_free);
    run_test(test_len);
    run_test(test_get_string);
    run_test(test_str_concat);
    end_tests();
    return 0;
}
