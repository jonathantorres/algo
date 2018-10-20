#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char *car;
    struct node *next;
    struct node *prev;
};
typedef struct node node_t;

node_t* create_node(char *car);
void print_list(node_t *head);
void append(node_t **head, char *car);
void prepend(node_t **head, char *car);

int main(void)
{
    // node_t *head = NULL; // This will initialize an empty list
    node_t *head = malloc(sizeof(node_t));
    head->car = "Toyota";
    head->prev = NULL;
    head->next = NULL;

    append(&head, "Honda");
    append(&head, "Mitsubishi");
    append(&head, "Nissan");
    append(&head, "Mercedes Benz");
    prepend(&head, "Lexus");
    print_list(head);
    return 0;
}

void prepend(node_t **head, char *car)
{
    // prepending to an empty list
    if ((*head) == NULL) {
        *head = create_node(car);
        return;
    }

    node_t *new_car = create_node(car);
    new_car->next = *head;
    *head = new_car;
}

void append(node_t **head, char *car)
{
    // appending to an empty list
    if ((*head) == NULL) {
        *head = create_node(car);
        return;
    }

    node_t *temp = *head;
    node_t *last;
    node_t *prev;

    while (temp != NULL) {
        last = temp;
        prev = temp->prev;
        temp = temp->next;
    }

    last->next = create_node(car);
    last->next->prev = prev;

    free(temp);
}

node_t* create_node(char *car)
{
    node_t *new_car = malloc(sizeof(node_t));

    if (new_car == NULL) {
        puts("Error: Could not allocate memory");
        exit(1);
    }

    new_car->car = car;
    new_car->next = NULL;
    new_car->prev = NULL;

    return new_car;
}

void print_list(node_t *head)
{
    node_t *current = head;

    if (current == NULL) {
        puts("[]");
        return;
    }

    printf("[");

    while (current != NULL) {
        printf("%s,", current->car);
        current = current->next;
    }

    printf("]\n");
}
