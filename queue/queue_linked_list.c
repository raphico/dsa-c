#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

node *create_node(int data);
int enqueue(node **head, node **tail, int data);
void dequeue(node **tail, node **head);
void peek(node **head);
void print_queue(node *head);
void free_queue(node **head, node **tail);

int main() {
    node *head = NULL;
    node *tail = NULL;

    if (enqueue(&head, &tail, 10) < 0) {
        fprintf(stderr, "failed to create node\n");
        free_queue(&head, &tail);
        return 1;
    }
    if (enqueue(&head, &tail, 20) < 0) {
        fprintf(stderr, "failed to create node\n");
        free_queue(&head, &tail);
        return 1;
    }
    if (enqueue(&head, &tail, 30) < 0) {
        fprintf(stderr, "failed to create node\n");
        free_queue(&head, &tail);
        return 1;
    }
    if (enqueue(&head, &tail, 40) < 0) {
        fprintf(stderr, "failed to create node\n");
        free_queue(&head, &tail);
        return 1;
    }

    peek(&head);
    dequeue(&head, &tail);
    peek(&head);
    dequeue(&head, &tail);
    peek(&head);

    // print_queue(head);
    free_queue(&head, &tail);

}

node *create_node(int data) {
    node *n = malloc(sizeof(node));
    if (!n) {
        return NULL;
    }

    n->next = NULL;
    n->data = data;

    return n;
}

int enqueue(node **head, node **tail, int data) {
    node *n = create_node(data);
    if (!n) {
        return -1;
    }

    if (!*tail) {
        *tail = n;
        *head = n;
        return 0;
    }

    (*tail)->next = n;
    *tail = n;

    return 0;
}

void dequeue(node **head, node **tail) {
    if (!*head) {
        return;
    }

    node *next = (*head)->next;
    free(*head);
    *head = next;
    if (!*head) {
        *tail = NULL;
    }
}

void peek(node **head) {
    if (!*head) {
        return;
    }

    printf("%d\n", (*head)->data);
}

void print_queue(node *head) {
    for (node *ptr = head; ptr != NULL; ptr = ptr->next) {
        printf("%d\n", ptr->data);
    }
}

void free_queue(node **head, node **tail) {
    node *ptr = *head;
    while (ptr != NULL) {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }

    *head = NULL;
    *tail = NULL;
}
