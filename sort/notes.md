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

## Quick Sort

Quick sort is a divide-and-conquer algorithm. It sorts the array by:

- picking a pivot in the array
- partitioning the array to:
  - move all elements less than the pivot to the left
  - and move all elements greater than the pivot to the right
- after a partition, the pivot is guaranteed to end up at its correct position

Say we are sorting `[3, 7, 2, 5]` and we pick 5 as the pivot.

- Step 1: Partition -> `[3, 2] | 5 | [7]`
- Step 2: Recursively sort `[3, 2]` -> `[2, 3]`
- Step 3: `[2, 3] | 5 | [7]` -> `[2, 3, 5, 7]`

### Time complexity

A partition compares every element with the pivot exactly once. So partition takes O(n) time at each level (partition together still touch all elements).

In the Best case, the pivot splits the array into two equal halves, resulting in log2n levels. So the total time = O(nlogn)

In the worst case, the pivot splits the array into n - 1 and 1 sub-array, resulting in n - 1 levels. So the total time = O(n^2)

### What can we do in practical situations to avoid the worst-case split?

A lot of textbook examples pick the last element has the pivot. The problem with this is that if the array is already sorted, either in ascending or descending, it will result in the worst-case split every time. That means we it O(n^2).

Common tricks include:

- picking a random element as the pivot each time
- picking the median of the first, middle, and last element

### Implementing Quick sort

The quick sort implementation consists of two main parts:

1. Partition function: takes an array along with the starting index (low) and ending index (high) of the subarray. It selects a pivot and rearranges the array so that elements less than the pivot are on the left, and elements greater than the pivot are on the right. It then returns the pivot's final index
2. Recursive quick sort function: calls the partition function. Once the pivot is placed in its correct position, it divides the array into two subarrays and recursively sorts the left and right subarray. The recursion stops when a subarray is has 0 or 1 element

## Merge sort

Merge sort is a divide-and-conquer algorithm that recursively splits an array into halves until subarrays of size 1 remain. It then merges the subarrays in sorted order

Say we are sorting `[3, 1, 4, 2]`

**Step 1:** Divide until subarrays of size 1 remain

```bash
[3, 1, 4, 2]
   /      \
[3, 1]   [4, 2]
 /   \    /   \
[3] [1] [4] [2]
```

**Step 2:** Merge

- Merge `[3]` and `[1]` -> compares 3 vs 1 -> `[1, 3]`
- Merge `[4]` and `[2]` -> compares 4 vs 2 -> `[2, 4]`

**Step 3:** Final merge

- Merge `[1, 3]` and `[2, 4]`
  - compare 1 vs 2 -> 1 is smaller -> `[1]`
  - compares 2 vs 3 -> 2 is smaller -> `[1, 2]`
  - compares 3 vs 4 -> 3 is smaller -> `[1, 2, 3]`
  - append leftover 4 -> `[1, 2, 3, 4]`

### Time complexity

Merge sort repeatedly divides the array in halves until subarrays of size 1 remain; therefore, the total number of levels = how many times 2 can divide n before reaching 1 = log2n. Each level of merging makes n comparisons, giving a time complexity of O(nlogn).

Unlike quick sort, its time complexity is consistently O(nlogn), but requires more memory for merging

### Implementing merge sort

The merge sort implementation is made up of two main parts

1. Recursive merge sort function:
   - Input: an array
   - Base case: if the array is of size 0 or 1, then its already sorted
   - Recursive case:
     - split into two halves
     - recursively call merge sort on each half
     - merge two sorted halves
2. Merge function
   - Input: two sorted array
   - Output: a single sorted array
