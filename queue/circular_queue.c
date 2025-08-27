#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define QUEUE_CAPACITY 5

typedef struct {
    int data[QUEUE_CAPACITY];
    int front;
    int rear;
    size_t size;
} queue;

void init_queue(queue *q);
bool is_empty(queue *q);

int enqueue(queue *q, int data);
int dequeue(queue *q, int *rval);
int peek(queue *q, int *val);
void print_queue(queue *q);

int main(void) {
    queue q;
    q.front = 0;
    q.rear = -1;
    q.size = 0;

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);

    int val;
    if (peek(&q, &val) == 0) {
        printf("Peek: %d\n", val);
    }

    if (dequeue(&q, &val) == 0) {
        printf("Dequeued: %d\n", val);
    }

    enqueue(&q, 60);

    if (peek(&q, &val) == 0) {
        printf("Peek: %d\n", val);
    }

    while (!is_empty(&q)) {
        if (dequeue(&q, &val) == 0) {
            printf("Dequeued: %d\n", val);
        }
    }

    return 0;
}

bool is_empty(queue *q) { return q->size == 0; }

bool is_full(queue *q) { return q->size == QUEUE_CAPACITY; }

int peek(queue *q, int *val) {
    if (is_empty(q)) {
        return -1;
    }

    *val = q->data[q->front];
    return 0;
}

int enqueue(queue *q, int data) {
    if (is_full(q)) {
        return -1;
    }

    int i = (q->rear + 1) % QUEUE_CAPACITY;
    q->data[i] = data;
    q->rear = i;
    q->size++;

    return 0;
}

int dequeue(queue *q, int *rval) {
    if (is_empty(q)) {
        return -1;
    }

    *rval = q->data[q->front];
    q->front = (q->front + 1) % QUEUE_CAPACITY;
    q->size--;

    return 0;
}

void print_queue(queue *q) {
    if (is_empty(q)) {
        printf("empty\n");
        return;
    }

    for (int i = q->front; true; i = (i + 1) % QUEUE_CAPACITY) {
        printf("%d\n", q->data[i]);
        if (i == q->rear) {
            return;
        }
    }
}
