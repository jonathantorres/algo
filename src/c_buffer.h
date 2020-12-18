#ifndef _c_buffer_h
#define _c_buffer_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct c_buffer {
    char *buffer;
    unsigned int len;
    unsigned int start;
    unsigned int end;
} c_buffer;

void *c_buffer_new(unsigned int len);
void c_buffer_clear(c_buffer *buffer);
void c_buffer_free(c_buffer *buffer);
int c_buffer_write(c_buffer *buffer, char *data, unsigned int amount);
int c_buffer_read(c_buffer *buffer, char *target, unsigned int amount);
unsigned int c_buffer_is_empty(c_buffer *buffer);
unsigned int c_buffer_is_full(c_buffer *buffer);

#endif
