#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node;

typedef struct {
    node *top;
    size_t size;
} stack;

void init_stack(stack *s);
void free_stack(stack *s);

bool is_empty(const stack *s);
int push(stack *s, int data);
int pop(stack *s, int *rval);
int peek(stack *s, int *val);

int main() {
    stack s;
    init_stack(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    push(&s, 40);

    int val;
    if (peek(&s, &val) == 0) {
        printf("Peek: %d\n", val);
    }

    while (!is_empty(&s)) {
        if (pop(&s, &val) == 0) {
            printf("Popped: %d\n", val);
        }
    }

    free_stack(&s);
    return 0;
}

void init_stack(stack *s) {
    s->top = NULL;
    s->size = 0;
}

bool is_empty(const stack *s) { return s->size == 0; }

int push(stack *s, int data) {
    node *n = malloc(sizeof(node));
    if (!n) {
        return -1;
    }

    n->data = data;
    n->next = s->top;
    s->top = n;
    s->size++;

    return 0;
}

int peek(stack *s, int *val) {
    if (!s->top) {
        return -1;
    }

    *val = s->top->data;
    return 0;
}

int pop(stack *s, int *rval) {
    if (!s->top) {
        return -1;
    }

    node *tmp = s->top;
    *rval = tmp->data;
    s->top = s->top->next;

    free(tmp);
    s->size--;
    return 0;
}

void free_stack(stack *s) {
    node *ptr = s->top;
    while (ptr != NULL) {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }

    s->top = NULL;
    s->size = 0;
}
