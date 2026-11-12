// Módulo de Lógica: Implementación de algoritmos de simulación y cálculos físicos[cite: 5].
#include <stdio.h>
#include <math.h>
#include "artemis.h"
#include "validaciones.h"

void inicializar_parametros(ParametrosReingreso *simulacion) {
    // Valores base preestablecidos para el reingreso de la nave Orion
    simulacion->vel_ini = 11000.0;     // Velocidad hiperveloz inicial (m/s)
    simulacion->alt_ini = 120000.0;    // Altitud inicial de reingreso (m)
    simulacion->vel_para = 25.0;       // Rapidez en el momento de despliegue de paracaídas (m/s)
    simulacion->alt_para = 2500.0;     // Altitud de despliegue de paracaídas (m)
    simulacion->v_impacto = 8.0;       // Rapidez final segura al amerizar (m/s)
    
    // Lectura interactiva de parámetros variables mediante validaciones
    printf("\n--- Configuracion de Parametros de Reingreso ---\n");
    simulacion->t_freno = leer_flotante("Ingrese duracion de desaceleracion en seg (ej. 400.0): ", 1.0, 10000.0);
    simulacion->hundimiento = leer_flotante("Ingrese hundimiento en el agua en metros (ej. 1.50): ", 0.1, 100.0);
    simulacion->angulo_reingreso = leer_flotante("Ingrese angulo de reingreso en grados (ej. 6.0): ", 0.0, 90.0);
}

void calcular_trabajo_rozamiento(const ParametrosReingreso *simulacion) {
    // Cálculo del trabajo total por rozamiento atmosférico usando conservación de energía
    double e_ci = 0.5 * MASA_ORION * pow(simulacion->vel_ini, 2);
    double e_pi = MASA_ORION * GRAVEDAD * simulacion->alt_ini;
    double e_cf = 0.5 * MASA_ORION * pow(simulacion->vel_para, 2);
    double e_pf = MASA_ORION * GRAVEDAD * simulacion->alt_para;
    
    double w_roz = (e_cf + e_pf) - (e_ci + e_pi);
    printf("\na. Trabajo total por rozamiento (Wroz): %.2e Joules\n", w_roz);
}

void calcular_desaceleracion_media(const ParametrosReingreso *simulacion) {
    // Cálculo de la desaceleración media experimentada durante la fase atmosférica
    double a = fabs((simulacion->vel_para - simulacion->vel_ini) / simulacion->t_freno);
    double a_g = a / GRAVEDAD;
    printf("b. Desaceleracion media: %.2f m/s^2 (%.2f g)\n", a, a_g);
}

void calcular_fuerza_amerizaje(const ParametrosReingreso *simulacion) {
    // Determinación de la fuerza promedio del agua sobre el módulo durante el impacto
    double e_c_impacto = 0.5 * MASA_ORION * pow(simulacion->v_impacto, 2);
    double trabajo_peso = MASA_ORION * GRAVEDAD * simulacion->hundimiento;
    double f_prom = (e_c_impacto + trabajo_peso) / simulacion->hundimiento;
    double peso = MASA_ORION * GRAVEDAD;
    
    printf("c. Fuerza promedio del agua: %.2f N (%.2f veces el peso)\n", f_prom, f_prom / peso);
}

void analizar_angulo_reingreso(const ParametrosReingreso *simulacion) {
    // Evaluación del ángulo de reingreso respecto a los límites de seguridad de la trayectoria
    printf("d. Analisis del angulo de reingreso (%.2f grados): ", simulacion->angulo_reingreso);
    if (simulacion->angulo_reingreso > 7.0) {
        printf("Desaceleracion excesiva (angulo muy empinado).\n");
    } else if (simulacion->angulo_reingreso < 5.5) {
        printf("Rebote atmosferico (angulo muy plano).\n");
    } else {
        printf("Angulo dentro de la ventana de seguridad.\n");
    }
}

void ejecutar_simulacion() {
    // Función controladora principal que instancia el estado e invoca los cálculos
    ParametrosReingreso simulacion;
    
    inicializar_parametros(&simulacion);
    calcular_trabajo_rozamiento(&simulacion);
    calcular_desaceleracion_media(&simulacion);
    calcular_fuerza_amerizaje(&simulacion);
    analizar_angulo_reingreso(&simulacion);
}
