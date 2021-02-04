#include <string.h>
#include "str.h"
#include "unittest.h"

void array_of_strs_cb(void *_str)
{
    str *s = (str*)_str;
    str_free(s);
}

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

char *test_str_contains_char()
{
    str *_str = str_new("Jonathan");
    bool found = str_contains_char(_str, 'J');
    assert(found == true, "The character 'J' is in 'Jonathan'");
    found = str_contains_char(_str, 'i');
    assert(found == false, "The character 'i' is not in 'Jonathan'");
    str_free(_str);
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

char *test_str_suffix()
{
    str *_str = str_new("Jonathan");
    bool hassu = str_has_suffix(_str, "han");
    assert(hassu == true, "The suffix han should be true");
    hassu = str_has_suffix(_str, "than");
    assert(hassu == true, "The suffix than should be true");
    hassu = str_has_suffix(_str, "Jona");
    assert(hassu == false, "The suffix Jona should be false");
    hassu = str_has_suffix(_str, "lola");
    assert(hassu == false, "The suffix lola should be false");
    str_free(_str);
    return NULL;
}

char *test_str_suffix_str()
{
    str *_str1 = str_new("Jonathan");
    str *_str2 = str_new("han");
    str *_str3 = str_new("than");
    str *_str4 = str_new("Jona");
    str *_str5 = str_new("lola");
    bool hassu = str_has_suffix_str(_str1, _str2);
    assert(hassu == true, "The suffix han should be true");
    hassu = str_has_suffix_str(_str1, _str3);
    assert(hassu == true, "The suffix than should be true");
    hassu = str_has_suffix_str(_str1, _str4);
    assert(hassu == false, "The suffix Jona should be false");
    hassu = str_has_suffix_str(_str1, _str5);
    assert(hassu == false, "The suffix lola should be false");
    str_free(_str1);
    str_free(_str2);
    str_free(_str3);
    str_free(_str4);
    str_free(_str5);
    return NULL;
}

char *test_str_dup()
{
    char *me = "Jonathan Torres";
    char *new = str_dup(me);
    assert(new != NULL, "The new string should not be NULL");
    assert(strcmp(new, me) == 0, "The new string should be equal to the old one");
    free(new);
    return NULL;
}

char *test_str_dup_str()
{
    str *me = str_new("Jonathan Torres");
    str *new = str_dup_str(me);
    assert(new != NULL, "The new string should not be NULL");
    assert(strcmp(new->string, me->string) == 0, "The new string should be equal to the old one");
    str_free(me);
    str_free(new);
    return NULL;
}

char *test_str_split_by_char()
{
    str *s = str_new("one,two,three");
    array *res = str_split_by_char(s, ',');
    str *cur_s = NULL;
    assert(res->len == 3, "The length of the resulting array should be 3");
    cur_s = array_get(res, 0);
    assert(cur_s != NULL, "The string returned at index 0 should not be NULL");
    assert(strcmp("one", cur_s->string) == 0, "The string at index 0 is not equal to \"one\"");

    cur_s = array_get(res, 1);
    assert(cur_s != NULL, "The string returned at index 1 should not be NULL");
    assert(strcmp("two", cur_s->string) == 0, "The string at index 1 is not equal to \"two\"");

    cur_s = array_get(res, 2);
    assert(cur_s != NULL, "The string returned at index 2 should not be NULL");
    assert(strcmp("three", cur_s->string) == 0, "The string at index 2 is not equal to \"three\"");

    str_free(s);
    array_free(res, array_of_strs_cb);
    return NULL;
}

char *test_str_split_by_char_with_equals()
{
    str *s = str_new("name = localhost");
    array *res = str_split_by_char(s, '=');
    str *cur_s = NULL;
    assert(res->len == 2, "The length of the resulting array should be 2");
    cur_s = array_get(res, 0);
    assert(cur_s != NULL, "The string returned at index 0 should not be NULL");
    assert(strcmp("name ", cur_s->string) == 0, "The string at index 0 is not equal to \"name \"");

    cur_s = array_get(res, 1);
    assert(cur_s != NULL, "The string returned at index 1 should not be NULL");
    assert(strcmp(" localhost", cur_s->string) == 0, "The string at index 1 is not equal to \" localhost\"");

    str_free(s);
    array_free(res, array_of_strs_cb);
    return NULL;
}

char *test_str_split_by_char_no_delim()
{
    str *s = str_new("one");
    array *res = str_split_by_char(s, ',');
    str *cur_s = NULL;
    assert(res != NULL, "The returned array cannot be NULL");
    assert(res->len == 1, "The length of the resulting array should be 1");
    cur_s = array_get(res, 0);
    assert(cur_s != NULL, "The string returned at index 0 should not be NULL");
    assert(strcmp("one", cur_s->string) == 0, "The string at index 0 is not equal to \"one\"");

    str_free(s);
    array_free(res, array_of_strs_cb);
    return NULL;
}

char *test_str_trim()
{
    str *s1 = str_new("   Jonathan");
    str *s2 = str_new("  Jonathan   ");
    str *s3 = str_new("Jonathan   ");
    str_trim(s1);
    str_trim(s2);
    str_trim(s3);
    assert(strcmp(s1->string, "Jonathan") == 0, "The resulting string from (s1) does not have the expected value");
    assert(strcmp(s2->string, "Jonathan") == 0, "The resulting string from (s2) does not have the expected value");
    assert(strcmp(s3->string, "Jonathan") == 0, "The resulting string from (s3) does not have the expected value");

    str_free(s1);
    str_free(s2);
    str_free(s3);
    return NULL;
}

char *test_str_equals()
{
    str *s1 = str_new("one");
    str *s2 = str_new("");

    bool res;
    res = str_equals(s1, "one");
    assert(res == true, "The string in s1 should be equal to 'one'");
    res = str_equals(s1, "two");
    assert(res == false, "The string in s1 should not be equal to 'two'");
    res = str_equals(s2, "one");
    assert(res == false, "The string in s2 should not be equal to 'one'");
    res = str_equals(s2, "");
    assert(res == true, "The strings should be equal since they are empty");

    str_free(s1);
    str_free(s2);
    return NULL;
}

char *test_str_equals_str()
{
    str *s1 = str_new("one");
    str *s2 = str_new("");
    str *s3 = str_new("one");
    str *s4 = str_new("two");
    str *s5 = str_new("");

    bool res;
    res = str_equals_str(s1, s3);
    assert(res == true, "The string in s1 should be equal to the one in s3");
    res = str_equals_str(s1, s4);
    assert(res == false, "The string in s1 should not be equal to the one in s4");
    res = str_equals_str(s2, s1);
    assert(res == false, "The string in s2 should not be equal to the one in s1");
    res = str_equals_str(s2, s5);
    assert(res == true, "The strings should be equal since they are empty");

    str_free(s1);
    str_free(s2);
    str_free(s3);
    str_free(s4);
    str_free(s5);
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
    run_test(test_str_contains_char);
    run_test(test_str_has_prefix);
    run_test(test_str_has_prefix_str);
    run_test(test_str_suffix);
    run_test(test_str_suffix_str);
    run_test(test_str_dup);
    run_test(test_str_dup_str);
    run_test(test_str_split_by_char);
    run_test(test_str_split_by_char_with_equals);
    run_test(test_str_split_by_char_no_delim);
    run_test(test_str_trim);
    run_test(test_str_equals);
    run_test(test_str_equals_str);
    end_tests();
    return 0;
}
