#include "unittest.h"
#include "cbuffer.h"

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
    return NULL;
}

char *test_destroy()
{
    cbuffer *buf = cbuffer_create(10);
    cbuffer_destroy(buf);

    return NULL;
}

int main()
{
    start_tests("cbuffer tests");
    run_test(test_create);
    run_test(test_clear);
    run_test(test_destroy);
    end_tests();

    return 0;
}
