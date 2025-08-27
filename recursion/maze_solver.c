#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

typedef struct {
    int x;
    int y;
} point;

typedef struct {
    point *steps;
    int length;
} path;

bool dfs(char *maze[], int height, int width, char wall, bool *visited,
         point curr, point end, point *path, int *path_len);
path maze_solver(char *maze[], int height, int width, char wall, point start,
                 point end);

int main() {
    char *maze[] = {"..#", "#.#", "#.."};
    point start = {.x = 0, .y = 0};
    point end = {.x = 2, .y = 2};

    path p = maze_solver(maze, 3, 3, '#', start, end);
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

path maze_solver(char *maze[], int height, int width, char wall, point start,
                 point end) {
    path result = {.length = 0, .steps = NULL};

    bool *visited = calloc(height * width, sizeof(bool));
    if (!visited) {
        return result;
    }

    int path_len = 0;
    point *path = calloc(height * width, sizeof(point));
    if (!dfs(maze, height, width, wall, visited, start, end, path, &path_len)) {
        free(visited);
        return result;
    }

    result.length = path_len;
    result.steps = path;

    free(visited);
    return result;
}

bool dfs(char *maze[], int height, int width, char wall, bool *visited,
         point curr, point end, point *path, int *path_len) {
    if (curr.x < 0 || curr.y < 0 || curr.x >= width || curr.y >= height) {
        return false;
    }

    if (maze[curr.y][curr.x] == wall) {
        return false;
    }

    if (curr.x == end.x && curr.y == end.y) {
        path[*path_len] = curr;
        (*path_len)++;
        return true;
    }

    if (visited[curr.y * width + curr.x]) {
        return false;
    }

    path[*path_len] = curr;
    (*path_len)++;
    visited[curr.y * width + curr.x] = true;

    point moves[] = {
        {.x = 1, .y = 0},
        {.x = -1, .y = 0},
        {.x = 0, .y = 1},
        {.x = 0, .y = -1},
    };
    for (int i = 0; i < 4; i++) {
        point p = {.x = curr.x + moves[i].x, .y = curr.y + moves[i].y};

        if (dfs(maze, height, width, wall, visited, p, end, path, path_len)) {
            return true;
        }
    }

    (*path_len)--;
    return false;
}
