## Linked Lists

A linked list is a data structure that stores elements in nodes connected by pointers.

- Each node contains:

  1. an element (the actual value)
  2. a pointer to the next node

- The head is a pointer to the first node

- The tail is the last node, and its pointer is NULL

## Types of linked lists

- In a singly linked list, each node only has a pointer to the next node; therefore, traversal is only in one-way (from head -> tail).

- In a doubly linked list, each node has pointers to the next and previous node, allowing traversal in both direction, forward and backward, but it uses extra memory to store one extra pointer

## Time complexity of basic operations in a linked list

### Deletion

- In a singly linked list:
  - deleting the first node takes O(1) time, because the first node has a pointer to the next node, we just need to set the head to the next node and free the first node
  - deleting the tail or a middle node takes O(n) time, because each node only has a pointer to the next node. To delete a node, we need to traverse the list and set the node before pointer to NULL
- In a doubly linked list:
  - if we have a pointer to the node we want to delete, deletion is O(1), because we can adjust the prev and next pointers immediately
  - if we only know the value to delete, we will still need to traverse the list first, so O(n)

### Insertion

- Insertion at the head
  - Singly: O(1), (new node -> first node, update head)
  - Doubly: O(1) same idea
- Insertion at the tail
  - Singly (without tail pointer): O(n), since we first need to find the tail before linking the new node
  - Singly (with tail pointer): O(1), since we can just jump to the tail and link the new node
  - Doubly: O(1), since we can just jump to to the tail and link the new node
- Insertion at the middle
  - Both singly and doubly take O(n) if the spot is not know, because traversal is needed to find the spot which takes O(n) before insertion
  - If the spot is already known, they both take O(1)

### Random Access

- Random access takes O(n) in both singly and doubly, because traversal is required to find the target

## Linked lists vs Arrays

- linked lists use more memory to store pointers
- linked lists are cache inefficient, because nodes are scattered in memory, resulting in slower sequential access unlike contiguous arrays

Rules of thumb:

- Use arrays for faster indexing, less memory usage, and better cache performance(accessing element, automatically loads adjacent element)
- Use linked lists for faster insertions, deletions, and a more flexible structure
- Use arrays if you know the size in advance or if the size rarely changes
