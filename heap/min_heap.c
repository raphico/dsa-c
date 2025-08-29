#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
    size_t capacity;
} min_heap_t;

min_heap_t *min_heap_create(size_t capacity) {
    min_heap_t *min_heap = malloc(sizeof(min_heap_t));
    if (!min_heap) {
        return NULL;
    }

    min_heap->elements = malloc(sizeof(int) * capacity);
    if (!min_heap->elements) {
        free(min_heap);
        return NULL;
    }

    min_heap->size = 0;
    min_heap->capacity = capacity;

    return min_heap;
}

void min_heap_heapify_up(min_heap_t *min_heap, int i) {
    if (i == 0) {
        return;
    }

    int parent_idx = (i - 1) / 2;
    if (min_heap->elements[i] >= min_heap->elements[parent_idx]) {
        return;
    }
    
    int tmp = min_heap->elements[parent_idx];
    min_heap->elements[parent_idx] = min_heap->elements[i];
    min_heap->elements[i] = tmp;
    min_heap_heapify_up(min_heap, parent_idx);
}

int min_heap_insert(min_heap_t *min_heap, int data) {
    if (!min_heap) {
        return -1;
    }

    if (min_heap->size >= min_heap->capacity) {
        int new_capacity = min_heap->capacity * 2;
        int *new_elements = realloc(min_heap->elements, sizeof(int) * new_capacity);
        if (!new_capacity) {
            return -1;
        }
        min_heap->capacity = new_capacity;
        min_heap->elements = new_elements;
    }

    min_heap->elements[min_heap->size++] = data;

    min_heap_heapify_up(min_heap, min_heap->size - 1);
    return 0;
}

int min_heap_peek_min(min_heap_t *min_heap, int *min) {
    if (!min_heap) {
        return -1;
    }

    *min = min_heap->elements[0];
    return 0; 
}

void min_heap_heapify_down(min_heap_t *min_heap, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;

    if (
        left < min_heap->size &&
        min_heap->elements[left] < min_heap->elements[smallest]
    ) {
        smallest = left;
    }

    if (
        right < min_heap->size &&
        min_heap->elements[right] < min_heap->elements[smallest]
    ) {
        smallest = right;
    }

    if (smallest != i) {
        int tmp = min_heap->elements[i];
        min_heap->elements[i] = min_heap->elements[smallest];
        min_heap->elements[smallest] = tmp;

        min_heap_heapify_down(min_heap, smallest);
    }
}

int min_heap_extract_min(min_heap_t *min_heap, int *min) { 
    if (!min_heap || min_heap->size == 0) {
        return -1;
    }

    *min = min_heap->elements[0];

    min_heap->elements[0] = min_heap->elements[min_heap->size - 1];
    min_heap->size--;
    min_heap_heapify_down(min_heap, 0);
    return 0; 
}

void min_heap_free(min_heap_t *min_heap) {
    if (!min_heap) {
        return;
    }

    free(min_heap->elements);
    free(min_heap);
}

int main() {
    min_heap_t *min_heap = min_heap_create(4);

    min_heap_insert(min_heap, 2);
    min_heap_insert(min_heap, 10);
    min_heap_insert(min_heap, 3);
    min_heap_insert(min_heap, 6);
    min_heap_insert(min_heap, 1);

    int min;
    min_heap_extract_min(min_heap, &min);
    printf("Extract min: %d\n", min);
    
    min_heap_peek_min(min_heap, &min);
    printf("Peek min: %d\n", min);

    min_heap_free(min_heap);
    return 0;
}
