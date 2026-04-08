#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>

#include "arena.h"

// Node of the queue, stores the value and a reference to the next node
typedef struct QueueNode {
    int value;
    struct QueueNode* next;
} QueueNode;

// Queue struct, stores references to the front and rear.
// An array for the nodes of the queue (of size capacity on initialization) - node_pool
// An array of free nodes (point to the free spaces in node_pool)
// Size of enqueued elements
// Total capacity
typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
    QueueNode* node_pool;
    QueueNode* free_list;
    int size;
    int capacity;
} Queue;

bool queue_init(Queue* queue, mem_arena* arena, int capacity);
bool queue_enqueue(Queue* queue, int value);
bool queue_dequeue(Queue* queue, int* out_value);
bool queue_peek(const Queue* queue, int* out_value);
void queue_clear(Queue* queue);

#endif
