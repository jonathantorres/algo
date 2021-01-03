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

char *str_dup(char *_str)
{
    if (!_str) {
        return NULL;
    }
    size_t len = strlen(_str);
    if (len == 0) {
        return NULL;
    }
    return _create_string(_str);
}

str *str_dup_str(str *_str)
{
    if (!_str) {
        return NULL;
    }
    if (_str->len == 0 || !_str->string) {
        return NULL;
    }
    return str_new(_str->string);
}

bool str_contains(str *_str, char *substr)
{
    if (!_str || !substr || !_str->string) {
        return false;
    }
    if (strlen(substr) == 0) {
        return true;
    }

    char *found = strstr(_str->string, substr);
    if (found) {
        return true;
    }
    return false;
}

bool str_contains_str(str *_str, str *substr)
{
    if (!_str || !substr || !_str->string || !substr->string) {
        return false;
    }
    if (strlen(substr->string) == 0) {
        return true;
    }

    char *found = strstr(_str->string, substr->string);
    if (found) {
        return true;
    }
    return false;
}

bool str_has_prefix(str *_str, char *prefix)
{
    if (!_str || !prefix || !_str->string) {
        return false;
    }
    if (strlen(prefix) == 0) {
        return true;
    }

    char *pos = strstr(_str->string, prefix);
    if (!pos) {
        return false;
    }
    return (pos - _str->string) == 0;
}

bool str_has_prefix_str(str *_str, str *prefix)
{
    if (!_str || !prefix || !_str->string || !prefix->string) {
        return false;
    }
    if (strlen(prefix->string) == 0) {
        return true;
    }

    char *pos = strstr(_str->string, prefix->string);
    if (!pos) {
        return false;
    }

    return (pos - _str->string) == 0;
}

bool str_has_suffix(str *_str, char *suffix)
{
    if (!_str || !suffix || !_str->string) {
        return false;
    }
    if (strlen(suffix) == 0) {
        return true;
    }
    if (strlen(suffix) > strlen(_str->string)) {
        return false;
    }

    char *str_p = (_str->string + strlen(_str->string)) - strlen(suffix);
    if (strcmp(str_p, suffix) == 0) {
        return true;
    }
    return false;
}

bool str_has_suffix_str(str *_str, str *suffix)
{
    if (!_str || !suffix || !_str->string || !suffix->string) {
        return false;
    }
    if (strlen(suffix->string) == 0) {
        return true;
    }
    if (strlen(suffix->string) > strlen(_str->string)) {
        return false;
    }

    char *str_p = (_str->string + strlen(_str->string)) - strlen(suffix->string);
    if (strcmp(str_p, suffix->string) == 0) {
        return true;
    }
    return false;
}
