#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

typedef struct {
    node *front;
    node *rear;
} queue;

node *create_node(int data);
int enqueue(queue *q, int data);
int dequeue(queue *q, int *rval);
int peek(queue *q, int *val);
void free_queue(queue *q);

int main() {
    queue q = {
        .front = NULL,
        .rear = NULL
    };

    if (enqueue(&q, 10)) {
        fprintf(stderr, "failed to create node\n");
        free_queue(&q);
        return 1;
    }
    if (enqueue(&q, 20)) {
        fprintf(stderr, "failed to create node\n");
        free_queue(&q);
        return 1;
    }
    if (enqueue(&q, 30)) {
        fprintf(stderr, "failed to create node\n");
        free_queue(&q);
        return 1;
    }
    if (enqueue(&q, 40)) {
        fprintf(stderr, "failed to create node\n");
        free_queue(&q);
        return 1;
    }

    int val;
    if (peek(&q, &val) == 0) {
        printf("Peek: %d\n", val);
    }

    while (dequeue(&q, &val) == 0) {
        printf("Dequeued: %d\n", val);
    }

    free_queue(&q);
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

int enqueue(queue *q, int data) {
    node *n = create_node(data);
    if (!n) {
        return -1;
    }

    if (!q->rear) {
        q->front = q->rear = n;
        return 0;
    }

    q->rear->next = n;
    q->rear = n;

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
