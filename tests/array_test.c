#include "unittest.h"
#include "array.h"
#include <stdio.h>
#include <string.h>

// utility method to print the contents of an array
// in this test we'll be using an array of numbers
void array_print(array *_array, char type)
{
    if (!_array) {
        fputs("Must provide an array.", stderr);
        exit(EXIT_FAILURE);
    }

    printf("[");
    ARRAY_FOREACH(_array) {
        void *val = NULL;
        switch (type) {
            case 'i':
                val = (int*)array_get(_array, i);
                printf("%d,", *(int*)val);
            break;

            case 's':
                val = array_get(_array, i);
                printf("%s,", (char*)val);
            break;
        }
    }
    printf("]\n");
}

void array_free_cb_func(void *value)
{
    if (value) {
        free(value);
    }
}

char *test_create()
{
    array *_array = array_new(10, sizeof(int*));

    assert(_array->len == 0, "Array len should be 0");
    assert(_array->capacity == 10, "Array capacity should be 10");
    assert(_array->expand_rate == 100, "Array expand_rate should be 100");
    assert(_array->item_size == sizeof(int*), "Array item_size is not correct, it should be sizeof(int*)");
    assert(_array->contents != NULL, "Array contents should not be NULL");

    array_free(_array, NULL);

    return NULL;
}

char *test_free()
{
    array *_array = array_new(100, sizeof(int*));

    for (unsigned int i = 0; i < 100; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = i * 5;
            array_push(_array, value);
        }
    }

    assert(_array->len == 100, "Array len must be 100");
    assert(_array->capacity == 200, "Array capacity must be 200");
    assert(_array->contents != NULL, "Array contents should not be NULL");
    array_free(_array, array_free_cb_func);

    return NULL;
}

char *test_clear()
{
    array *_array = array_new(100, sizeof(int*));

    for (unsigned int i = 0; i < 100; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = i * 5;
            array_push(_array, value);
        }
    }

    assert(_array->len == 100, "Array len must be 100");
    assert(_array->capacity == 200, "Array capacity should be 200");
    assert(_array->contents != NULL, "Array contents should not be NULL");

    array_clear(_array, array_free_cb_func);
    assert(_array->len == 0, "Array len must be 0");
    array_free(_array, NULL);

    return NULL;
}

char *test_push()
{
    array *_array = array_new(10, sizeof(int*));

    for (unsigned int i = 0; i < 100; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = i * 5;
            array_push(_array, value);
        }
    }

    assert(_array->capacity == 110, "Array capacity should be 110");
    assert(_array->len == 100, "Array len should be 100");
    assert(_array->contents != NULL, "Array contents should not be NULL");
    array_free(_array, array_free_cb_func);

    return NULL;
}

char *test_pop()
{
    array *_array = array_new(10, sizeof(int*));

    for (unsigned int i = 0; i < 5; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = i * 5;
            array_push(_array, value);
        }
    }

    assert(_array->len == 5, "Array len should be 5");
    int *last_num = array_pop(_array);
    assert(*last_num == 20, "Last element's value should be 20");
    assert(_array->len == 4, "Array len should be 4");
    assert(_array->contents != NULL, "Array contents should not be NULL");
    array_free(_array, array_free_cb_func);
    free(last_num);

    return NULL;
}

char *test_set()
{
    array *_array = array_new(10, sizeof(int*));

    for (unsigned int i = 0; i < 5; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = i * 5;
            array_set(_array, value, i);
        }
    }

    assert(_array->capacity == 10, "Array capacity should be 10");
    assert(_array->len == 5, "Array len should be 5");
    assert(_array->contents != NULL, "Array contents should not be NULL");
    array_free(_array, array_free_cb_func);

    return NULL;
}

char *test_get()
{
    array *_array = array_new(10, sizeof(int*));

    for (unsigned int i = 0; i < 5; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = i * 5;
            array_push(_array, value);
        }
    }

    int *number = array_get(_array, 4);
    void *off_number = array_get(_array, 100);
    assert(*number == 20, "Element's value should be 20");
    assert(off_number == NULL, "The off number should be NULL");
    array_free(_array, array_free_cb_func);

    return NULL;
}

char *test_remove()
{
    array *_array = array_new(10, sizeof(int*));

    for (unsigned int i = 0; i < 5; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = i * 5;
            array_push(_array, value);
        }
    }

    assert(_array->len == 5, "Array len should be 5");
    int *number = array_remove(_array, 1);
    assert(*number == 5, "Element's value should be 5");
    assert(_array->len == 4, "Array len should be 4");
    array_free(_array, array_free_cb_func);
    free(number);

    return NULL;
}

