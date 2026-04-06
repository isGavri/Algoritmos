#include "heap.h"
#include "arena.h"

static void heap_swap(int* a, int* b) {
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

size_t heap_parent(size_t index) {
    return (index - 1u) / 2u;
}

size_t heap_left(size_t index) {
    return index * 2u + 1u;
}

size_t heap_right(size_t index) {
    return index * 2u + 2u;
}

bool heap_init(BinaryHeap* heap, mem_arena* arena, size_t capacity) {
    void* memory;

    if (heap == NULL || arena == NULL || capacity == 0u) {
        return false;
    }

    memory = PUSH_ARRAY(arena, int, capacity);
    if (memory == NULL) {
        return false;
    }

    heap->data = (int*)memory;
    heap->size = 0u;
    heap->capacity = capacity;
    return true;
}

void heap_clear(BinaryHeap* heap) {
    if (heap == NULL) {
        return;
    }
    heap->size = 0u;
}

bool heap_push(BinaryHeap* heap, int value) {
    size_t index;

    if (heap == NULL || heap->data == NULL || heap->size >= heap->capacity) {
        return false;
    }

    index = heap->size;
    heap->data[index] = value;
    heap->size += 1u;

    while (index > 0u) {
        size_t parent;
        parent = heap_parent(index);
        if (heap->data[parent] >= heap->data[index]) {
            break;
        }
        heap_swap(&heap->data[parent], &heap->data[index]);
        index = parent;
    }
    return true;
}

bool heap_pop(BinaryHeap* heap, int* out_value) {
    size_t index;

    if (heap == NULL || heap->data == NULL || heap->size == 0u) {
        return false;
    }

    if (out_value != NULL) {
        *out_value = heap->data[0];
    }

    heap->size -= 1u;
    if (heap->size == 0u) {
        return true;
    }

    heap->data[0] = heap->data[heap->size];
    index = 0u;

    while (1u) {
        size_t left;
        size_t right;
        size_t largest;

        left = heap_left(index);
        right = heap_right(index);
        largest = index;

        if (left < heap->size && heap->data[left] > heap->data[largest]) {
            largest = left;
        }
        if (right < heap->size && heap->data[right] > heap->data[largest]) {
            largest = right;
        }
        if (largest == index) {
            break;
        }

        heap_swap(&heap->data[index], &heap->data[largest]);
        index = largest;
    }
    return true;
}

bool heap_peek(const BinaryHeap* heap, int* out_value) {
    if (heap == NULL || heap->data == NULL || heap->size == 0u ||
        out_value == NULL) {
        return false;
    }
    *out_value = heap->data[0];
    return true;
}
