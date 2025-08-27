#include <stdio.h>

void merge(int arr[], int left, int mid, int right);
void merge_sort(int arr[], int left, int right);

int main() {
    int arr[] = {9, 3, 7, 1, 8, 2, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    merge_sort(arr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

void merge_sort(int arr[], int left, int right) {
    if (left == right) {
        return;
    }

    int mid = (left + right) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void merge(int arr[], int left, int mid, int right) {
    int len = 0;
    int n = right - left + 1;
    int tmp[n];

    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            tmp[len++] = arr[i++];
        } else {
            tmp[len++] = arr[j++];
        }
    }

    while (i <= mid) {
        tmp[len++] = arr[i++];
    }

    while (j <= right) {
        tmp[len++] = arr[j++];
    }

    for (int k = 0; k < n; k++) {
        arr[left + k] = tmp[k];
    }
}
