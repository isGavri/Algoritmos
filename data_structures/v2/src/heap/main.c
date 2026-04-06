#include <stdio.h>

#include "arena.h"
#include "heap.h"


static void print_heap(const BinaryHeap* heap) {
    size_t i;

    printf("heap(size=%zu): ", heap->size);
    for (i = 0u; i < heap->size; ++i) {
        printf("%d", heap->data[i]);
        if (i + 1u < heap->size) {
            printf(", ");
        }
    }
    printf("\n");
}

int main(void) {
    mem_arena* arena = arena_create(GiB(1), MiB(100));
    BinaryHeap heap;
    int value;
    size_t i;
    int inputs[8] = {42, 19, 73, 6, 55, 88, 12, 31};

    if (arena ==  NULL) {
        return 1;
    }
    if (!heap_init(&heap, arena, 8)) {
        arena_destroy(arena);
        return 1;
    }

    printf("Binary heap example (arena-backed max-heap)\n");
    for (i = 0u; i < 8u; ++i) {
        if (!heap_push(&heap, inputs[i])) {
            printf("push(%d) failed\n", inputs[i]);
            break;
        }
        printf("push(%d)\n", inputs[i]);
        print_heap(&heap);
    }

    if (heap_peek(&heap, &value)) {
        printf("peek() -> %d\n", value);
    }

    for (i = 0u; i < 3u; ++i) {
        if (heap_pop(&heap, &value)) {
            printf("pop() -> %d\n", value);
            print_heap(&heap);
        }
    }

    heap_clear(&heap);
    printf("clear()\n");
    print_heap(&heap);

    arena_destroy(arena);
    return 0;
}
