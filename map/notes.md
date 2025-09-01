## Map

A map (also called a dictionary) is an abstract data type (ADT) that represents an unordered collection of key-value pairs, where each key is unique and maps to a specific value. The key is used to efficiently retrieve, insert, update, and delete the corresponding value.

### Key operations

1. insert: adds a new key-value pair
2. update: changes the value associated with a key
3. delete: removes a key and its value
4. get: retrieves the value associated with a key

## Hash Table

A hash table is a concrete data structure that implements the map ADT using hashing—the process of converting a key to a fixed-size integer called an hash.

- A hash table stores key-value pairs in an array of buckets
- Each bucket may hold multiple values (e.g. linked list or dynamic array) to handle collision—when multiple keys map to the same bucket
- A hash function maps each key to an array index, allowing direct access to the correct bucket

### The load factor

The load factor of an hash map is a measure of how full it is:

$$
\text{Load Factor} = \frac{\text{Number of elements in the table}}{\text{Number of available buckets (slots)}}
$$

For example, if an hash table has 100 buckets and 45 elements, the load factor is `45/100 = 0.45`

- Low load factor means there are few collisions (so faster lookups), but wastes memory
- High load factor means there are many collisions (so slower lookups), but better memory usage
- Many implementations (like Java’s HashMap) automatically resize (rehash) when the load factor exceeds about 0.75.

### Time complexity

- On average, insert, update, get, and delete take O(1) time
- In the worst case, when there are multiple collisions to the same bucket, retrieval or updates can degrade to O(n)
