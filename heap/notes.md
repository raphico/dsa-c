## Heap

An heap is a special kind of binary tree that follows two rules:

1. All levels are completely filled, except possibly the leaf leaf which is filled from left to right
2. Every node compares a certain with its children
   - In a max heap, every parent >= children, so the maximum element is always at the root
   - In a min heap, every parent <= children, so the minimum element is always at the root

This is useful, because the root is either always the min (min-heap) or the max (max-heap). This allows us to quickly:

- get the highest or lowest priority item with O(1) time
- insert a new element with O(log n)
- remove the root with O(log n)

Heaps are conceptually binary trees, but are almost always implemented with arrays to save memory (no pointers), compact, faster traversal, and makes bubble-up and bubble-down operations faster

### How heaps map to arrays

If we number the nodes of an heap in level order, we can store them in array without pointers:

1. The root index will be 0
2. A parent at index i, will have its left child at index 2i + 1, and its right child at index 2i + 2
3. A child at index j, will have its parent at (j - 1) // 2 (floor division)

### Insertion

1. Insert a new element at the next open slot in the heap to maintain the complete tree property
2. If the new element violates the heap property with respect to its parent:
   - In a max heap, if the new element > parent, we swap them
   - In a min heap, if the new element < parent, we swap them
   - We repeat until the heap property is satisfied

### Deletion

We usually only remove the root:

1. move the last element in the heap to the root to maintain the complete tree property
2. If this violates the heap property, we restore it by:
   - comparing the root with its children, swap with the largest element in a max heap (or smallest in a min heap)
   - repeat until the heap property is restored
