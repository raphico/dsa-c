## Queues

Queues are ADT that follows the FIFO principle, meaning the first element added is the first element to be removed. It is a linear structure structure where elements are added to the rear of the structure, and elements are removed from the front of the structure. It supports:

- Enqueue: adds new elements to the rear of the structure
- Dequeue: removes the element the element at the front of the structure

Implementation(Data structure): Queues can be built by using arrays or linked lists

### Implementation with arrays

**shifting problem**

Dequeuing requires all subsequent elements to be shifted to the left by one. That makes dequeuing O(n) instead of O(1)

One possible fix is to keep two pointers: one for the "front" and the other for the "rear". Then instead of shifting, we just move the pointers.

```bash
Index:   0   1   2   3   4
Values: [A] [B] [C] [ ] [ ]
front = 0
rear = 2
```

After one dequeue:

```bash
Index:   0   1   2   3   4
Values: [A] [B] [C] [ ] [ ]
front = 1
rear = 2
```

Now we enqueue D:

```bash
Index:   0   1   2   3   4
Values: [A] [B] [C] [D] [ ]
front = 1
rear = 3
```

**Fixed capacity problem**

If we keep enqueuing without resizing, we will eventually run out of space. The fix is to either:

dynamically allocating a larger array and copy the old contents to accommodate space for the new element, or use a circular buffer (wrapping around inside the same array):

```bash
Index:   0  1  2  3  4
Values: [] [] [] [] []

front = NULL
rear = NULL
```

We enqueue A, B, C, D, E:

```bash
Index:   0   1   2   3   4
Values: [A] [B] [C] [D] [E]

front = 0
rear = 4
```

We dequeue A, B

```bash
Index:   0   1   2   3   4
Values: [A] [B] [C] [D] [E]

front = 2
rear = 4
```

The rear is already at the last index. If we try to enqueue one more element, the array we say full, even though we have space at the front. So to fix this we act like the array is a circle: after index `4`, we wrap back to index `0`. If we enqueue `F`, its position in the circular queue is calculated as: `(rear + 1) % size = (4 + 1) % 5 = 5 % 5 = 0`

```bash
Index:   0   1   2   3   4
Values: [F] [ ] [C] [D] [E]
front = 2   (C)
rear  = 0   (F)
```

### Implementation with linked lists

- Dequeuing in a linked list is O(1), because it takes constant step regardless of the size of the structure: we just need to move the head to the next node
- Enqueuing(singly without a tail pointer) takes O(n), since we need to first find the tail before linking the new node
- Enqueuing(singly with a tail pointer) takes O(1), since we can just jump to the tail and link the new node
- Enqueuing(doubly) takes O(1), same idea
