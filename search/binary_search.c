int binary_search(int haystack[], int n, int needle) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid =  (int) (low + high) / 2;

        if (haystack[mid] == needle) {
            return mid;
        } else if (haystack[mid] < needle) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}
