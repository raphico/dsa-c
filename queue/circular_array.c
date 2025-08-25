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

bool enqueue(queue *q, int data);
bool dequeue(queue *q, int *rval);
void peek(queue *q);
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

    int rval;
    dequeue(&q, &rval);
    // peek(&q);
    enqueue(&q, 60);


    print_queue(&q);
}

bool isEmpty(queue *q) {
    return q->size == 0;
}

bool isFull(queue *q) {
    return q->size == QUEUE_CAPACITY;
}

void peek(queue *q) {
    if (isEmpty(q)) {
        printf("empty\n");
        return;
    }

    printf("%d\n", q->data[q->front]);
}

bool enqueue(queue *q, int data) {
    if (isFull(q)) {
        return false;
    }

    int i = (q->rear + 1) % QUEUE_CAPACITY;
    q->data[i] = data;
    q->rear = i;
    q->size++;
    
    return true;
}

bool dequeue(queue *q, int *rval) {
    if (isEmpty(q)) {
        return false;
    }

    *rval = q->data[q->front];
    q->front = (q->front + 1) % QUEUE_CAPACITY;
    q->size--;

    return true;
}

void print_queue(queue *q) {
    if (isEmpty(q)) {
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
