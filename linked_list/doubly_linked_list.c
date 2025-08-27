#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} node_t;

typedef struct {
    node_t *head;
    node_t *tail;
    size_t length;
} dlist_t;

void init_dlist(dlist_t *dlist) {
    if (!dlist) {
        return;
    }

    dlist->head = NULL;
    dlist->tail = NULL;
    dlist->length = 0;
}

void cleanup_dlist(dlist_t *dlist) {
    if (!dlist) {
        return;
    }

    node_t *ptr = dlist->head;
    while (ptr != NULL) {
        node_t *next = ptr->next;
        free(ptr);
        ptr = next;
    }

    dlist->length = 0;
    dlist->head = dlist->tail = NULL;
}

int preappend(dlist_t *dlist, int data) {
    if (!dlist) {
        return -1;
    }

    node_t *n = malloc(sizeof(node_t));
    if (!n) {
        return -1;
    }

    n->data = data;
    n->prev = NULL;

    if (dlist->head == NULL) {
        n->next = NULL;
        dlist->head = dlist->tail = n;
    } else {
        n->next = dlist->head;
        dlist->head->prev = n;
        dlist->head = n;
    }

    dlist->length++;
    return 0;
}

int append(dlist_t *dlist, int data) {
    node_t *n = malloc(sizeof(node_t));
    if (!n) {
        return -1;
    }

    n->data = data;
    n->next = NULL;

    if (dlist->head == NULL) {
        n->prev = NULL;
        dlist->head = dlist->tail = n;
    } else {
        n->prev = dlist->tail;
        dlist->tail->next = n;
        dlist->tail = n;
    }

    dlist->length++;
    return 0;
}

int rm(dlist_t *dlist, int data) {
    if (!dlist) {
        return -1;
    }

    node_t *ptr = dlist->head;
    while (ptr != NULL) {
        node_t *next = ptr->next;

        if (ptr->data == data) {
            if (ptr->prev) {
                ptr->prev->next = ptr->next;
            } else {
                dlist->head = ptr->next;
            }

            if (ptr->next) {
                ptr->next->prev = ptr->prev;
            } else {
                dlist->tail = ptr->prev;
            }

            free(ptr);
            dlist->length--;
        }

        ptr = next;
    }

    return 0;
}

int get(dlist_t *dlist, size_t index, int *data) {
    if (!dlist || !data || index >= dlist->length) {
        return -1;
    }

    node_t *ptr = dlist->head;
    for (size_t i = 0; i < index; i++) {
        ptr = ptr->next;
    }

    *data = ptr->data;
    return 0;
}

int rmAt(dlist_t *dlist, size_t index) {
    if (!dlist || index >= dlist->length) {
        return -1;
    }

    node_t *ptr = dlist->head;
    for (size_t i = 0; i < index; i++) {
        ptr = ptr->next;
    }

    if (ptr->prev) {
        ptr->prev->next = ptr->next;
    } else {
        dlist->head = ptr->next;
    }

    if (ptr->next) {
        ptr->next->prev = ptr->prev;
    } else {
        dlist->tail = ptr->prev;
    }

    free(ptr);
    dlist->length--;
    return 0;
}

int insertAt(dlist_t *dlist, size_t index, int data) {
    if (!dlist || index > dlist->length) {
        return -1;
    }

    if (index == 0) {
        return preappend(dlist, data);
    }

    if (index == dlist->length) {
        return append(dlist, data);
    }

    node_t *ptr = dlist->head;
    for (size_t i = 0; i < index; i++) {
        ptr = ptr->next;
    }

    node_t *n = malloc(sizeof(node_t));
    if (!n) {
        return -1;
    }

    n->data = data;
    n->next = ptr;
    n->prev = ptr->prev;
    ptr->prev->next = n;
    ptr->prev = n;

    dlist->length++;
    return 0;
}

int main() {
    dlist_t dlist;
    init_dlist(&dlist);

    preappend(&dlist, 1);
    preappend(&dlist, 2);
    append(&dlist, 3);
    append(&dlist, 4);

    rm(&dlist, 2);

    int data;
    get(&dlist, 0, &data);
    printf("%d\n", data);
    printf("%zu\n", dlist.length);

    insertAt(&dlist, 2, 5);
    printf("%zu\n", dlist.length);

    get(&dlist, 2, &data);
    printf("%d\n", data);

    cleanup_dlist(&dlist);
    return 0;
}
