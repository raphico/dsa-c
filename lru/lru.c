#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lru_node_t {
    char *key;
    void *data;
    struct lru_node_t *prev;
    struct lru_node_t *next;
    struct lru_node_t *bucket_next;
} lru_node_t;

typedef struct {
    lru_node_t **buckets;
    size_t num_buckets;

    lru_node_t *head, *tail;

    size_t size;
    size_t capacity;
} lru_cache_t;

lru_cache_t *lru_cache_create(size_t capacity, size_t num_buckets) {
    lru_cache_t *cache = malloc(sizeof(lru_cache_t));
    if (!cache) {
        return NULL;
    }

    cache->buckets = calloc(num_buckets, sizeof(lru_node_t *));
    if (!cache->buckets) {
        free(cache);
        return NULL;
    }

    cache->capacity = capacity;
    cache->num_buckets = num_buckets;
    cache->size = 0;
    cache->head = cache->tail = NULL;

    return cache;
}

void lru_cache_destroy(lru_cache_t *cache) {
    if (!cache) {
        return;
    }

    lru_node_t *ptr = cache->head;
    while (ptr) {
        lru_node_t *next = ptr->next;
        free(ptr->key);
        free(ptr);
        ptr = next;
    }

    free(cache->buckets);
    free(cache);
}

unsigned long djb2_hash(const char *key) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

void move_to_head(lru_cache_t *cache, lru_node_t *node) {
    if (node == cache->head) {
        return;
    }

    node->prev->next = node->next;

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        cache->tail = node->prev;
    }

    node->prev = NULL;
    node->next = cache->head;
    cache->head->prev = node;
    cache->head = node;
}

size_t lru_cache_hash(lru_cache_t *cache, const char *key) {
    return djb2_hash(key) % cache->num_buckets;
}

void *lru_cache_get(lru_cache_t *cache, const char *key) {
    if (!cache) {
        return NULL;
    }

    size_t hash = lru_cache_hash(cache, key);
    lru_node_t *node = cache->buckets[hash];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            break;
        }
        node = node->bucket_next;
    }

    if (!node) {
        return NULL;
    }

    move_to_head(cache, node);

    return node->data;
}

int lru_cache_delete(lru_cache_t *cache, const char *key) {
    if (!cache) {
        return -1;
    }

    size_t hash = lru_cache_hash(cache, key);
    lru_node_t *curr = cache->buckets[hash];
    lru_node_t *bucket_prev = NULL;
    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            if (curr->prev) {
                curr->prev->next = curr->next;
            } else {
                cache->head = curr->next;
            }

            if (curr->next) {
                curr->next->prev = curr->prev;
            } else {
                cache->tail = curr->prev;
            }

            if (bucket_prev) {
                bucket_prev->bucket_next = curr->bucket_next;
            } else {
                cache->buckets[hash] = curr->bucket_next;
            }

            free(curr->key);
            free(curr);
            cache->size--;
            return 0;
        }

        bucket_prev = curr;
        curr = curr->bucket_next;
    }

    return -1;
}

int lru_cache_put(lru_cache_t *cache, const char *key, void *data) {
    if (!cache) {
        return -1;
    }

    size_t hash = lru_cache_hash(cache, key);
    lru_node_t *ptr = cache->buckets[hash];
    while (ptr) {
        if (strcmp(ptr->key, key) == 0) {
            ptr->data = data;
            move_to_head(cache, ptr);
            return 0;
        }
        ptr = ptr->bucket_next;
    }

    if (cache->size == cache->capacity) {
        lru_cache_delete(cache, cache->tail->key);
    }

    lru_node_t *n = malloc(sizeof(lru_node_t));
    if (!n) {
        return -1;
    }

    n->key = strdup(key);
    n->data = data;

    n->bucket_next = cache->buckets[hash];
    cache->buckets[hash] = n;

    n->prev = NULL;
    if (cache->head) {
        n->next = cache->head;
        cache->head->prev = n;
        cache->head = n;
    } else {
        n->next = NULL;
        cache->head = cache->tail = n;
    }

    cache->size++;
    return 0;
}

int main(void) {
    lru_cache_t *cache = lru_cache_create(3, 5);
    if (!cache) {
        fprintf(stderr, "Failed to create cache\n");
        return 1;
    }

    printf("Inserting A=Apple\n");
    lru_cache_put(cache, "A", "Apple");

    printf("Inserting B=Banana\n");
    lru_cache_put(cache, "B", "Banana");

    printf("Inserting C=Cherry\n");
    lru_cache_put(cache, "C", "Cherry");

    printf("Get A: %s\n", (char *)lru_cache_get(cache, "A")); // should be Apple
    printf("Get B: %s\n",
           (char *)lru_cache_get(cache, "B")); // should be Banana

    printf("Inserting D=Durian (should evict C)\n");
    lru_cache_put(cache, "D", "Durian");

    printf("Get C (should be NULL): %s\n", (char *)lru_cache_get(cache, "C"));
    printf("Get A (still there): %s\n", (char *)lru_cache_get(cache, "A"));
    printf("Get D (just inserted): %s\n", (char *)lru_cache_get(cache, "D"));

    printf("Deleting B...\n");
    lru_cache_delete(cache, "B");
    printf("Get B (should be NULL): %s\n", (char *)lru_cache_get(cache, "B"));

    lru_cache_destroy(cache);
    return 0;
}
