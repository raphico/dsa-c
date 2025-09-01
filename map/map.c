#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct kv_pair_t {
    char *key;
    void *value;
    struct kv_pair_t *next;
} kv_pair_t;

typedef struct {
    kv_pair_t **buckets;
    size_t num_buckets;
    size_t size;
} hashmap_t;

hashmap_t *hashmap_create(size_t num_buckets);
void hashmap_destroy(hashmap_t *map);

size_t hashmap_hash(hashmap_t *map, const char *key);
int hashmap_insert(hashmap_t *map, const char *key, void *value);
int hashmap_update(hashmap_t *map, const char *key, void *value);
void *hashmap_get(hashmap_t *map, const char *key);
int hashmap_delete(hashmap_t *map, const char *key);
int hashmap_resize(hashmap_t *map, size_t new_num_buckets);

hashmap_t *hashmap_create(size_t num_buckets) {
    hashmap_t *map = malloc(sizeof(hashmap_t));
    if (!map) {
        return NULL;
    }

    map->buckets = calloc(num_buckets, sizeof(kv_pair_t *));
    if (!map->buckets) {
        free(map);
        return NULL;
    }
    map->num_buckets = num_buckets;
    map->size = 0;

    return map;
}

void hashmap_destroy(hashmap_t *map) {
    if (!map) {
        return;
    }

    for (size_t i = 0, n = map->num_buckets; i < n; i++) {
        kv_pair_t *ptr = map->buckets[i];
        while (ptr != NULL) {
            kv_pair_t *next = ptr->next;
            free(ptr->key);
            free(ptr);
            ptr = next;
        }
    }

    free(map->buckets);
    free(map);
}

unsigned long djb2_hash(const char *key) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

size_t hashmap_hash(hashmap_t *map, const char *key) {
    return djb2_hash(key) % map->num_buckets;
}

int hashmap_insert(hashmap_t *map, const char *key, void *value) {
    if (!map) {
        return -1;
    }

    kv_pair_t *kv_pair = malloc(sizeof(kv_pair_t));
    if (!kv_pair) {
        return -1;
    }

    if ((double)map->size / map->num_buckets > 0.7) {
        hashmap_resize(map, map->num_buckets * 2);
    }

    size_t hash = hashmap_hash(map, key);

    kv_pair->key = strdup(key);
    kv_pair->value = value;

    kv_pair->next = map->buckets[hash];
    map->buckets[hash] = kv_pair;
    map->size++;

    return 0;
}

int hashmap_update(hashmap_t *map, const char *key, void *value) {
    if (!map) {
        return -1;
    }

    size_t hash = hashmap_hash(map, key);
    for (kv_pair_t *ptr = map->buckets[hash]; ptr != NULL; ptr = ptr->next) {
        if (strcmp(ptr->key, key) == 0) {
            ptr->value = value;
            return 0;
        }
    }

    return -1;
}

void *hashmap_get(hashmap_t *map, const char *key) {
    if (!map) {
        return NULL;
    }

    size_t hash = hashmap_hash(map, key);
    for (kv_pair_t *ptr = map->buckets[hash]; ptr != NULL; ptr = ptr->next) {
        if (strcmp(ptr->key, key) == 0) {
            return ptr->value;
        }
    }

    return NULL;
}

int hashmap_delete(hashmap_t *map, const char *key) {
    if (!map) {
        return -1;
    }

    size_t hash = hashmap_hash(map, key);
    kv_pair_t *curr = map->buckets[hash];
    kv_pair_t *prev = NULL;

    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            if (prev) {
                prev->next = curr->next;
            } else {
                map->buckets[hash] = curr->next;
            }

            free(curr->key);
            free(curr);
            map->size--;
            return 0;
        }

        prev = curr;
        curr = curr->next;
    }

    return -1;
}

int hashmap_resize(hashmap_t *map, size_t new_num_buckets) {
    if (!map || new_num_buckets == 0) {
        return -1;
    }

    kv_pair_t **new_buckets = calloc(new_num_buckets, sizeof(kv_pair_t *));
    if (!new_buckets) {
        return -1;
    }

    for (size_t i = 0, n = map->num_buckets; i < n; i++) {
        kv_pair_t *curr = map->buckets[i];
        while (curr) {
            kv_pair_t *next = curr->next;
            size_t hash = djb2_hash(curr->key) % new_num_buckets;

            curr->next = new_buckets[hash];
            new_buckets[hash] = curr;

            curr = next;
        }
    }

    free(map->buckets);

    map->buckets = new_buckets;
    map->num_buckets = new_num_buckets;

    return 0;
}
