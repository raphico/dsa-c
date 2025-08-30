#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **adj;
    size_t size;
} weighted_adjacency_matrix_t;

typedef struct {
    int *vertices;
    int front;
    int rear;
    size_t capacity;
} queue_t;

typedef struct {
    int *path;
    size_t path_len;
} bfs_result_t;

queue_t *queue_create(size_t capacity);
void queue_free(queue_t *q);

bool queue_is_empty(queue_t *q);
int queue_enqueue(queue_t *q, int vertex);
int queue_dequeue(queue_t *q, int *out);
bfs_result_t *bfs(weighted_adjacency_matrix_t *graph, int source, int needle);

int main() {
    weighted_adjacency_matrix_t graph;
    int data[7][7] = {
        {0, 3, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0}, {0, 0, 7, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0}, {0, 1, 0, 5, 0, 2, 0}, {0, 0, 18, 0, 0, 0, 1},
        {0, 0, 0, 1, 0, 0, 1},
    };

    graph.size = 7;
    graph.adj = malloc(sizeof(int *) * graph.size);
    for (int i = 0; i < graph.size; i++) {
        graph.adj[i] = malloc(sizeof(int) * graph.size);
        for (int j = 0; j < graph.size; j++) {
            graph.adj[i][j] = data[i][j];
        }
    }

    bfs_result_t *result = bfs(&graph, 0, 6);
    if (result) {
        for (int i = 0; i < result->path_len; i++) {
            printf("%d ", result->path[i]);
        }
        printf("\n");

        free(result->path);
        free(result);
    } else {
        printf("No path found\n");
    }

    for (int i = 0; i < graph.size; i++) {
        free(graph.adj[i]);
    }
    free(graph.adj);

    return 0;
}

bfs_result_t *bfs(weighted_adjacency_matrix_t *graph, int source, int needle) {
    bfs_result_t *bfs_result = malloc(sizeof(bfs_result_t));
    if (!bfs_result) {
        return NULL;
    }

    bfs_result->path_len = 0;
    bfs_result->path = NULL;

    int *prev = malloc(sizeof(int) * graph->size);
    if (!prev) {
        free(bfs_result);
        return NULL;
    }

    for (int i = 0, n = graph->size; i < n; i++) {
        prev[i] = -1;
    }

    queue_t *q = queue_create(graph->size);
    if (!q) {
        free(prev);
        free(bfs_result);
        return NULL;
    }

    queue_enqueue(q, source);
    while (!queue_is_empty(q)) {
        int curr;
        queue_dequeue(q, &curr);

        if (curr == needle) {
            break;
        }

        for (int i = 0, n = graph->size; i < n; i++) {
            int neighbor = graph->adj[curr][i];
            if (neighbor == 0) {
                continue;
            }
            if (prev[i] != -1) {
                continue;
            }

            queue_enqueue(q, i);
            prev[i] = curr;
        }
    }

    queue_free(q);

    // a vertex never discovered the needle
    if (prev[needle] == -1) {
        free(prev);
        free(bfs_result);
        return NULL;
    }

    bfs_result->path = malloc(sizeof(int) * graph->size);
    if (!bfs_result->path) {
        free(prev);
        free(bfs_result);
        return NULL;
    }

    int curr = needle;
    int len = 0;
    while (curr != -1) {
        bfs_result->path[len++] = curr;
        curr = prev[curr];
    }

    free(prev);

    for (int i = 0; i < len / 2; i++) {
        int tmp = bfs_result->path[i];
        bfs_result->path[i] = bfs_result->path[len - i - 1];
        bfs_result->path[len - i - 1] = tmp;
    }

    bfs_result->path_len = len;
    return bfs_result;
}

queue_t *queue_create(size_t capacity) {
    queue_t *q = malloc(sizeof(queue_t));
    if (!q) {
        return NULL;
    }

    q->vertices = malloc(sizeof(int) * capacity);
    if (!q->vertices) {
        free(q);
        return NULL;
    }

    q->front = 0;
    q->rear = 0;
    q->capacity = capacity;

    return q;
}

bool queue_is_full(queue_t *q) { return q->rear == q->capacity; }

int queue_enqueue(queue_t *q, int vertex) {
    if (!q || queue_is_full(q)) {
        return -1;
    }

    q->vertices[q->rear++] = vertex;
    q->rear = (q->rear + 1) % q->capacity;
    return 0;
}

int queue_dequeue(queue_t *q, int *out) {
    if (!q || queue_is_empty(q)) {
        return -1;
    }

    *out = q->vertices[q->front];
    q->front = (q->front + 1) % q->capacity;
    return 0;
}

void queue_free(queue_t *q) {
    if (!q) {
        return;
    }

    free(q->vertices);
    free(q);
}

bool queue_is_empty(queue_t *q) { return q->front == q->rear; }
