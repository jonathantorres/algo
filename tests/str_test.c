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

int main(void)
{
    start_tests("str tests");
    run_test(test_create_empty_string);
    run_test(test_create_string);
    run_test(test_free);
    end_tests();
    return 0;
}
