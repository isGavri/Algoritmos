#include <stdio.h>

#define INF 99999
#define V 5 // Número de vértices (A, B, C, D, E)

void imprimirMatriz(int matriz[][V]);

void floydWarshall(int grafo[][V]) {
    int dist[V][V], i, j, k;

    // Inicializar la matriz de distancias con los valores del grafo
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = grafo[i][j];

    // Iterar sobre cada nodo como intermediario (k)
    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                // Si el camino a través de k es más corto, actualizamos
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    imprimirMatriz(dist);
}

void imprimirMatriz(int matriz[][V]) {
    char nodos[] = {'A', 'B', 'C', 'D', 'E'};
    printf("Matriz de distancias mas cortas entre todos los pares:\n\t");
    for (int i = 0; i < V; i++) printf("%c\t", nodos[i]);
    printf("\n");

    for (int i = 0; i < V; i++) {
        printf("%c\t", nodos[i]);
        for (int j = 0; j < V; j++) {
            if (matriz[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Definición del grafo según la imagen
    // A=0, B=1, C=2, D=3, E=4
    int grafo[V][V] = {
        {0,   5,   1,   INF, INF}, // A
        {INF, 0,   INF, 3,   INF}, // B
        {INF, INF, 0,   INF, 2},   // C
        {6,   INF, INF, 0,   4},   // D
        {INF, INF, INF, INF, 0}    // E
    };

    floydWarshall(grafo);
    return 0;
}

