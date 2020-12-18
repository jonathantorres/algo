#include "unittest.h"
#include "c_buffer.h"
#include <string.h>

char *test_create()
{
    c_buffer *buf = c_buffer_new(10);
    assert(buf != NULL, "Buffer should not be NULL");
    assert(buf->start == 0, "Buffer's start should be at 0");
    assert(buf->end == 0, "Buffer's end should be at 0");
    assert(buf->len == 10, "Buffer len should be 10");
    assert(buf->buffer != NULL, "Buffer's buffer should not be NULL");
    c_buffer_free(buf);

    return NULL;
}

char *test_clear()
{
    c_buffer *buf = c_buffer_new(100);
    c_buffer_write(buf, "Jonathan", sizeof("Jonathan"));
    c_buffer_clear(buf);
    assert(buf->start == 0, "Buffer's start should be at 0");
    assert(buf->end == 0, "Buffer's end should be at 0");
    assert(buf->len == 100, "Buffer len should be 100");
    c_buffer_free(buf);

    return NULL;
}

char *test_free()
{
    c_buffer *buf = c_buffer_new(10);
    c_buffer_free(buf);

    return NULL;
}

char *test_write()
{
    c_buffer *buf = c_buffer_new(100);
    int rc = c_buffer_write(buf, "John", sizeof("John"));
    assert(rc == sizeof("John"), "Write of 'John' failed!");
    assert(buf->start == 0, "Buffer start should be 0");
    assert(buf->end == 5, "Buffer end should be 5");
    rc = c_buffer_write(buf, "Jonathan", sizeof("Jonathan"));
    assert(rc == sizeof("Jonathan"), "Write of 'Jonathan' failed!");
    assert(buf->end == 14, "Buffer end should be 14");
    c_buffer_free(buf);

    return NULL;
}

char *test_read()
{
    c_buffer *buf = c_buffer_new(100);
    c_buffer_write(buf, "Hello, my name is Jonathan", sizeof("Hello, my name is Jonathan"));
    char data[100] = { '\0' };
    int rc = c_buffer_read(buf, data, 5);
    assert(rc == 5, "Read of 'Hello' failed!");
    assert(strcmp("Hello", data) == 0, "Wrong data read into the data array");
    assert(buf->start == 5, "Buffer start should be 5");
    char msg[100] = { '\0' };
    rc = c_buffer_read(buf, msg, 15);
    assert(rc == 15, "Read of ', my name is Jo' failed!");
    assert(strcmp(", my name is Jo", msg) == 0, "Wrong data read into the msg array");
    assert(buf->start == 20, "Buffer start should be 20");
    assert(buf->end == 27, "Buffer end should be 27");
    c_buffer_free(buf);

    return NULL;
}

char *test_buffer_is_empty()
{
    c_buffer *buf = c_buffer_new(10);
    int rc = c_buffer_is_empty(buf);
    assert(rc == 1, "The buffer should be empty");
    c_buffer_write(buf, "John", sizeof("John"));
    rc = c_buffer_is_empty(buf);
    assert(rc == 0, "The buffer should not be empty");
    char msg[10] = { '\0' };
    int rc2 = c_buffer_read(buf, msg, 5);
    assert(rc2 == 5, "Reading into msg failed!");
    rc = c_buffer_is_empty(buf);
    assert(rc == 1, "The buffer should be empty after reading all of the data");
    return NULL;
}

char *test_buffer_is_full()
{
    c_buffer *buf = c_buffer_new(10);
    int rc = c_buffer_is_full(buf);
    assert(rc == 0, "The buffer should not be full, since there's nothing on it");
    c_buffer_write(buf, "John", sizeof("John"));
    rc = c_buffer_is_full(buf);
    assert(rc == 0, "The buffer should not be full, after writing just some data");
    c_buffer_write(buf, "Luis", sizeof("Luis"));
    rc = c_buffer_is_full(buf);
    assert(rc == 1, "The buffer should be full");
    char msg[10] = { '\0' };
    int rc2 = c_buffer_read(buf, msg, 5);
    assert(rc2 == 5, "Reading into msg failed!");
    rc = c_buffer_is_full(buf);
    assert(rc == 0, "The buffer should be not be full now, since we read some of it's data");
    return NULL;
}

int main()
{
    start_tests("c_buffer tests");
    run_test(test_create);
    run_test(test_clear);
    run_test(test_free);
    run_test(test_write);
    run_test(test_read);
    run_test(test_buffer_is_empty);
    run_test(test_buffer_is_full);
    end_tests();

    return 0;
}
