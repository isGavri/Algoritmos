#include <stdio.h>

#include "arena.h"
#include "priority_queue.h"


static void print_pq(const PriorityQueue* pq) {
    size_t i;

    printf("priority_queue(size=%zu): ", pq->size);
    for (i = 0u; i < pq->size; ++i) {
        printf("(v=%d,p=%d)", pq->data[i].vertex, pq->data[i].priority);
        if (i + 1u < pq->size) {
            printf(", ");
        }
    }
    printf("\n");
}

int main(void) {
    mem_arena* arena = arena_create(GiB(1), MiB(100));
    PriorityQueue pq;
    PqElement out;

    if (arena == NULL) {
        return 1;
    }
    if (!pq_init(&pq, arena, 5)) {
        arena_destroy(arena);
        return 1;
    }

    printf("Priority queue example (arena-backed min-heap)\n");

    pq_insert(&pq, 3, 40);
    pq_insert(&pq, 1, 15);
    pq_insert(&pq, 7, 60);
    pq_insert(&pq, 2, 25);
    pq_insert(&pq, 5, 50);
    print_pq(&pq);

    if (pq_decrease_key(&pq, 5, 10)) {
        printf("decrease_key(v=5, p=10)\n");
    }
    print_pq(&pq);

    if (pq_extract_min(&pq, &out)) {
        printf("extract_min() -> (v=%d,p=%d)\n", out.vertex, out.priority);
    }
    print_pq(&pq);

    if (pq_extract_min(&pq, &out)) {
        printf("extract_min() -> (v=%d,p=%d)\n", out.vertex, out.priority);
    }
    print_pq(&pq);

    pq_clear(&pq);
    printf("clear()\n");
    print_pq(&pq);

    arena_destroy(arena);
    return 0;
}
