#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct node_t {
    int data;
    struct node_t *left;
    struct node_t *right;
} node_t;

typedef struct {
    node_t *root;
    size_t size;
} bt_t;

bool compare(node_t *a, node_t *b) {
    if (!a && !b) {
        return true;
    }

    if ((a == NULL) != (b == NULL)) {
        return false;
    }
    
    if (a->data != b->data) {
        return false;
    }

    return compare(a->left, b->left) && compare(a->right, b->right);
}
