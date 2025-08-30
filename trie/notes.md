## Trie

A trie (from "re**trie**val") is a tree-like data structure that store strings or sequences

- Each edge represents a character
- Each path from the root to a node represents a prefix
- A special marker (often a boolean flag) tells us when path is actually a complete word

A trie can be implemented in two main ways:

- Array-based:
  Each node keeps an array, where the index of the array corresponds to a character(c - 'a'). The content of the slot is a pointer: NULL if no words goes through that character or a pointer to another trie node if a path continues through that character.

  - Lookup is O(1) for each character, since you can just jump to children[c - 'a']
  - Memory can be wasted if most slots are empty

- Hashmap/linked-list based:
  Each node only stores the children that actually exist
  - Saves memory
  - Lookup is slower
