void bubble_sort(int arr[], int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 1; j < n - i; j++) {
      if (arr[j - 1] > arr[j]) {
        int tmp = arr[j];
        arr[j] = arr[j - 1];
        arr[j - 1] = tmp;
      }
    }
  }
}
