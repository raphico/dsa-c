## What are arrays?

An Array is a fixed-size, ordered collection of elements of the same type arranged contiguously in memory. Each element is assigned an index starting from zero

```c
int scores[3];
```

The above code declares a variable `scores` that hold up to 3 elements, and each element is of type `int`

## Time complexity of basic operations in an array

### Random access

The running time of random access in an array is O(1), because the memory address of an element is computed using a constant formula, independent of the array size: `address = base_address + i x size_of_element`

### Insertion

The running time of insertion at the end of an array(if space is available) is O(1), just place the element at the next available index. While, the running time of insertion at the beginning or in the middle is O(n), because all subsequent elements have to be shifted to accommodate the new element

### Deletion

The running time of deletion at the end of an array is O(1), because no shifting is required. While, the running time of deletion at the middle or beginning, requires shifting all subsequent elements to the left to fill the gap, hence O(n)
