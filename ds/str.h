#ifndef _h_str_h
#define _h_str_h

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "array.h"

typedef struct str {
    char *string;
    char *start_p;
    int len;
} str;

str *str_new(char* chars);
void str_free(str *_str);
int str_len(str *_str);
char *str_get_string(str *_str);
char *str_dup(char *_str);
str *str_dup_str(str *_str);
str *str_concat(str *_str, char *chars);
str *str_concat_str(str *_str, str *chars);
array *str_split_by_char(str *_str, char delim);
void str_trim(str *_str);

bool str_contains(str *_str, char *substr);
bool str_contains_str(str *_str, str *substr);
bool str_contains_char(str *_str, char ch);
bool str_equals(str *_str, char *cstr);
bool str_equals_str(str *str1, str *str2);
bool str_has_prefix(str *_str, char *prefix);
bool str_has_prefix_str(str *_str, str *prefix);
bool str_has_suffix(str *_str, char *suffix);
bool str_has_suffix_str(str *_str, str *suffix);

#endif
