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

Depth-First Search, also known as Depth-First Traversal, is an algorithm for searching or traversing tree or graph data structures. The core principle of DFS is a explore as far as possible along each branch before backtracking

## Tree Traversal

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
