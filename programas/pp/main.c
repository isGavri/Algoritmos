#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* * Estimar la probabilidad las caras de las monedas
 */

int main() {
    srand(time(NULL));

    int observations[] = {1, 0, 1, 1, 1, 0, 1, 1, 1, 1}; // 1 = cara, 0 = cruz
    int num_obs = 10;
    int simulations = 1000000;
    int matches = 0;
    float total_weight = 0;

    // hypotesis de cara 0.8
    float hypothesis_p = 0.8;

    for (int i = 0; i < simulations; i++) {
        int heads_count = 0;

        // Simular 10 lanzamientos
        for (int j = 0; j < num_obs; j++) {
            float r = (float)rand() / RAND_MAX;
            if (r < hypothesis_p) heads_count++;
        }

        // Es correcta
        if (heads_count == 8) {
            matches++;
        }
    }

    printf("Con %d simulaciones\n", simulations);
    printf("La hipótesis (p=0.8) fue correcta %d veces.\n", matches);
    printf("Inferencia: % .4f\n", (float)matches / simulations);

    return 0;
}
