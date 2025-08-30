#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

typedef struct trie_node_t {
    struct trie_node_t *children[ALPHABET_SIZE];
    bool is_end_of_word;
} trie_node_t;

trie_node_t *trie_create_node() {
    trie_node_t *trie_node = malloc(sizeof(trie_node_t));
    if (!trie_node) {
        return NULL;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        trie_node->children[i] = NULL;
    }
    trie_node->is_end_of_word = false;

    return trie_node;
}

int trie_insert(trie_node_t *root, const char *word) {
    if (!word || !root) {
        return -1;
    }

    trie_node_t *current = root;
    for (int i = 0, n = strlen(word); i < n; i++) {
        int index = tolower(word[i]) - 'a';
        if (index < 0 || index >= ALPHABET_SIZE) {
            return -1;
        }

        if (!current->children[index]) {
            current->children[index] = trie_create_node();
            if (!current->children[index]) {
                return -1;
            }
        }

        current = current->children[index];
    }

    current->is_end_of_word = true;
    return 0;
}

bool trie_delete(trie_node_t *root, const char *word, int depth) {
    if (depth == strlen(word)) {
        root->is_end_of_word = false;
        return true;
    }
    int index = tolower(word[depth]) - 'a';
    
    if (!root->children[index]) {
        return false;
    }
    return trie_delete(root->children[index], word, depth + 1);
}

int trie_remove(trie_node_t *root, const char *word) {
    if (!root || !word) {
        return -1;
    }

    return trie_delete(root, word, 0) ? 0 : -1;
}

bool trie_search(trie_node_t *root, const char *word) {
    if (!word || !root) {
        return false;
    }

    trie_node_t *current = root;
    for (int i = 0, n = strlen(word); i < n; i++) {
        int index = tolower(word[i]) - 'a';
        if (index < 0 || index >= ALPHABET_SIZE) {
            return false;
        }

        if (!current->children[index]) {
            return false;
        }

        current = current->children[index];
    }

    return current->is_end_of_word;
}

int main() {
    trie_node_t *root = trie_create_node();

    trie_insert(root, "bat");
    trie_insert(root, "batman");

    printf("Search bat: %d\n", trie_search(root, "bat"));
    printf("Search batman: %d\n", trie_search(root, "batman"));
    printf("Search cat: %d\n", trie_search(root, "cat"));

    trie_remove(root, "bat");
    printf("Search bat: %d\n", trie_search(root, "bat"));

    return 0;
}
