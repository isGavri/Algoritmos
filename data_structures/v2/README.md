# Data Structures 
Contains queue, binary heap and priority queue.
Succesful implementation of structures. Full documentation on the way.
## Approach
The examples are only for static sizes of structures but easily expandible to be dynamic. It uses a linear arena allocator which makes this pretty safe.
It builds up from one data structure to another
### Structure
`./include/` are just header files with function prototyes and type definitions.
Under `./src` we find the actual implementations.
```bash
├── include
│   ├── arena.h
│   ├── heap.h
│   ├── priority_queue.h
│   └── queue.h
├── README.md
└── src
    ├── common
    │   └── arena.c
    ├── heap
    │   ├── heap.c
    │   └── main.c
    ├── priority_queue
    │   ├── main.c
    │   └── priority_queue.c
    └── queue
        ├── main.c
        └── queue.c
```

### First lets start with the arena
This implementation is not mine it's [magicalbat](https://www.youtube.com/watch?v=jgiMagdjA1s), it has very small changes and drops the support to windows.
Some resources to get more insight into the topic.
https://www.dgtlgrove.com/p/untangling-lifetimes-the-arena-allocator
https://www.gingerbill.org/series/memory-allocation-strategies/

### Queue
First data structure of this build up and easiest one also.
The queue is represented by this struct.
```c
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
```
Where:
- `QueueNode` is just an element of the queue
    - `value` value to be stored
    - `next` pointer to the next queue element
- `Queue` is the whole strcture
    - `front` is a pointer to the first element int the queue
    - `rear` pointer to the last element in the queue
    - `node_pool` pointer to the start of the actual array of aviables space for nodes
    - `free_list` list of free pointers on the node pool array (points to same memory blocks just with different logic)
    - `size` current size of the queue
    - `capacity` total capacity of the queue
We have 5 operations
1. `queue_init`: Initializes the queue by requesting `capacity` ammount of `QueueNode` for the list of nodes and assings it into `node_pool`. Sets front, rear and size as null since its empty. And maps `node_pool` nodes to `free_list` since all of the nodes are currently free
1. `queue_enqueue`: Updates the `rear` and `front` if needs. Updates `free_list`. Basically adds a new rear, and moves free_list pointer forward
1. `queue_dequeue`: Same as the past one just removes the front and moves the pointers forward and the dequeued memory goes to the start of `free_list`.
1. `queue_peek`: Returns value of the first element int he queue without removing it.
1. `queue_clear`: Removes all of the elements int he queue. Sets it into a state similar to `queue_init`.

### Binary Heap


## Building
You can build all of the executables with:
```
cmake --build build -j
```
It autogenerates compile_commands.json for clang. (it is soft linked)

