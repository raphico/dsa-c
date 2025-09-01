## Cache

A cache is a small, fast storage layer that stores copies of data from a slower storage system to speed up access to data that is frequently used or expensive to fetch

## Least Recently Used (LRU)

LRU is a cache eviction policy that decides which data to remove when the cache is full. The main idea is that if a piece of data hasn't been used recently, then it's less likely to be used soon. So when the cache is full

- remove the least recently used item
- insert the new item

### Implementation

Most implementation of an LRU use a hashmap and a doubly linked list:

- the hashmap maps a key to the corresponding node in global doubly linked list for O(1) lookup
- while, the doubly linked list maintains the order of usage (most recently used item at the head, and least recently used item at the tail)

When an item is accessed or inserted

- if it exits (hashmap lookup), move the corresponding node to the head of the list
- if it's new and the cache full, remove the tail node (LRU), and insert the new node at the head

This combination gives us:

1. O(1) lookup via hashmap
2. O(1) insert and delete from the list
