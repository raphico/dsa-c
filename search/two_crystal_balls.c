#include <math.h>
#include <stdbool.h>

int two_crystal_balls(bool breaks[], int n) {
    int jump = (int)sqrt(n);
    int i = 0;

    for (i = jump; i < n; i += jump) {
        if (breaks[i]) {
            break;
        }
    }

    int start = i - jump;
    for (int j = start; j < n && j <= i; j++) {
        if (breaks[j]) {
            return j;
        }
    }

    return -1;
}
