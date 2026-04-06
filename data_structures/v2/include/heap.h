#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>
#include <stddef.h>

#include "arena.h"

typedef struct BinaryHeap {
    int* data;
    size_t size;
    size_t capacity;
} BinaryHeap;

bool heap_init(BinaryHeap* heap, mem_arena* arena, size_t capacity);
void heap_clear(BinaryHeap* heap);
bool heap_push(BinaryHeap* heap, int value);
bool heap_pop(BinaryHeap* heap, int* out_value);
bool heap_peek(const BinaryHeap* heap, int* out_value);

size_t heap_parent(size_t index);
size_t heap_left(size_t index);
size_t heap_right(size_t index);

#endif