char *test_shift()
{
    array *_array = array_new(10, sizeof(int*));

    for (unsigned int i = 0; i < 5; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = i * 5;
            array_push(_array, value);
        }
    }

    assert(_array->len == 5, "Array len should be 5");
    int *new_value = malloc(sizeof(int));
    if (new_value != NULL) {
        *new_value = 200;
        array_shift(_array, new_value);
    }
    int *val = array_get(_array, 0);
    assert(*val == 200, "Value of new element should be 200");
    assert(_array->len == 6, "Array len should be 6");
    array_free(_array, array_free_cb_func);

    return NULL;
}

char *test_unshift()
{
    array *_array = array_new(10, sizeof(int*));

    for (unsigned int i = 0; i < 5; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = i * 5;
            array_push(_array, value);
        }
    }

    assert(_array->len == 5, "Array len should be 5");
    int *first_num = array_unshift(_array);
    assert(*first_num == 0, "Value of removed element should be 0");
    assert(_array->len == 4, "Array len should be 4");
    array_free(_array, array_free_cb_func);
    free(first_num);

    return NULL;
}

char *test_array_of_strings()
{
    array *_array = array_new(10, sizeof(char**));
    char *strings[5] = {
        "foo",
        "bar",
        "baz",
        "hello",
        "again",
    };

    for (unsigned int i = 0; i < 5; i++) {
        char *string = malloc(10);
        if (string != NULL) {
            strcpy(string, strings[i]);
            array_push(_array, string);
        }
    }

    assert(_array->contents != NULL, "Array contents should not be NULL");
    assert(_array->len == 5, "Array len should be 5");
    char *last = array_pop(_array);
    assert(strcmp(last, strings[4]) == 0, "Strings 'again' should be equal");
    assert(_array->len == 4, "Array len should be 4");
    char *first = array_unshift(_array);
    assert(strcmp(first, strings[0]) == 0, "Strings 'foo' should be equal");
    assert(_array->len == 3, "Array len should be 3");

    array_free(_array, array_free_cb_func);
    free(last);
    free(first);

    return NULL;
}

char *test_array_stack_items()
{
    array *_array = array_new(10, sizeof(char*));

    array_push(_array, "John");
    array_push(_array, "Jonathan");
    array_push(_array, "George");

    assert(_array->contents != NULL, "Array contents should not be NULL");
    assert(_array->len == 3, "Array len should be 3");
    char *last = array_pop(_array);
    assert(strcmp(last, "George") == 0, "String 'George' should be equal");
    assert(_array->len == 2, "Array len should be 2");
    char *first = array_unshift(_array);
    assert(strcmp(first, "John") == 0, "String 'John' should be equal");
    assert(_array->len == 1, "Array len should be 1");
    array_free(_array, NULL);

    return NULL;
}

typedef struct person_dum {
    char *first_name;
    char *last_name;
    int age;
} person_dum_t;

char *test_array_struct_pointers()
{
    array *_array = array_new(10, sizeof(person_dum_t*));
    person_dum_t *p = malloc(sizeof(person_dum_t));
    p->first_name = "Jonathan";
    p->last_name = "Torres";
    p->age = 33;

    array_push(_array, p);
    assert(_array->contents != NULL, "Array contents should not be NULL");
    assert(_array->len == 1, "Array len should be 1");
    person_dum_t *per = array_get(_array, 0);
    assert(strcmp(per->first_name, "Jonathan") == 0, "String 'Jonathan' should be equal");
    array_free(_array, array_free_cb_func);

    return NULL;
}

char *test_array_swap()
{
    array *_array = array_new(10, sizeof(int*));

    for (unsigned int i = 0; i < 5; i++) {
        int *value = malloc(sizeof(int));
        if (value != NULL) {
            *value = i * 5;
            array_push(_array, value);
        }
    }

    assert(_array->len == 5, "Array len should be 5");
    assert(*(int*)array_get(_array, 0) == 0, "Index 0 of array should be zero");
    assert(*(int*)array_get(_array, 1) == 5, "Index 0 of array should be five");
    array_swap(_array, 0, 1);
    assert(*(int*)array_get(_array, 0) == 5, "Index 0 of array should be five");
    assert(*(int*)array_get(_array, 1) == 0, "Index 0 of array should be zero");
    assert(_array->len == 5, "Array len should be 5");
    array_free(_array, array_free_cb_func);

    return NULL;
}

int main()
{
    start_tests("array tests");
    run_test(test_create);
    run_test(test_free);
    run_test(test_clear);
    run_test(test_push);
    run_test(test_pop);
    run_test(test_set);
    run_test(test_get);
    run_test(test_remove);
    run_test(test_shift);
    run_test(test_unshift);
    run_test(test_array_of_strings);
    run_test(test_array_stack_items);
    run_test(test_array_struct_pointers);
    run_test(test_array_swap);
    end_tests();

    return 0;
}
