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
