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
    _str->start_p = NULL;
    if (!chars) {
        char *empty_str = _create_string("");
        if (!empty_str) {
            free(_str);
            return NULL;
        }
        _str->string = empty_str;
        _str->start_p = empty_str;
        return _str;
    }

    _str->len = strlen(chars);
    _str->string = _create_string(chars);
    _str->start_p = _str->string;
    return _str;
}

void str_free(str *_str)
{
    if (!_str) {
        return;
    }
    if (_str->start_p) {
        free(_str->start_p);
    }
    _str->start_p = NULL;
    _str->string = NULL;
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
    _str->start_p = _str->string;
    _str->len += chars_len;

    return _str;
}

array *str_split_by_char(str *_str, char delim)
{
    if (!_str) {
        return NULL;
    }
    if (_str->len == 0 || !_str->string) {
        return NULL;
    }

    // find out how many delimiters are in the string
    int delim_count = 0;
    for (int i = 0; i < (int)strlen(_str->string); i++) {
        if (_str->string[i] == delim) {
            delim_count++;
        }
    }
    if (delim_count == 0) {
        return NULL;
    }

    array *splits = array_new(delim_count, sizeof(str*));
    if (!splits) {
        return NULL;
    }
    char *buf = malloc(strlen(_str->string));
    if (!buf) {
        array_free(splits, NULL);
        return NULL;
    }
    memset(buf, 0, strlen(_str->string));
    char *buf_p = buf;

    for (int j = 0; j < (int)strlen(_str->string); j++) {
        if (_str->string[j] == delim || j == (int)(strlen(_str->string) - 1)) {
            // in the current delimiter or the end of the string,
            // push the string to the array and reset the buffer
            if (j == (int)(strlen(_str->string) - 1)) {
                *buf_p = _str->string[j];
                buf_p++;
            }

            *buf_p = '\0';
            str *part = str_new(buf);
            array_push(splits, part);
            buf_p = buf;
            continue;
        }

        *buf_p = _str->string[j];
        buf_p++;
    }
    free(buf);

    return splits;
}

void str_trim(str *_str)
{
    if (!_str) {
        return;
    }
    if (_str->len == 0 || !_str->string) {
        return;
    }

    int spaces_left = 0;
    char *str_p = _str->string;

    // count the amount of whitespace on the left
    for (int i = 0; i < _str->len; i++) {
        if (isspace(_str->string[i])) {
            spaces_left++;
            str_p++;
            continue;
        }
        break;
    }
    if (spaces_left > 0) {
        _str->len = _str->len - spaces_left;
        _str->string = str_p;
    }

    int spaces_right = 0;
    bool ws_found = false;
    str_p = &_str->string[_str->len-1];
    // move string pointer the left as long as there is whitespace
    for (int i = _str->len-1; i > 0; i--) {
        if (isspace(_str->string[i])) {
            spaces_right++;
            ws_found = true;
            str_p--;
            continue;
        }
        if (ws_found) {
            *++str_p = '\0';
        }
        break;
    }

    if (spaces_right > 0) {
        _str->len = _str->len - spaces_right;
    }
}

str *str_concat(str *_str, char *chars)
{
    if (!_str || !chars) {
        return _str;
    }
    unsigned long chars_len = strlen(chars);

    _str->string = _concat_chars(_str->string, chars);
    _str->start_p = _str->string;
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

bool str_contains_char(str *_str, char ch)
{
    if (!_str || !_str->string) {
        return false;
    }

    char *res = NULL;
    if ((res = strchr(_str->string, ch)) == NULL) {
        return false;
    }
    return true;
}

bool str_equals(str *_str, char *cstr)
{
    if (!_str || !cstr || !_str->string) {
        return false;
    }

    if (strlen(cstr) == 0 && _str->len == 0) {
        return true;
    }

    if (strcmp(_str->string, cstr) == 0) {
        return true;
    }
    return false;
}

bool str_equals_str(str *str1, str *str2)
{
    if (!str2) {
        return false;
    }
    return str_equals(str1, str2->string);
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
