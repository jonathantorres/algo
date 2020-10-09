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
str *str_concat_char(str *_str, char _char);

bool str_contains(str *_str, char *chars);
bool str_contains_str(str *_str, str *chars);

#endif
