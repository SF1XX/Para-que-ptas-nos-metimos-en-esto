// Módulo de Cabecera: Declaración de constantes, definición de tipos estructurados y prototipos[cite: 5].
#ifndef ARTEMIS_H
#define ARTEMIS_H

#define MASA_ORION 10400.0 // Masa del módulo Orion en kg[cite: 4].
#define GRAVEDAD 9.80

// Estructura de datos para representar entidades y estados[cite: 1].
typedef struct {
    double v_i; // 11000.0 m/s[cite: 4].
    double h_i; // 120000.0 m[cite: 4].
    double v_f; // 25.0 m/s[cite: 4].
    double h_f; // 2500.0 m[cite: 4].
    double v_impacto; // 8.0 m/s[cite: 4].
    double delta_t;
    double hundimiento_d;
    double angulo_reingreso;
} ParametrosReingreso;

void inicializar_parametros(ParametrosReingreso *params);
void calcular_trabajo_rozamiento(const ParametrosReingreso *params);
void calcular_desaceleracion_media(const ParametrosReingreso *params);
void calcular_fuerza_amerizaje(const ParametrosReingreso *params);
void analizar_angulo_reingreso(const ParametrosReingreso *params);
void ejecutar_simulacion();

#endif