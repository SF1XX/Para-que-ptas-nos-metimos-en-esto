// Módulo de Lógica: Implementación de algoritmos de simulación y cálculos físicos[cite: 5].
#include <stdio.h>
#include <math.h>
#include "artemis.h"
#include "validaciones.h"

void inicializar_parametros(ParametrosReingreso *params) {
    params->v_i = 11000.0; // Velocidad hiperveloz inicial[cite: 4].
    params->h_i = 120000.0; // Altitud inicial[cite: 4].
    params->v_f = 25.0; // Rapidez de despliegue de paracaídas[cite: 4].
    params->h_f = 2500.0; // Altitud de despliegue de paracaídas[cite: 4].
    params->v_impacto = 8.0; // Rapidez final segura[cite: 4].
    
    printf("\n--- Configuracion de Parametros ---\n");
    params->delta_t = leer_flotante("Ingrese duracion de desaceleracion en seg (ej. 400.0): ", 1.0, 10000.0);
    params->hundimiento_d = leer_flotante("Ingrese hundimiento en el agua en metros (ej. 1.50): ", 0.1, 100.0);
    params->angulo_reingreso = leer_flotante("Ingrese angulo de reingreso en grados (ej. 6.0): ", 0.0, 90.0);
}

void calcular_trabajo_rozamiento(const ParametrosReingreso *params) {
    // Cálculo del trabajo total Wroz por rozamiento atmosférico[cite: 5].
    double e_ci = 0.5 * MASA_ORION * pow(params->v_i, 2);
    double e_pi = MASA_ORION * GRAVEDAD * params->h_i;
    double e_cf = 0.5 * MASA_ORION * pow(params->v_f, 2);
    double e_pf = MASA_ORION * GRAVEDAD * params->h_f;
    
    double w_roz = (e_cf + e_pf) - (e_ci + e_pi);
    printf("\na. Trabajo total por rozamiento (Wroz): %.2e Joules\n", w_roz);
}

void calcular_desaceleracion_media(const ParametrosReingreso *params) {
    // Cálculo de la desaceleración media en m/s^2 y g[cite: 5].
    double a = fabs((params->v_f - params->v_i) / params->delta_t);
    double a_g = a / GRAVEDAD;
    printf("b. Desaceleracion media: %.2f m/s^2 (%.2f g)\n", a, a_g);
}

void calcular_fuerza_amerizaje(const ParametrosReingreso *params) {
    // Determinación de la fuerza promedio Fprom del agua durante el amerizaje[cite: 5].
    double e_c_impacto = 0.5 * MASA_ORION * pow(params->v_impacto, 2);
    double trabajo_peso = MASA_ORION * GRAVEDAD * params->hundimiento_d;
    double f_prom = (e_c_impacto + trabajo_peso) / params->hundimiento_d;
    double peso = MASA_ORION * GRAVEDAD;
    
    printf("c. Fuerza promedio del agua: %.2f N (%.2f veces el peso)\n", f_prom, f_prom / peso);
}

void analizar_angulo_reingreso(const ParametrosReingreso *params) {
    // Evaluación de ventana de seguridad del ángulo de reingreso[cite: 5].
    printf("d. Analisis del angulo de reingreso (%.2f grados): ", params->angulo_reingreso);
    if (params->angulo_reingreso > 7.0) {
        printf("Desaceleracion excesiva.\n"); // Evaluación si y > 7.0[cite: 5].
    } else if (params->angulo_reingreso < 5.5) {
        printf("Rebote atmosferico.\n"); // Evaluación si y < 5.5[cite: 5].
    } else {
        printf("Angulo dentro de la ventana de seguridad.\n");
    }
}

void ejecutar_simulacion() {
    ParametrosReingreso sim;
    inicializar_parametros(&sim);
    calcular_trabajo_rozamiento(&sim);
    calcular_desaceleracion_media(&sim);
    calcular_fuerza_amerizaje(&sim);
    analizar_angulo_reingreso(&sim);
}