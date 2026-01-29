#include <stdio.h>
#include <stdlib.h>

// Dadas dos matrices, greed[] y cookie[] tales que greed[i]
// denota el tamaño mínimo de cookie deseado por el i-ésimo hijo
// y cookie[i] denota el tamaño de la i-ésima cookie,
// tenemos que encontrar el número máximo de hijos que se pueden
// satisfacer asignándoles cookies, y cada hijo recibirá como máximo 1 galleta.

// - Si b es mayor que a
// 0 si son iguales
// + si a es mayor que b
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int maxChildren(int greed[], int n, int cookie[], int m) {

    // Ordenar los arreglos de niños y galletas de menor a mayor
    qsort(greed, n, sizeof(int), compare);
    qsort(cookie, m, sizeof(int), compare);

    // Punteros al inicio del arreglo
    int i = 0, j = 0;
    // Contador de cuantos niños se han alimentado
    int cnt = 0;

    // Iterar hasta acabar cualquiera de los arreglos
    while (i < n && j < m) {
        // Si el niño i, se alimenta con la galleta i
        // se le asigna y aumenta el contador
        if (greed[i] <= cookie[j]) {
            cnt++;
            i++;
            j++;
        }
        // Si no, se mueve a la sieguiente galleta
        // con el mismo niño
        else 
            j++;
    }
    return cnt;
}

int main() {
    // Niños con hambre 1, 3, 10
    int greed[] = {1, 10, 3};
    // Galletas del tamaño 1, 2, 3
    int cookie[] = {1, 2,3};

    int n = sizeof(greed)/sizeof(greed[0]);
    int m = sizeof(cookie)/sizeof(cookie[0]);

    int result = maxChildren(greed, n, cookie, m);
  
    // Cantidad de niños alimentados
    printf("%d\n", result);
    return 0;
}
