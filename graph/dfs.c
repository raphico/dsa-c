#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct neighbor_t {
    int vertex;
    int weight;
    struct neighbor_t *next;
} neighbor_t;

typedef struct {
    neighbor_t **adj;
    size_t size;
} weighted_adjacency_list_t;

typedef struct {
    int *path;
    int path_len;
} dfs_result_t;

dfs_result_t *dfs(weighted_adjacency_list_t *graph, int source, int needle);

int main() {
    weighted_adjacency_list_t graph;
    int data[7][7] = {
        {0, 3, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 7, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0}, {0, 1, 0, 5, 0, 2, 0}, {0, 0, 18, 0, 0, 0, 1},
        {0, 0, 0, 1, 0, 0, 0},
    };

    graph.size = 7;
    graph.adj = malloc(sizeof(neighbor_t *) * graph.size);
    for (int i = 0; i < graph.size; i++) {
        graph.adj[i] = NULL;
    }

    for (int i = 0; i < graph.size; i++) {
        for (int j = 0; j < graph.size; j++) {
            if (data[i][j] != 0) {
                neighbor_t *n = malloc(sizeof(neighbor_t));
                n->vertex = j;
                n->weight = data[i][j];
                n->next = graph.adj[i];
                graph.adj[i] = n;
            }
        }
    }

    dfs_result_t *result = dfs(&graph, 0, 6);
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
        neighbor_t *curr = graph.adj[i];
        while (curr) {
            neighbor_t *tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
    free(graph.adj);

    return 0;
}

bool dfs_recur(weighted_adjacency_list_t *graph, int curr, int needle,
               bool *visited, int *path, int *path_len) {
    if (curr == needle) {
        path[*path_len] = curr;
        (*path_len)++;
        return true;
    }

    if (visited[curr]) {
        return false;
    }

    path[*path_len] = curr;
    (*path_len)++;
    visited[curr] = true;

    for (neighbor_t *edge = graph->adj[curr]; edge != NULL; edge = edge->next) {
        if (dfs_recur(graph, edge->vertex, needle, visited, path, path_len)) {
            return true;
        }
    }

    (*path_len)--;
    return false;
}

dfs_result_t *dfs(weighted_adjacency_list_t *graph, int source, int needle) {
    dfs_result_t *dfs_result = malloc(sizeof(dfs_result_t));
    if (!dfs_result) {
        return NULL;
    }

    dfs_result->path = malloc(sizeof(int) * graph->size);
    if (!dfs_result->path) {
        free(dfs_result);
        return NULL;
    }
    dfs_result->path_len = 0;

    bool *visited = calloc(graph->size, sizeof(bool));
    if (!visited) {
        free(dfs_result->path);
        free(dfs_result);
        return NULL;
    }

    if (!dfs_recur(graph, source, needle, visited, dfs_result->path,
                   &dfs_result->path_len)) {
        free(dfs_result->path);
        free(visited);
        free(dfs_result);
        return NULL;
    }

    free(visited);
    return dfs_result;
}
