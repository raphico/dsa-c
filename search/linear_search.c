int linear_search(int haystack[], int n, int needle) {
    for (int i = 0; i < n; i++) {
        if (needle == haystack[i]) {
            return i;
        }
    }

    return -1;
}
