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

// create a new buffer
void *c_buffer_new(unsigned int len);
// clear the contents of the buffer
void c_buffer_clear(c_buffer *buffer);
// free the buffer
void c_buffer_free(c_buffer *buffer);
// write {amount} of bytes of {data} into the buffer
int c_buffer_write(c_buffer *buffer, char *data, unsigned int amount);
// read {amount} of bytes of data from the buffer into {target}
int c_buffer_read(c_buffer *buffer, char *target, unsigned int amount);
// check if the buffer is empty
// unsigned int c_buffer_is_empty(c_buffer *buffer);
// check if the buffer is full
// unsigned int c_buffer_is_full(c_buffer *buffer);

#endif
