#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>

#include "arena.h"

typedef struct QueueNode {
    int value;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
    QueueNode* node_pool;
    QueueNode* free_list;
    size_t size;
    size_t capacity;
} Queue;

bool queue_init(Queue* queue, mem_arena* arena, int capacity);
bool queue_enqueue(Queue* queue, int value);
bool queue_dequeue(Queue* queue, int* out_value);
bool queue_peek(const Queue* queue, int* out_value);
void queue_clear(Queue* queue);

#endif
