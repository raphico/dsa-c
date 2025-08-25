#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t top;
    size_t capacity;
} stack;

int init_stack(stack *s, size_t capacity);
void free_stack(stack *s);

bool is_empty(const stack *s);
bool is_full(const stack *s);
int push(stack *s, int data);
int pop(stack *s, int *rval);
int peek(stack *s, int *val);

int main() {
    stack s;
    init_stack(&s, 4);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    push(&s, 40);
    push(&s, 50);

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

int init_stack(stack *s, size_t capacity) {
    s->data = malloc(sizeof(int) * capacity);
    if (!s->data) {
        return -1;
    }
    s->capacity = capacity;
    s->top = 0;
    return 0;
}

bool is_empty(const stack *s) {
    return s->top == 0;
}

bool is_full(const stack *s) {
    return s->capacity == s->top;
}

int push(stack *s, int data) {
    if (is_full(s)) {
        size_t new_cap = s->capacity * 2;
        int *new_data = realloc(s->data, new_cap * sizeof(int));
        if (!s->data) {
            return -1;
        }
        s->data = new_data;
        s->capacity = new_cap;
    }

    s->data[s->top++] = data;
    return 0;
}

int pop(stack *s, int *rval) {
    if (is_empty(s)) {
        return -1;
    }

    *rval = s->data[--s->top];
    return 0;
}

int peek(stack *s, int *val) {
    if (is_empty(s)) {
        return -1;
    }

    *val = s->data[s->top - 1];
    return 0;
}

void free_stack(stack *s) {
    free(s->data);
    s->top = 0;
}