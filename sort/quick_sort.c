#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quick_sort(int arr[], int low, int high);
int partition(int arr[], int low, int high);

int main() {
    int arr[] = {9, 3, 7, 1, 8, 2, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    // to avoid getting the same sequence of randoms each time the program runs
    srand(time(NULL));  

    quick_sort(arr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pivot_idx = partition(arr, low, high);
        quick_sort(arr, low, pivot_idx - 1);
        quick_sort(arr, pivot_idx + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot_idx = low + rand() % (high - low + 1);
    int pivot_val = arr[pivot_idx];

    arr[pivot_idx] = arr[high];
    arr[high] = pivot_val;

    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot_val) {
            i++;

            if (j > i) {
                int tmp = arr[j];
                arr[j] = arr[i];
                arr[i] = tmp;
            }
        }
    }
    
    int tmp = arr[i + 1];
    arr[i + 1] = pivot_val;
    arr[pivot_idx] = tmp;

    return i + 1;
}
