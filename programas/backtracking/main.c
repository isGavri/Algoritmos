#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// *** Dynamic Array *** 

typedef struct {
  int *items;
  size_t count;
  size_t capacity;
} Numbers;

typedef struct {
  Numbers *items;
  size_t count;
  size_t capacity;
} Subsets;

// Append for the dynamic arrays
#define append(xs, x)                                                    \
  do                                                                     \
  {                                                                      \
    if (xs.count >= xs.capacity)                                         \
    {                                                                    \
      if (xs.capacity == 0)                                              \
        xs.capacity = 256;                                               \
      else                                                               \
        xs.capacity *= 2;                                                \
      xs.items = realloc(xs.items, xs.capacity * sizeof(*xs.items));     \
    }                                                                    \
    xs.items[xs.count++] = x;                                            \
  } while (0)


void subsetRecur(size_t i, Numbers *arr, Subsets *res, Numbers *subset) {
    
    // Base Case: Add subset to result
    if (i == arr->count) {
        Numbers copy = {0};
        if (subset->count > 0) {

            copy.items = malloc(subset->count * sizeof(int));

            memcpy(copy.items, subset->items, subset->count * sizeof(int));
            copy.count = subset->count;
            copy.capacity = subset->count;
        }
        append((*res), copy); 
        return;
    }

    append((*subset), arr->items[i]);
    subsetRecur(i + 1, arr, res, subset);

    subset->count--; 
    subsetRecur(i + 1, arr, res, subset);
}

// Wrapper Function
Subsets subsets(Numbers *arr) {
    Numbers subset = {0};
    Subsets res = {0};

    subsetRecur(0, arr, &res, &subset);

    // Clean up the temporary working buffer
    free(subset.items); 

    return res;
}


int main() {
    Numbers arr = {0};
    append(arr, 1);
    append(arr, 2);
    append(arr, 3);

    // Genera subconjuntos
    Subsets res = subsets(&arr);

    for (size_t i = 0; i < res.count; i++) {
        printf("[");
        for (size_t j = 0; j < res.items[i].count; j++) {
            printf("%d", res.items[i].items[j]);
            if (j != res.items[i].count - 1) printf(", ");
        }
        printf("]\n");
    }

    // Free memoria
    for (size_t i = 0; i < res.count; i++) {
        free(res.items[i].items);
    }

    free(res.items);
    free(arr.items);

    return 0;
}
