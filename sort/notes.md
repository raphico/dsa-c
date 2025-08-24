## Bubble sort

Bubble sort is a sorting algorithm that repeatedly compares and swaps adjacent element if they are out of order.
Each swap "bubbles up" the largest element in the unsorted region to its correct position at the end

### Time Complexity:

In the worst case(when the array is arranged in descending order):

1. In the first pass, there are n-1 comparisons
2. In the second pass, there are n-2 comparisons
   ...
3. In the last pass, there is only 1 comparison
   The total number of comparisons = (n-2) + (n-1) +...+ 1 = n(n-1)/2
   This simplifies to a O(n^2)

In the best case(when the array is already sorted),

- in the first pass there are n-1 comparisons.
- If the algorithm implements a "no swap" check, it stops early, so the running time is Ω(n)
- Without optimization, it does all passes, so it remains Ω(n^2)

### Implementing bubble sort:

1. We need two loops
   - The outer loop counts passes through the array
   - The inner loop compares adjacent elements
2. Each pass in the inner loop
   - compares element i with i + 1
   - swaps them if they are out of other
3. After each pass in the outer loop, the largest element is guaranteed at the end, so each outer loop can ignore one more element at the end
