#include "c_buffer.h"

unsigned int _c_buffer_available_data(c_buffer *buffer)
{
    return buffer->end % buffer->len - buffer->start;
}

void *c_buffer_new(unsigned int len)
{
    c_buffer *buffer = malloc(sizeof(c_buffer));

    if (!buffer) {
        fputs("Not enough memory.", stderr);
        return NULL;
    }

    buffer->len = len;
    buffer->start = 0;
    buffer->end = 0;
    buffer->buffer = malloc(buffer->len);

    if (!buffer->buffer) {
        fputs("Not enough memory.", stderr);
        return NULL;
    }

    return buffer;
}

void c_buffer_clear(c_buffer *buffer)
{
    if (!buffer) {
        fputs("Must provide a valid c_buffer.", stderr);
        return;
    }

    if (buffer->buffer) {
        free(buffer->buffer);
        buffer->buffer = malloc(buffer->len);

        if (!buffer->buffer) {
            fputs("Not enough memory.", stderr);
            return;
        }
        buffer->start = 0;
        buffer->end = 0;
    }
}

void c_buffer_free(c_buffer *buffer)
{
    if (!buffer) {
        fputs("Must provide a valid c_buffer.", stderr);
        return;
    }

    if (buffer->buffer) {
        free(buffer->buffer);
    }
    free(buffer);
}

int c_buffer_write(c_buffer *buffer, char *data, unsigned int amount)
{
    if (!buffer) {
        fputs("Must provide a valid c_buffer.", stderr);
        return -1;
    }

    if (_c_buffer_available_data(buffer) == 0) {
        buffer->start = 0;
        buffer->end = 0;
    }

    // not enough space
    if (buffer->len - buffer->end < amount) {
        return -1;
    }

    void *result = memcpy(buffer->buffer + buffer->end, data, amount);
    if (!result) {
        return -1;
    }

    buffer->end = buffer->end + amount % buffer->len;

    return amount;
}

int c_buffer_read(c_buffer *buffer, char *target, unsigned int amount)
{
    if (!buffer) {
        fputs("Must provide a valid c_buffer.", stderr);
        return -1;
    }

    if (amount > _c_buffer_available_data(buffer)) {
        return -1;
    }

    void *result = memcpy(target, buffer->buffer + buffer->start, amount);
    if (!result) {
        return -1;
    }

    buffer->start = buffer->start + amount % buffer->len;

    if (buffer->start == buffer->end) {
        buffer->start = 0;
        buffer->end = 0;
    }

    return amount;
}
