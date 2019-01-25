#include "cbuffer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void *cbuffer_create(unsigned int length)
{
    cbuffer *buffer = malloc(sizeof(cbuffer));

    if (!buffer) {
        fputs("Not enough memory.", stderr);
        return NULL;
    }

    buffer->length = length;
    buffer->start = 0;
    buffer->end = 0;
    buffer->buffer = malloc(buffer->length);

    if (!buffer->buffer) {
        fputs("Not enough memory.", stderr);
        return NULL;
    }

    return buffer;
}

void cbuffer_clear(cbuffer *buffer)
{
    if (!buffer) {
        fputs("Must provide a valid cbuffer.", stderr);
        return;
    }

    if (buffer->buffer) {
        free(buffer->buffer);
        buffer->buffer = malloc(buffer->length);

        if (!buffer->buffer) {
            fputs("Not enough memory.", stderr);
            return;
        }
        buffer->start = 0;
        buffer->end = 0;
    }
}

void cbuffer_destroy(cbuffer *buffer)
{
    if (!buffer) {
        fputs("Must provide a valid cbuffer.", stderr);
        return;
    }

    if (buffer->buffer) {
        free(buffer->buffer);
    }
    free(buffer);
}

unsigned int available_data(cbuffer *buffer)
{
    return buffer->end % buffer->length - buffer->start;
}

int cbuffer_write(cbuffer *buffer, char *data, unsigned int amount)
{
    if (!buffer) {
        fputs("Must provide a valid cbuffer.", stderr);
        return -1;
    }

    if (available_data(buffer) == 0) {
        buffer->start = 0;
        buffer->end = 0;
    }

    // not enough space
    if (buffer->length - buffer->end < amount) {
        return -1;
    }

    void *result = memcpy(buffer->buffer + buffer->end, data, amount);
    if (!result) {
        return -1;
    }

    buffer->end = buffer->end + amount % buffer->length;

    return amount;
}

int cbuffer_read(cbuffer *buffer, char *target, unsigned int amount)
{
    if (!buffer) {
        fputs("Must provide a valid cbuffer.", stderr);
        return -1;
    }

    if (amount > available_data(buffer)) {
        return -1;
    }

    void *result = memcpy(target, buffer->buffer + buffer->start, amount);
    if (!result) {
        return -1;
    }

    buffer->start = buffer->start + amount % buffer->length;

    if (buffer->start == buffer->end) {
        buffer->start = 0;
        buffer->end = 0;
    }

    return amount;
}
