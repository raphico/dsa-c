#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct edge_t {
    int vertex;
    int weight;
    struct edge_t *next;
} edge_t;

typedef struct {
    edge_t **adj;   
    size_t size;    
} graph_t;

typedef struct {
    int *dist;      
    int *prev;      
} dijkstra_result_t;

typedef struct {
    int vertex;
    int dist;
} heap_entry_t;

typedef struct {
    heap_entry_t *data;
    size_t size;
    size_t capacity;
} heap_t;

heap_t *heap_create(size_t capacity);
void heap_destroy(heap_t *h);
int heap_push(heap_t *h, int vertex, int dist);
int heap_pop(heap_t *h, heap_entry_t *out);
bool heap_empty(heap_t *h);
bool heap_full(heap_t *h);

dijkstra_result_t *dijkstra(graph_t *g, int source, int sink) {
    dijkstra_result_t *res = malloc(sizeof(dijkstra_result_t));
    if (!res) return NULL;

    res->dist = malloc(sizeof(int) * g->size);
    if (!res->dist) {
        free(res);
        return NULL;
    }
    for (size_t i = 0; i < g->size; i++) {
        res->dist[i] = INT_MAX;
    }

    res->prev = malloc(sizeof(int) * g->size);
    if (!res->prev) {
        free(res->dist);
        free(res);
        return NULL;
    }
    for (size_t i = 0; i < g->size; i++) {
        res->prev[i] = -1;
    }

    heap_t *heap = heap_create(g->size);
    if (!heap) {
        free(res->dist);
        free(res->prev);
        free(res);
        return NULL;
    }

    res->dist[source] = 0;
    heap_push(heap, source, 0);

    while (!heap_empty(heap)) {
        heap_entry_t curr;
        heap_pop(heap, &curr);

        if (curr.vertex == sink) break;

        for (edge_t *e = g->adj[curr.vertex]; e; e = e->next) {
            int new_dist = res->dist[curr.vertex] + e->weight;
            if (new_dist < res->dist[e->vertex]) {
                res->dist[e->vertex] = new_dist;
                res->prev[e->vertex] = curr.vertex;
                heap_push(heap, e->vertex, new_dist);
            }
        }
    }

    heap_destroy(heap);
    return res;
}

heap_t *heap_create(size_t capacity) {
    heap_t *h = malloc(sizeof(heap_t));
    if (!h) return NULL;

    h->data = malloc(sizeof(heap_entry_t) * capacity);
    if (!h->data) {
        free(h);
        return NULL;
    }

    h->size = 0;
    h->capacity = capacity;
    return h;
}

void heap_destroy(heap_t *h) {
    if (!h) return;
    free(h->data);
    free(h);
}

bool heap_full(heap_t *h) {
    return h->size == h->capacity;
}

bool heap_empty(heap_t *h) {
    return h->size == 0;
}

static void heap_sift_up(heap_t *h, int i) {
    if (i == 0) return;

    int parent = (i - 1) / 2;
    if (h->data[i].dist >= h->data[parent].dist) return;

    heap_entry_t tmp = h->data[parent];
    h->data[parent] = h->data[i];
    h->data[i] = tmp;

    heap_sift_up(h, parent);
}

int heap_push(heap_t *h, int vertex, int dist) {
    if (!h || heap_full(h)) return -1;

    heap_entry_t entry = { .vertex = vertex, .dist = dist };
    h->data[h->size++] = entry;
    heap_sift_up(h, h->size - 1);
    return 0;
}

static void heap_sift_down(heap_t *h, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;

    if (left < (int)h->size && h->data[left].dist < h->data[smallest].dist)
        smallest = left;

    if (right < (int)h->size && h->data[right].dist < h->data[smallest].dist)
        smallest = right;

    if (smallest != i) {
        heap_entry_t tmp = h->data[i];
        h->data[i] = h->data[smallest];
        h->data[smallest] = tmp;
        heap_sift_down(h, smallest);
    }
}

int heap_pop(heap_t *h, heap_entry_t *out) {
    if (!h || h->size == 0) return -1;

    *out = h->data[0];
    h->data[0] = h->data[--h->size];
    heap_sift_down(h, 0);
    return 0;
}
