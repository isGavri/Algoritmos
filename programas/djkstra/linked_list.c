#include "arena.c"
// *** Linked List Types *** //
typedef struct Node Node;
struct Node {
    i32 data;
    Node* next;
};

typedef struct {
    Node* head;
    Node* tail;
    Node* free_list; // Tracks popped nodes for reuse
    u64 count;
} List;

// *** Internal Free List Managers *** //

// Gets a node from the free list if available, otherwise asks the arena
Node* _list_alloc_node(mem_arena* arena, List* list) {
    if (list->free_list != NULL) {
        Node* recycled = list->free_list;
        list->free_list = recycled->next;
        
        // Disconnect the recycled node from the free list chain
        recycled->next = NULL; 
        return recycled;
    }
    
    // Fallback: ask the arena for fresh memory
    return PUSH_STRUCT(arena, Node);
}

// Puts a popped node into the free list for future reuse
void _list_recycle_node(List* list, Node* node) {
    node->next = list->free_list;
    list->free_list = node;
}

// *** Linked List Functions *** //

List* list_create(mem_arena* arena) {
    List* list = PUSH_STRUCT(arena, List);
    list->head = NULL;
    list->tail = NULL;
    list->free_list = NULL;
    list->count = 0;
    return list;
}

void list_push_back(mem_arena* arena, List* list, i32 data) {
    Node* node = _list_alloc_node(arena, list);
    node->data = data;

    if (list->tail == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    
    list->count++;
}

void list_push_front(mem_arena* arena, List* list, i32 data) {
    Node* node = _list_alloc_node(arena, list);
    node->data = data;
    node->next = list->head;

    list->head = node;
    
    if (list->tail == NULL) {
        list->tail = node;
    }
    
    list->count++;
}

void list_insert_at(mem_arena* arena, List* list, u64 index, i32 data) {
    if (index == 0) {
        list_push_front(arena, list, data);
        return;
    }

    if (index >= list->count) {
        list_push_back(arena, list, data);
        return;
    }

    Node* current = list->head;
    for (u64 i = 0; i < index - 1; i++) {
        current = current->next;
    }

    Node* node = _list_alloc_node(arena, list);
    node->data = data;
    node->next = current->next;
    current->next = node;
    
    list->count++;
}

void list_pop_back(List* list) {
    if (list->head == NULL) {
        return;
    }

    Node* popped_node;

    if (list->head == list->tail) {
        popped_node = list->head;
        list->head = NULL;
        list->tail = NULL;
    } else {
        Node* current = list->head;
        while (current->next != list->tail) {
            current = current->next;
        }
        popped_node = current->next;
        current->next = NULL;
        list->tail = current;
    }
    
    // Recycle the memory instead of abandoning it
    _list_recycle_node(list, popped_node);
    list->count--;
}

void list_pop_front(List* list) {
    if (list->head == NULL) {
        return;
    }

    Node* popped_node = list->head;
    list->head = list->head->next;
    
    if (list->head == NULL) {
        list->tail = NULL;
    }
    
    // Recycle the memory instead of abandoning it
    _list_recycle_node(list, popped_node);
    list->count--;
}
