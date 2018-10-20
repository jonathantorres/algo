#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char *car;
    struct node *next;
};
typedef struct node node_t;

node_t* create_node(char *car);
void print_list(node_t *head);
void append(node_t **head, char *car);
void prepend(node_t **head, char *car);
void remove_node(node_t **head, char *car);

int main(void)
{
    // node_t *head = NULL; // This will initialize an empty list
    node_t *head = malloc(sizeof(node_t));
    head->car = "Toyota";
    head->next = NULL;

    append(&head, "Honda");
    append(&head, "Mitsubishi");
    append(&head, "Nissan");
    append(&head, "Mercedes Benz");
    prepend(&head, "Lexus");
    print_list(head);
    remove_node(&head, "Mitsubishi");
    print_list(head);
    return 0;
}

void remove_node(node_t **head, char *car)
{
    // do nothing if list is empty
    if ((*head) == NULL) {
        return;
    }

    node_t *current = *head;
    node_t *next_node = NULL;

    if (strcmp((*head)->car, car) == 0) {
        // remove the first item
        *head = (*head)->next;
        return;
    }

    while (current != NULL) {
        if (strcmp(current->car, car) == 0) {
            next_node = current->next;
            current->next = NULL;
            current = next_node;
            break;
        }

        current = current->next;
    }
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

    while (temp != NULL) {
        last = temp;
        temp = temp->next;
    }

    free(temp);

    last->next = create_node(car);
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
