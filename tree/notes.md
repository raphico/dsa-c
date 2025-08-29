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

## M-way tree

An M-way tree is a tree where:

- Each node can have up to M children. So if M = 4, any node can have 0 to 4 children
- Each node stores an array of keys that act as a separator between subtrees
- The number of keys per node is between 1 and M - 1

## Self-Balancing Trees

The main idea of self-balancing BST is that a plain BST can be become skewed, like a linked list, if values are added in a sorted order. This make search, insert, and delete operations degrade to O(n). Self-balancing BST fix this by re-balancing the tree after an insertion or deletion. That way operations stay at O(logn).

### AVL

AVL trees are a kind of self-balancing trees that use a balance factor to determine if a tree is balanced. If the balance factor falls between {-1, 0, 1}, then the tree is balanced. Anything else means the tree is unbalanced. The balance factor for every node is defined as:

BF(node) = height(right) - height(left)

If the balance factor is:

- 0: that means the right and left subtree are the same height
- +1: that means the right subtree is taller
- -1: that means the left subtree is taller

When the balance factor ends up outside {-1, 0, 1}, the tree is considered unbalanced and rotations are used to restore balance without breaking the BST property. Once an imbalance is detected, there are four patterns of in-balance to fix:

1. **Right-Right:** Right Right imbalance occur when inserting to the right subtree of the right child of a node, causing the balance factor of that node to go up to +2. The recipe to fix RR case is to perform a single left rotation at the unbalanced node

2. **Left-Left:** Left-left imbalance occurs when inserting to the left subtree of the left child of a node, causing the balance factor of that node to go up to -2. This is fixed by performing a single right rotation at that unbalanced node

3. **Right-Left:** Right-Left imbalance occurs when inserting to the left subtree of the right child of a node, causing the balance factor of that node to go up to -2. This is fixed using a double rotation: a right rotation on the right child, followed by a left rotation on the unbalanced node

4. **Left-Right:** Left-Right imbalance occur when inserting to right subtree of the left child of a node, causing the balance factor of that node to go up to -2. This is also fixed using a double rotation: left rotation on the left child, followed by a right rotation on the unbalanced node

**Trade off:**

Rotation always take constant time O(1), because no matter how big the tree is only a constant number of pointers changes. In AVL trees, you might need to walk back to the root after an insertion, update height and balance factor, and potentially do one rotation. So insertion complexity is still O(logn).

AVL trees are stricter than other self-balancing trees, meaning it rebalances as soon as the balance factor is out of range, resulting in more rotations overall during many insertions. Every node also store its height (or balance factor) which is updated after each insertion or deletion, resulting in more memory and update overhead.

AVLs have a stricter balance, better search performance, and more rotations

### Red-black Trees

Red-black tree is a self-balancing binary search tree like AVL, but instead of using height difference to track balances, it uses colors and a few simple rules:

1. Every node is red or black
2. The root is always black
3. All leaves (we imagine every NULL as black) are black
4. No red parent can have a red child
5. Same number of blacks nodes on every path from a node down to its leaves

This rules ensures the tree never gets too tall: height <= 2 \* shortest path. Therefore, searching O(2h) = O(2logn) = O(logn)

RB trees have a looser balance than AVLs, and slightly worst search than AVL, but faster insertion/deletion

### B-Tree

A B-tree is a self-balancing M-way search tree. The order of a B-tree is the maximum number of children any node in the tree can have. A B-tree of order m must have the following properties:

1. Each node has multiple keys (up to M - 1) and have up to M children
2. Every node (expect the root) must have at least M/2 children (so at least M/2 - 1 keys ceiling)
3. Keys within a node are kept in sorted order
4. All leaves appear at the same depth, so the tree is always balanced
5. The subtrees of a node partition the keys range

After insertions or deletions, the B-tree may perform splits or merges to restore these properties. This ensures the tree height stay very small

B-trees are widely used in Databases, because they remain shallow even when storing massive amounts data

- An AVL or Red-Black tree keeps height around log2n
- A B-tree keeps height around logMn
- And since M can be in the hundreds or thousands, the tree's height become very small, which means searches, insertions, and deletions only require visiting a few nodes

**Insertions on a B-tree:**

A B-tree grows upwards. When a node gets full, it splits:

- The middle key goes up into the parent
- The children are redistributed around it
- If the parent also full, we split it as well

If this split chain reaches the root, then the root itself splits and a new root is created. That's the only time the tree gets taller

**Deletions on a B-tree:**

When deleting a key in a B-tree, we need to make sure every node still has at least M/2 - 1 keys.

1. Case 1: Deleting a leaf (easy case):
   - If the leaf still has at least the minimum number of keys after deletion, just remove it
2. Case 2: Delete from an internal node:
   - Replace the key with either:
     - its predecessor (the largest key in left subtree) or
     - its successor (the smallest key in right subtree)
   - Then recursively delete that predecessor/successor (which will always be in a leaf)
   - To do this, we need that child to have at least the minimum number of keys so it can give one up safely
3. Case 3: If a child has too few keys to lend
   - Borrow from a sibling: if a sibling has more than the minimum number of keys, rotate one through the parent
   - Merge with sibling: if neither can lend, merge the underfull child will a sibling and "pull down" a key from the parent
   - The parent itself might fall below the minimum, and the fix bubble upwards
   - If the root ends up with 0 keys, we shrink the height of the tree
