## Tree as an ADT

Tree is a hierarchical ADT that organizes data in a parent-child relationship. Each node contains:

1. data (the actual value stored in the node)
2. pointers to children

**It supports:**

1. Insert: adds a new node
2. Delete: removes a node
3. Search: checks for a node with a specific value
4. Traversal: visits all nodes in a specific order

**Key Concepts:**

1. Root: the topmost node with no parents
2. Parent: a node with at least one child
3. Child: a node with a parent
4. Leaf: a node with no children
5. Edge: a connection between a parent and child
6. Subtree: a tree consisting of a node and its descendant
7. Siblings: nodes that share the same parent
8. Depth: number of edges from the root to a node
9. Height of a node: number of edges on the longest path from that node to a leaf
10. Height of the tree: height of the root node
11. Level: nodes with the same depth
12. Degree: number of children a node has
13. A perfect tree: all leafs are on the same level
14. A balanced tree: the height of the left and right subtree differ by at most 1

## Binary trees

A binary tree is a tree in which each at has at most two children: the left child and the right child

### Binary Search Tree (BST)

A binary search tree is a binary tree in which for every node:

- all values in the left subtree is less than or equal to the node's value
- all values in the right subtree is greater than or equal to the node's value

## Depth-First Search (DFS)

Depth-First Search, also known as Depth-First Traversal, is an algorithm for searching or traversing tree or graph data structures. The core principle of DFS is to explore as far as possible along one path (parent -> child -> grandchild, until you reach a leaf) before backtracking. It is implemented using a stack (either explicit or through recursion)

When traversing a tree, we decide when we want to visit root compared to the left and right subtrees. This gives us three depth-first traversals:

1. Preorder: visit root -> visit left -> visit right
2. Inorder: visit left -> visit root -> visit right
3. Postorder: visit left -> visit right -> visit root

Suppose we have:

```bash
    A
   / \
  B   C
```

- Preorder: `A B C`
- Inorder: `C A B`
- Postorder: `C B A`

An inorder traversal on a binary search tree always gives us the sorted sequence of keys. This is one of the big reasons why BST are useful

Depth-First traversal preserves enough information about the shape of a tree. Inorder gives us the relative ordering of the left vs root vs right, combined with preorder or postorder, we can uniquely pin down the structure

## Breadth-First Search (BFS)

Breadth-First Search, also known as Breadth-First Traversal, is also an algorithm for searching or traversing tree or graph data structures. The core principle of BFS is to explore all neighbors (or directly connected nodes: children of a node) of the current node before moving deeper. So BFS on a tree visits parent, then all its children, then all their children etc. This is implemented using a queue

When traversing a tree using breadth-first traversal, we visit nodes level by level from top to bottom (root -> children -> grandchildren)

### Implementation Idea

- Use a queue (FIFO)
- Start by enqueuing the root
- While the queue is not empty:
  - Dequeue one node, visit it
  - Enqueue its children (left, then right)

## Time complexity of search, insertion, and deletion on a BST

The time complexity of a tree is expressed in terms of the height of the tree, because you walk from the root down at most h edges. If the tree is balanced, each step cuts the remaining values in half. So O(h) = O(logn). However, if the tree is unbalanced like a linked list. So O(h) = O(n)

Insertion and Deletion is also O(h), because you first need to search where the node is or where to place a new node. In a balanced bst, O(h) = O(logn). If not, O(h) = O(n). That's why self-balancing trees are important: they guarantee h = log2n

## Implementing deletion in a BST

1. Case 1: If the node is a leaf node, then we can just delete the node
2. Case 2: If the node has one child, replace the node with its only child
3. Case 3: If the node has two children:
   - Two valid choices:
     - Inorder predecessor: largest value in the left subtree
     - Inorder successor: smallest value in the right subtree
   - Replace the node's value with its predecessor/successor, then delete that node recursively with Case 1 or Case 2
