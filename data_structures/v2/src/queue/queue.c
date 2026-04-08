#include "queue.h"

// Initializes queue
bool queue_init(Queue* queue, mem_arena* arena, int capacity) {

    // No valid reference for a queue
    // No valid reference for an arena
    // Invalid capacity
    if (queue == NULL || arena == NULL || capacity <= 0) {
        return false;
    }

    // Allocates memory for nodes
    queue->node_pool = PUSH_ARRAY(arena, QueueNode, capacity);
    // Initializes references as empty
    queue->front = NULL;
    queue->rear = NULL;
    // Sets the start of free list to the start of node_pool
    queue->free_list = &queue->node_pool[0];
    // Initializes size as empty
    queue->size = 0;
    // Just sets capacity
    queue->capacity = capacity;

    // maps nodes to next node_pool memory references
    int i;
    for (i = 0; i + 1 < capacity; i++) {
        queue->node_pool[i].next = &queue->node_pool[i + 1];
    }
    // sets last in the node next in the array as null to mark the end
    queue->node_pool[capacity - 1].next = NULL;
    return true;
}

// Enqueues a node into the queue
bool queue_enqueue(Queue* queue, int value) {
    QueueNode* node;

    // Null queue, at maximum size, no free space
    if (queue == NULL || queue->size >= queue->capacity ||
        queue->free_list == NULL) {
        return false;
    }

    // Picks first free space on the list
    node = queue->free_list;
    // Advances free space pointer
    queue->free_list = node->next;
    // Sets value
    node->value = value;
    // To end the queue
    node->next = NULL;

    // If emtpy logically initialize it
    if (queue->rear == NULL) {
        queue->front = node;
        queue->rear = node;
        // append and update rear
    } else {
        queue->rear->next = node;
        queue->rear = node;
    }

    // update size
    queue->size += 1;
    return true;
}

// Dequeues first node of the queue
bool queue_dequeue(Queue* queue, int* out_value) {
    QueueNode* n;

    // if not queue or empty
    if (queue == NULL || queue->front == NULL) {
        return false;
    }

    n = queue->front;
    // extrct value off the queue
    if (out_value != NULL) {
        *out_value = n->value;
    }

    // new front is past second element
    queue->front = n->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    // moves the dequeued memory block to the start of the free list
    n->next = queue->free_list;
    queue->free_list = n;

    // updates size
    queue->size -= 1;
    return true;
}

// Peeks (first element to be dequeued) into the queue.
bool queue_peek(const Queue* queue, int* out_value) {
    // no queue or empty queue or no valid pointer as output value
    if (queue == NULL || queue->front == NULL || out_value == NULL) {
        return false;
    }

    // reference to the value at the front of the queue
    *out_value = queue->front->value;
    return true;
}

// Clears memory and resets fields of queue
void queue_clear(Queue* queue) {
    int i;

    // no queue
    if (queue == NULL) {
        return;
    }

    // sets as empty
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;

    if (queue->node_pool == NULL || queue->capacity == 0) {
        queue->free_list = NULL;
        return;
    }

    // Re asigns free_list and "linked list" of pool of nodes
    queue->free_list = &queue->node_pool[0];
    for (i = 0; i + 1 < queue->capacity; i++) {
        queue->node_pool[i].next = &queue->node_pool[i + 1];
    }
    queue->node_pool[queue->capacity - 1].next = NULL;
}
