#include "priority_queue.h"
#include "arena.h"

static size_t pq_parent(size_t i) {
    return (i - 1u) / 2u;
}

static size_t pq_left(size_t i) {
    return i * 2u + 1u;
}

static size_t pq_right(size_t i) {
    return i * 2u + 2u;
}

static void pq_swap(PriorityQueue* pq, size_t i, size_t j) {
    PqElement t;
    t = pq->data[i];
    pq->data[i] = pq->data[j];
    pq->data[j] = t;

    pq->position[pq->data[i].vertex] = (int)i;
    pq->position[pq->data[j].vertex] = (int)j;
}

static void heapify_up(PriorityQueue* pq, size_t index) {
    while (index > 0u) {
        size_t parent;
        parent = pq_parent(index);
        if (pq->data[index].priority >= pq->data[parent].priority) {
            break;
        }
        pq_swap(pq, index, parent);
        index = parent;
    }
}

static void heapify_down(PriorityQueue* pq, size_t index) {
    while (1) {
        size_t left;
        size_t right;
        size_t smallest;

        left = pq_left(index);
        right = pq_right(index);
        smallest = index;

        if (left < pq->size &&
            pq->data[left].priority < pq->data[smallest].priority) {
            smallest = left;
        }
        if (right < pq->size &&
            pq->data[right].priority < pq->data[smallest].priority) {
            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        pq_swap(pq, index, smallest);
        index = smallest;
    }
}

bool pq_init(PriorityQueue* pq, mem_arena* arena, size_t capacity) {
    size_t i;

    if (pq == NULL || arena == NULL || capacity == 0u) {
        return false;
    }

    pq->data = PUSH_ARRAY(arena, PqElement, capacity);
    pq->position = PUSH_ARRAY(arena, int, capacity);

    if (pq->data == NULL || pq->position == NULL) {
        return false;
    }

    pq->size = 0u;
    pq->capacity = capacity;

    for (i = 0u; i < capacity; ++i) {
        pq->position[i] = -1;
    }

    return true;
}

void pq_clear(PriorityQueue* pq) {
    size_t i;

    if (pq == NULL || pq->position == NULL) {
        return;
    }

    pq->size = 0u;
    for (i = 0u; i < pq->capacity; ++i) {
        pq->position[i] = -1;
    }
}

bool pq_insert(PriorityQueue* pq, int vertex, int priority) {
    size_t index;

    if (pq == NULL || pq->data == NULL || pq->position == NULL || vertex < 0 ||
        (size_t)vertex >= pq->capacity || pq->size >= pq->capacity ||
        pq->position[vertex] != -1) {
        return false;
    }

    index = pq->size;
    pq->data[index].vertex = vertex;
    pq->data[index].priority = priority;
    pq->position[vertex] = (int)index;
    pq->size += 1u;
    heapify_up(pq, index);
    return true;
}

bool pq_extract_min(PriorityQueue* pq, PqElement* out_element) {
    if (pq == NULL || pq->data == NULL || pq->position == NULL ||
        pq->size == 0u) {
        return false;
    }

    if (out_element != NULL) {
        *out_element = pq->data[0];
    }
    pq->position[pq->data[0].vertex] = -1;

    pq->size -= 1u;
    if (pq->size == 0u) {
        return true;
    }

    pq->data[0] = pq->data[pq->size];
    pq->position[pq->data[0].vertex] = 0;
    heapify_down(pq, 0u);
    return true;
}

bool pq_decrease_key(PriorityQueue* pq, int vertex, int new_priority) {
    size_t index;

    if (pq == NULL || pq->position == NULL || vertex < 0 ||
        (size_t)vertex >= pq->capacity || pq->position[vertex] < 0) {
        return false;
    }

    index = (size_t)pq->position[vertex];
    if (new_priority >= pq->data[index].priority) {
        return false;
    }

    pq->data[index].priority = new_priority;
    heapify_up(pq, index);
    return true;
}

bool pq_contains(const PriorityQueue* pq, int vertex) {
    if (pq == NULL || pq->position == NULL || vertex < 0 ||
        (size_t)vertex >= pq->capacity) {
        return false;
    }
    return pq->position[vertex] != -1;
}
