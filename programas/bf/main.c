// Brute force aloritmo para adivinar un digito
#include <stdbool.h>
#include <stdio.h>

int posibilities[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int adivinar(int n)
{
    for (int i = 0; i < 10; i++)
    {
        if (n == posibilities[i])
        {
            printf("%d correcto. Encontrado\n", posibilities[i]);
            return posibilities[i];
        }
        printf("%d incorrecto. No encontrado\n", posibilities[i]);
    }

    return -1;
}
int main()
{
    int dig = 8;
    int resultado = adivinar(dig);
    printf("El numero es: %d\n", resultado);
    return 0;
}
