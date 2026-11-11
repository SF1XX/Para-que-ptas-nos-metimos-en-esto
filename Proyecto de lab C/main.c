// Módulo Principal: Contiene únicamente main(), menú principal y flujo general[cite: 5].
#include <stdio.h>
#include <stdlib.h>
#include "artemis.h"

int main() {
    int opcion;
    do {
        // Interfaz interactiva y coherente con el escenario asignado incorporando menú principal[cite: 2].
        printf("\n======================================================\n");
        printf(" SIMULADOR MISIONES ARTEMIS - ESCENARIO 4 (REINGRESO) \n");
        printf("======================================================\n");
        printf("1. Iniciar Simulacion\n");
        printf("0. Salir\n");
        printf("======================================================\n");
        printf("Seleccione una opcion: ");
        
        if (scanf("%d", &opcion) != 1) {
            while(getchar() != '\n'); 
            opcion = -1;
        }
        
        switch (opcion) {
            case 1:
                ejecutar_simulacion();
                break;
            case 0:
                printf("Saliendo de la simulacion...\n");
                break;
            default:
                printf("Opcion invalida. Intente nuevamente.\n");
        }
    } while (opcion != 0);
    
    return 0;
}