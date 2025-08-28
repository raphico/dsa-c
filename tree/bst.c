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
    int *arr;
    size_t size;
    size_t capacity;
} collector_t;

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

void collect_node(int data, void *ctx) {
    collector_t *col = ctx;
    if (col->size < col->capacity) {
        col->arr[col->size++] = data;
    }
}

void preorder(node_t *root, void (*visit)(int, void *), void *ctx) {
    if (!root) {
        return;
    }

    visit(root->data, ctx);
    preorder(root->left, visit, ctx);
    preorder(root->right, visit, ctx);
}

void inorder(node_t *root, void (*visit)(int, void *), void *ctx) {
    if (!root) {
        return;
    }

    inorder(root->left, visit, ctx);
    visit(root->data, ctx);
    inorder(root->right, visit, ctx);
}

void postorder(node_t *root, void(*visit)(int, void *), void *ctx) {
    if (!root) {
        return;
    }

    postorder(root->left, visit, ctx);
    postorder(root->right, visit, ctx);
    visit(root->data, ctx); 
}

int main() {
    int buf[100];
    collector_t col = {buf, 0, 100};

    bst_t bst;
    init_bst(&bst);

    insert(&bst, 5);
    insert(&bst, 2);
    insert(&bst, 8);
    insert(&bst, 1);
    insert(&bst, 3);
    insert(&bst, 7);
    insert(&bst, 9);

    // preorder(bst.root, collect_node, &col);
    // inorder(bst.root, collect_node, &col);
    postorder(bst.root, collect_node, &col);

    for (int i = 0, n = col.size; i < n; i++) {
        printf("%d ", col.arr[i]);
    }
    printf("\n");

    cleanup_bst(&bst);
    return 0;
}
