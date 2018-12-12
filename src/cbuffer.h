#ifndef _cbuffer_h
#define _cbuffer_h

typedef struct cbuffer {
    char *buffer;
    unsigned int length;
    unsigned int start;
    unsigned int end;
} cbuffer;

// create a new buffer
void *cbuffer_create(unsigned int length);
// clear the contents of the buffer
void cbuffer_clear(cbuffer *buffer);
// destroy the buffer
void cbuffer_destroy(cbuffer *buffer);
// write {amount} of bytes of {data} into the buffer
void cbuffer_write(cbuffer *buffer, char *data, unsigned int amount);
// read {amount} of bytes of data from the buffer into {target}
void cbuffer_read(cbuffer *buffer, char *target, unsigned int amount);
// check if the buffer is empty
unsigned int cbuffer_is_empty(cbuffer *buffer);
// check if the buffer is full
unsigned int cbuffer_is_full(cbuffer *buffer);

#endif
