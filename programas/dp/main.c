// Given an integer n, the task is to find the first n rows of Pascal's
// triangle. Pascal's triangle is a triangular array of binomial coefficients.

#include <stdio.h>
#include <stdlib.h>

int** pascal(int n)
{
    // Arreglo auxiliar para guardar valores del triangulo
    int** mat = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        // Reserva espacio para cada entero de las filas
        mat[i] = (int*)malloc((i + 1) * sizeof(int));
    }

    // Las columnas son iguales al valor de la fila
    for (int row = 0; row < n; row++)
    {
        for (int i = 0; i <= row; i++)
        {
            // primer y ultimo siempre 1
            if (row == i || i == 0)
                mat[row][i] = 1;
            // 
            // Suma de izq der arriba
            else
                mat[row][i] = mat[row - 1][i - 1] + mat[row - 1][i];
        }
    }
    return mat;
}

int main()
{
    int n = 5;
    int** mat = pascal(n);
    // Imprime la matriz
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    return 0;
}
