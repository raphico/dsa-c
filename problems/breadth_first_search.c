#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} point;

typedef struct {
    point *data;
    int front;
    int rear;
    size_t capacity;
} queue;

typedef struct {
    point *steps;
    int length;
} path;

queue *create_queue(size_t capacity);
void free_queue(queue *q);

bool is_empty(queue *q);
int dequeue(queue *q, point *out);
int enqueue(queue *q, point p);
path bfs_maze_solver(char **maze, int height, int width, char wall, point start,
                     point end);

int main() {
    char *maze[] = {"..#", "#.#", "#.."};

    point start = {0, 0};
    point end = {2, 2};

    path p = bfs_maze_solver(maze, 3, 3, '#', start, end);
    if (p.length == 0) {
        printf("No path found\n");
    }

    printf("Path found (%d steps):\n", p.length);
    for (int i = 0; i < p.length; i++) {
        printf("(%d, %d)\n", p.steps[i].x, p.steps[i].y);
    }

    free(p.steps);
    return 0;
}

path bfs_maze_solver(char **maze, int height, int width, char wall, point start,
                     point end) {
    path result = {0, NULL};

    bool *visited = calloc(height * width, sizeof(bool));
    if (!visited) {
        return result;
    }

    point *prev = malloc(sizeof(point) * width * height);
    if (!prev) {
        free(visited);
        return result;
    }
    for (int i = 0, n = height * width; i < n; i++) {
        prev[i].x = -1;
        prev[i].y = -1;
    }

    queue *q = create_queue(height * width);
    if (!q) {
        free(visited);
        free(prev);
        return result;
    }

    if (enqueue(q, start) < 0) {
        free(visited);
        free(prev);
        free_queue(q);
        return result;
    }

    visited[start.y * width + start.x] = true;

    bool found = false;
    point moves[] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    while (!is_empty(q)) {
        point curr;
        dequeue(q, &curr);

        if (curr.x == width - 1 && curr.y == height - 1) {
            found = true;
            break;
        }

        for (int i = 0; i < 4; i++) {
            point next = {.x = moves[i].x + curr.x, .y = moves[i].y + curr.y};

            if (next.x < 0 || next.y < 0 || next.x >= width ||
                next.y >= height) {
                continue;
            } else if (maze[next.y][next.x] == wall) {
                continue;
            } else if (visited[next.y * width + next.x]) {
                continue;
            }

            enqueue(q, next);
            visited[next.y * width + next.x] = true;
            prev[next.y * width + next.x] = curr;
        }
    }

    free_queue(q);
    free(visited);

    if (!found) {
        free(prev);
        return result;
    }

    result.steps = malloc(sizeof(point) * height * width);
    if (!result.steps) {
        free_queue(q);
        free(prev);
        return result;
    }

    int len = 0;
    point at = end;
    while (at.x != -1 && at.y != -1) {
        result.steps[len++] = at;
        at = prev[at.y * width + at.x];
    }
    free(prev);

    for (int i = 0; i < len / 2; i++) {
        point tmp = result.steps[i];
        result.steps[i] = result.steps[len - i - 1];
        result.steps[len - i - 1] = tmp;
    }

    result.length = len;
    return result;
}

queue *create_queue(size_t capacity) {
    queue *q = malloc(sizeof(queue));
    if (!q) {
        return NULL;
    }

    q->front = 0;
    q->rear = 0;
    q->capacity = capacity;

    q->data = malloc(sizeof(point) * capacity);
    if (!q->data) {
        free(q);
        return NULL;
    }

    return q;
}

bool is_full(queue *q) { return q->rear == q->capacity; }

bool is_empty(queue *q) { return q->rear == q->front; }

int enqueue(queue *q, point p) {
    if (!q) {
        return -1;
    }

    q->data[q->rear++] = p;
    return 0;
}

int dequeue(queue *q, point *out) {
    if (!q) {
        return -1;
    }

    *out = q->data[q->front++];
    return 0;
}

void free_queue(queue *q) {
    free(q->data);
    free(q);
}
