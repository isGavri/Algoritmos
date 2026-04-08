#include <stdio.h>

#include "arena.h"
#include "queue.h"


// loops thourgh the queue printing all of the nodes
static void print_queue(const Queue* queue) {
    const QueueNode* current;

    printf("queue(size=%d): ", queue->size);
    current = queue->front;
    while (current != NULL) {
        printf("%d", current->value);
        current = current->next;
        if (current != NULL) {
            printf(" -> ");
        }
    }
    printf("\n");
}

int main(void) {
    mem_arena* arena = arena_create(GiB(1), MiB(100));
    Queue queue;
    int value;
    size_t i;
    int inputs[6] = {10, 20, 30, 40, 50, 60};

    if (arena == NULL) {
        fprintf(stderr, "Arena creation failed.\n");
        return 1;
    }
    if (!queue_init(&queue, arena, 6)) {
        fprintf(stderr, "Queue initialization failed.\n");
        arena_destroy(arena);
        return 1;
    }

    printf("Queue example (arena-backed)\n");
    for (i = 0u; i < 6u; ++i) {
        if (!queue_enqueue(&queue, inputs[i])) {
            printf("enqueue(%d) failed\n", inputs[i]);
            break;
        }
        printf("enqueue(%d)\n", inputs[i]);
        print_queue(&queue);
    }

    if (queue_peek(&queue, &value)) {
        printf("peek() -> %d\n", value);
    }

    for (i = 0u; i < 3u; ++i) {
        if (queue_dequeue(&queue, &value)) {
            printf("dequeue() -> %d\n", value);
            print_queue(&queue);
        }
    }

    queue_clear(&queue);
    printf("clear()\n");
    print_queue(&queue);

    arena_destroy(arena);
    return 0;
}
