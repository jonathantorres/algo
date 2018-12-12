#include "cbuffer.h"
#include <stdlib.h>
#include <stdio.h>

void *cbuffer_create(unsigned int length)
{
    cbuffer *buffer = malloc(sizeof(cbuffer));

    if (!buffer) {
        fputs("Not enough memory.", stderr);
        exit(EXIT_FAILURE);
    }

    buffer->length = length;
    buffer->start = 0;
    buffer->end = 0;
    buffer->buffer = malloc(buffer->length);

    if (!buffer->buffer) {
        fputs("Not enough memory.", stderr);
        exit(EXIT_FAILURE);
    }

    return buffer;
}

void cbuffer_clear(cbuffer *buffer)
{
    if (!buffer) {
        fputs("Must provide a valid cbuffer.", stderr);
        exit(EXIT_FAILURE);
    }

    if (buffer->buffer) {
        free(buffer->buffer);
        buffer->buffer = malloc(buffer->length);

        if (!buffer->buffer) {
            fputs("Not enough memory.", stderr);
            exit(EXIT_FAILURE);
        }
        buffer->start = 0;
        buffer->end = 0;
    }
}

void cbuffer_destroy(cbuffer *buffer)
{
    if (!buffer) {
        fputs("Must provide a valid cbuffer.", stderr);
        exit(EXIT_FAILURE);
    }

    if (buffer->buffer) {
        free(buffer->buffer);
    }
    free(buffer);
}
