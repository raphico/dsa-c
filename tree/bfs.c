#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
    int data;
    struct node_t *left;
    struct node_t *right;
} node_t;

typedef struct {
    node_t *root;
    size_t size;
} bst_t;

typedef struct {
    node_t **items;
    int front;
    int rear;
    size_t capacity;
} queue_t;

void init_bst(bst_t *bst) {
    bst->root = NULL;
    bst->size = 0;
}

void cleanup_nodes(node_t *root) {
    if (!root) {
        return;
    }
    
    cleanup_nodes(root->left);
    cleanup_nodes(root->right);
    free(root);
}

void cleanup_bst(bst_t *bst) {
    if (!bst) {
        return;
    }

    cleanup_nodes(bst->root);
    bst->root = NULL;
    bst->size = 0;
}

node_t *insert_node(node_t *root, node_t *new_node) {
    if (!root) {
        return new_node;
    }

    if (new_node->data > root->data) {
        root->right = insert_node(root->right, new_node);
    } else if (new_node->data < root->data) {
        root->left = insert_node(root->left, new_node);
    }

    return root;
}

int insert(bst_t *bst, int data) {
    if (!bst) {
        return -1;
    }

    node_t *n = malloc(sizeof(node_t));
    if (!n) {
        return -1;
    }

    n->data = data;
    n->left = n->right = NULL;
    bst-> root = insert_node(bst->root, n);
    bst->size++;

    return 0;
}

queue_t *create_queue(size_t capacity) {
    queue_t *q = malloc(sizeof(queue_t));
    if (!q) {
        return NULL;
    }

    q->capacity = capacity;
    q->front = 0;
    q->rear = 0;
    q->items = malloc(sizeof(node_t*) * capacity);

    return q;
}

void free_queue(queue_t *q) {
    free(q->items);
    free(q);
}

int enqueue(queue_t *q, node_t *n) {
    if (!q) {
        return -1;
    }

    q->items[q->rear++] = n;
    return 0;
}

int dequeue(queue_t *q, node_t **out) {
    if (!q)  {
        return -1;
    }

    *out = q->items[q->front++];
    return 0;
}

bool is_empty(queue_t *q) {
    return q->rear == q->front;
}

int bfs(bst_t *bst, int needle, bool *found) {
    queue_t *q = create_queue(bst->size);
    if (!q) {
        return -1;
    }

    *found = false;

    if (enqueue(q, bst->root) < 0) {
        free_queue(q);
        return -1;
    }

    while (!is_empty(q)) {
        node_t *curr;
        dequeue(q, &curr);

        // Uncomment to show the BFS traversal order
        // printf("%d ", curr->data);

        if (curr->data == needle) {
            *found = true;
            break;
        }

        if (curr->left) {
            if (enqueue(q, curr->left) < 0) {
                free_queue(q);
                return -1;
            }
        }

        if (curr->right) {
            if (enqueue(q, curr->right) < 0) {
                free_queue(q);
                return -1;
            }
        }
    }

    free_queue(q);
    return 0;
}

int main() {
    bst_t bst;
    init_bst(&bst);

    insert(&bst, 5);
    insert(&bst, 2);
    insert(&bst, 8);
    insert(&bst, 1);
    insert(&bst, 3);
    insert(&bst, 7);
    insert(&bst, 9);

    bool found = false;
    bfs(&bst, 10, &found);

    printf("%d\n", found);

    cleanup_bst(&bst);
    return 0;
}
