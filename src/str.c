#include "str.h"

static char *_create_string(char *chars)
{
    int len = strlen(chars);
    char *string = malloc(len+1);
    if (!string) {
        return NULL;
    }
    memset(string, 0, len+1);
    char *str_p = string;
    for (char *c = chars; *c != '\0'; c++) {
        *str_p = *c;
        str_p++;
    }
    return string;
}

static char *_concat_chars(char *cur_str, char *chars)
{
    unsigned long chars_len = strlen(chars);
    if (chars_len == 0) {
        return cur_str;
    }

    char *new_str = realloc(cur_str, chars_len+1);
    if (!new_str) {
        return cur_str;
    }
    char *new_str_p = new_str;
    char *chars_p = chars;
    for (; *new_str_p != '\0'; new_str_p++) {
        // moving the pointer to the end of the current string
    }
    memset(new_str_p, 0, chars_len+1);
    for (; *chars_p != '\0'; chars_p++) {
        *new_str_p = *chars_p;
        new_str_p++;
    }
    *new_str_p = '\0';

    return new_str;
}

str *str_new(char *chars)
{
    str *_str = malloc(sizeof(str));
    if (!_str) {
        return NULL;
    }

    _str->len = 0;
    _str->string = NULL;
    if (!chars) {
        char *empty_str = _create_string("");
        if (!empty_str) {
            free(_str);
            return NULL;
        }
        _str->string = empty_str;
        return _str;
    }

    _str->len = strlen(chars);
    _str->string = _create_string(chars);
    return _str;
}

void str_free(str *_str)
{
    if (!_str) {
        return;
    }
    if (_str->string) {
        free(_str->string);
    }
    free(_str);
}

int str_len(str *_str)
{
    if (!_str) {
        return 0;
    }
    return _str->len;
}

char *str_get_string(str *_str)
{
    if (!_str) {
        return NULL;
    }
    if (!_str->string) {
        return NULL;
    }
    return _str->string;
}

str *str_concat_str(str *_str, str *chars)
{
    if (!_str || !chars) {
        return _str;
    }
    unsigned long chars_len = strlen(chars->string);

    _str->string = _concat_chars(_str->string, chars->string);
    _str->len += chars_len;

    return _str;
}

str *str_concat(str *_str, char *chars)
{
    if (!_str || !chars) {
        return _str;
    }
    unsigned long chars_len = strlen(chars);

    _str->string = _concat_chars(_str->string, chars);
    _str->len += chars_len;

    return _str;
}
