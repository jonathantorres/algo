#ifndef _h_str_h
#define _h_str_h

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct str {
    char *string;
    int len;
} str;

str *str_new(char* chars);
void str_free(str *_str);
int str_len(str *_str);
char *str_get_string(str *_str);
str *str_concat(str *_str, char *chars);
str *str_concat_str(str *_str, str *chars);

bool str_contains(str *_str, char *substr);
bool str_contains_str(str *_str, str *substr);
bool str_has_prefix(str *_str, char *prefix);
bool str_has_prefix_str(str *_str, str *prefix);
bool str_has_suffix(str *_str, char *suffix);
bool str_has_suffix_str(str *_str, str *suffix);

#endif
