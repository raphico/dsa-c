#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

void insert_node(node **head, int data);
void print_list(node *head);
void free_list(node **head);

int main() {
    node *head = NULL;

    insert_node(&head, 10);
    insert_node(&head, 20);
    insert_node(&head, 30);

    print_list(head);

    free_list(&head);
}

node *create_node(int data) {
    node *n = malloc(sizeof(node));
    if (!n) {
        return NULL;
    }

    n->data = data;
    n->next = NULL;

    return n;
}

void insert_node(node **head, int data) {
    node *n = create_node(data);
    if (!n) {
        fprintf(stderr, "failed to create node");
        free_list(head);
        exit(1);
    }

    n->next = *head;
    *head = n;
}

void print_list(node *head) {
    for (node *ptr = head; ptr != NULL; ptr = ptr->next) {
        printf("%d\n", ptr->data);
    }
}

void free_list(node **head) {
    node *ptr = *head;
    while (ptr != NULL) {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
    *head = NULL;
}
