#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

typedef struct {
    node *front;
    node *rear;
    size_t size;
} queue;

void free_queue(queue *q);
void init_queue(queue *q);

int enqueue(queue *q, int data);
int dequeue(queue *q, int *rval);
int peek(queue *q, int *val);
bool is_empty(queue *q);

int main() {
    queue q;
    init_queue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    int val;
    if (peek(&q, &val) == 0) {
        printf("Peek: %d\n", val);
    }

    while (!is_empty(&q)) {
        if (dequeue(&q, &val) == 0) {
            printf("Dequeued: %d\n", val);
        }
    }

    free_queue(&q);
    return 0;
}

void init_queue(queue *q) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

int enqueue(queue *q, int data) {
    node *n = malloc(sizeof(node));
    if (!n) {
        return -1;
    }

    n->next = NULL;
    n->data = data;

    if (!q->rear) {
        q->front = q->rear = n;
    } else {
        q->rear->next = n;
        q->rear = n;
    }

    q->size++;
    return 0;
}

int dequeue(queue *q, int *rval) {
    if (!q->front) {
        return -1;
    }

    node *tmp = q->front;
    *rval = tmp->data;

    q->front = q->front->next;
    if (!q->front) {
        q->rear = NULL;
    }

    free(tmp);
    q->size--;
    return 0;
}

int peek(queue *q, int *val) {
    if (!q->front) {
        return -1;
    }

    *val = q->front->data;
    return 0;
}

void print_queue(node *head) {
    for (node *ptr = head; ptr != NULL; ptr = ptr->next) {
        printf("%d\n", ptr->data);
    }
}

void free_queue(queue *q) {
    node *ptr = q->front;
    while (ptr != NULL) {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }

    q->front = NULL;
    q->rear = NULL;
}

bool is_empty(queue *q) { return q->size == 0; }
