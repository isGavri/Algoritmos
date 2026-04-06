#include "queue.h"

// Initializes queue
bool queue_init(Queue* queue, mem_arena* arena, int capacity) {

    if (queue == NULL || arena == NULL || capacity == 0u) {
        return false;
    }

    queue->node_pool = PUSH_ARRAY(arena, QueueNode, capacity);
    queue->front = NULL;
    queue->rear = NULL;
    queue->free_list = &queue->node_pool[0];
    queue->size = 0;
    queue->capacity = capacity;

    // maps memory
    int i;
    for (i = 0; i + 1 < capacity; ++i) {
        queue->node_pool[i].next = &queue->node_pool[i + 1];
    }
    // sets last in the node next in the array as null
    queue->node_pool[capacity - 1].next = NULL;
    return true;
}

bool queue_enqueue(Queue* queue, int value) {
    QueueNode* node;

    if (queue == NULL || queue->size >= queue->capacity ||
        queue->free_list == NULL) {
        return false;
    }

    node = queue->free_list;
    queue->free_list = node->next;
    node->value = value;
    node->next = NULL;

    if (queue->rear == NULL) {
        queue->front = node;
        queue->rear = node;
    } else {
        queue->rear->next = node;
        queue->rear = node;
    }

    queue->size += 1;
    return true;
}

bool queue_dequeue(Queue* queue, int* out_value) {
    QueueNode* n;

    if (queue == NULL || queue->front == NULL) {
        return false;
    }

    n = queue->front;
    if (out_value != NULL) {
        *out_value = n->value;
    }

    queue->front = n->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    n->next = queue->free_list;
    queue->free_list = n;
    queue->size -= 1u;
    return true;
}

bool queue_peek(const Queue* queue, int* out_value) {
    if (queue == NULL || queue->front == NULL || out_value == NULL) {
        return false;
    }
    *out_value = queue->front->value;
    return true;
}

void queue_clear(Queue* queue) {
    size_t i;

    if (queue == NULL) {
        return;
    }

    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0u;

    if (queue->node_pool == NULL || queue->capacity == 0u) {
        queue->free_list = NULL;
        return;
    }

    queue->free_list = &queue->node_pool[0];
    for (i = 0u; i + 1u < queue->capacity; ++i) {
        queue->node_pool[i].next = &queue->node_pool[i + 1u];
    }
    queue->node_pool[queue->capacity - 1u].next = NULL;
}
