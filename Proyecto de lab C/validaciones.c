// Módulo de Validaciones e Interfaz: Funciones dedicadas al ingreso seguro de datos[cite: 5].
#include <stdio.h>
#include "validaciones.h"

double leer_flotante(const char *mensaje, double min, double max) {
    double valor;
    int leidos;
    do {
        printf("%s", mensaje);
        leidos = scanf("%lf", &valor);
        while (getchar() != '\n'); 
        
        // Mecanismos de validación de entradas de usuario[cite: 1].
        if (leidos != 1 || valor < min || valor > max) {
            printf("Error: Ingrese un valor valido entre %.2f y %.2f.\n", min, max);
        }
    } while (leidos != 1 || valor < min || valor > max);
    
    return valor;
}