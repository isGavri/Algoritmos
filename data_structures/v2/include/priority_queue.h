#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdbool.h>
#include <stddef.h>

#include "arena.h"

typedef struct PqElement {
    int vertex;
    int priority;
} PqElement;

typedef struct PriorityQueue {
    PqElement* data;
    int* position;
    size_t size;
    size_t capacity;
} PriorityQueue;

bool pq_init(PriorityQueue* pq, mem_arena* arena, size_t capacity);
void pq_clear(PriorityQueue* pq);

bool pq_insert(PriorityQueue* pq, int vertex, int priority);
bool pq_extract_min(PriorityQueue* pq, PqElement* out_element);
bool pq_decrease_key(PriorityQueue* pq, int vertex, int new_priority);
bool pq_contains(const PriorityQueue* pq, int vertex);

#endif
