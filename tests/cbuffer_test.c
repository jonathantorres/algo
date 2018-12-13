#include "unittest.h"
#include "cbuffer.h"
#include <string.h>

char *test_create()
{
    cbuffer *buf = cbuffer_create(10);
    assert(buf != NULL, "Buffer should not be NULL");
    assert(buf->start == 0, "Buffer's start should be at 0");
    assert(buf->end == 0, "Buffer's end should be at 0");
    assert(buf->length == 10, "Buffer length should be 10");
    assert(buf->buffer != NULL, "Buffer's buffer should not be NULL");
    cbuffer_destroy(buf);

    return NULL;
}

char *test_clear()
{
    cbuffer *buf = cbuffer_create(100);
    cbuffer_write(buf, "Jonathan", sizeof("Jonathan"));
    cbuffer_clear(buf);
    assert(buf->start == 0, "Buffer's start should be at 0");
    assert(buf->end == 0, "Buffer's end should be at 0");
    assert(buf->length == 100, "Buffer length should be 100");
    cbuffer_destroy(buf);

    return NULL;
}

char *test_destroy()
{
    cbuffer *buf = cbuffer_create(10);
    cbuffer_destroy(buf);

    return NULL;
}

char *test_write()
{
    cbuffer *buf = cbuffer_create(100);
    int rc = cbuffer_write(buf, "John", sizeof("John"));
    assert(rc == sizeof("John"), "Write of 'John' failed!");
    assert(buf->start == 0, "Buffer start should be 0");
    assert(buf->end == 5, "Buffer end should be 5");
    rc = cbuffer_write(buf, "Jonathan", sizeof("Jonathan"));
    assert(rc == sizeof("Jonathan"), "Write of 'Jonathan' failed!");
    assert(buf->end == 14, "Buffer end should be 14");
    cbuffer_destroy(buf);

    return NULL;
}

char *test_read()
{
    cbuffer *buf = cbuffer_create(100);
    cbuffer_write(buf, "Hello, my name is Jonathan", sizeof("Hello, my name is Jonathan"));
    char data[100] = { '\0' };
    int rc = cbuffer_read(buf, data, 5);
    assert(rc == 5, "Read of 'Hello' failed!");
    assert(strcmp("Hello", data) == 0, "Wrong data read into the data array");
    assert(buf->start == 5, "Buffer start should be 5");
    char msg[100] = { '\0' };
    rc = cbuffer_read(buf, msg, 15);
    assert(rc == 15, "Read of ', my name is Jo' failed!");
    assert(strcmp(", my name is Jo", msg) == 0, "Wrong data read into the msg array");
    assert(buf->start == 20, "Buffer start should be 20");
    assert(buf->end == 27, "Buffer end should be 27");
    cbuffer_destroy(buf);

    return NULL;
}

int main()
{
    start_tests("cbuffer tests");
    run_test(test_create);
    run_test(test_clear);
    run_test(test_destroy);
    run_test(test_write);
    run_test(test_read);
    end_tests();

    return 0;
}
