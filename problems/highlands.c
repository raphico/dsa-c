/*
Problem Statement: Number of Highlands (Islands)

You are given a 2D grid (matrix) of size m × n filled with 0s and 1s:

- 1 represents land (highland).
- 0 represents water (lowland).

Goal: Count how many distinct highlands (islands) exist.

Rules:

- A highland is a group of connected 1s.
- Two 1s are connected if they are adjacent horizontally or vertically
(sometimes diagonals are included — clarify which you want).
- Each connected group counts as one highland.

Example

Input:
1 1 0 0
0 1 0 1
1 0 0 1
0 0 0 0

Output: 3
*/

#include <stdbool.h>
#include <stdio.h>

#define ROWS 4
#define COLS 4

typedef struct {
    int x;
    int y;
} point_t;

int count_highlands(int grid[ROWS][COLS]);
void dfs(int grid[ROWS][COLS], bool visited[ROWS][COLS], point_t curr);

int main() {
    int grid[ROWS][COLS] = {
        {1, 1, 0, 0}, {0, 1, 0, 1}, {1, 0, 0, 1}, {0, 0, 0, 0}};

    int result = count_highlands(grid);
    printf("Number of highlands: %d\n", result);
    return 0;
}

int count_highlands(int grid[ROWS][COLS]) {
    bool visited[ROWS][COLS] = {false};
    int count = 0;

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (grid[r][c] == 1 && !visited[r][c]) {
                point_t p = {c, r};
                dfs(grid, visited, p);
                count++;
            }
        }
    }

    return count;
}

void dfs(int grid[ROWS][COLS], bool visited[ROWS][COLS], point_t curr) {
    if (curr.x < 0 || curr.y < 0 || curr.y >= ROWS || curr.x >= COLS) {
        return;
    }

    if (grid[curr.y][curr.x] == 0) {
        return;
    }

    if (visited[curr.y][curr.x]) {
        return;
    }

    visited[curr.y][curr.x] = true;

    point_t moves[] = {
        {.x = 1, .y = 0},
        {.x = -1, .y = 0},
        {.x = 0, .y = 1},
        {.x = 0, .y = -1},
    };
    for (int i = 0; i < 4; i++) {
        point_t new_point = {.x = curr.x + moves[i].x,
                             .y = curr.y + moves[i].y};
        dfs(grid, visited, new_point);
    }
}
