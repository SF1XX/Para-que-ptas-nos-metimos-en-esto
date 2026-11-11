# Explicación Detallada del Código Fuente

Este documento detalla el funcionamiento interno de cada archivo y función del Simulador de Misiones Artemis (Escenario 4), con el objetivo de facilitar su comprensión y defensa durante el coloquio.

---

## 1. `artemis.h` (Cabeceras y Estructuras)
Este es el "contrato" o índice de nuestro módulo principal. Contiene aquello que necesita ser público para que otros archivos lo conozcan.

*   **`#define MASA_ORION 10400.0` y `#define GRAVEDAD 9.80`:** Son constantes globales. Se usa `#define` para no tener "números mágicos" repetidos en el código. Si la masa cambia, se cambia aquí una sola vez.
*   **`typedef struct ParametrosReingreso`:** Agrupa todas las variables físicas (velocidades, alturas, tiempo, hundimiento, ángulo) en un solo bloque de memoria (un registro). Esto es fundamental porque evita que las funciones tengan 8 parámetros distintos; en su lugar, se pasa un solo "paquete" con toda la información.
*   **Prototipos (ej. `void inicializar_parametros(...)`):** Son declaraciones que le avisan al compilador qué funciones existen, qué devuelven (`void`) y qué parámetros reciben. 

---

## 2. `validaciones.h` y `validaciones.c` (Entrada Robusta de Datos)
El objetivo de este módulo es cumplir con el requisito de "Validaciones exhaustivas de entrada" para evitar que el programa se rompa.

*   **`leer_flotante(const char *mensaje, double min, double max)`:**
    *   Imprime un `mensaje` en pantalla pidiendo un dato.
    *   Usa `scanf("%lf", &valor)` para leer un `double`. Retorna la cantidad de elementos leídos correctamente (se guarda en `leidos`).
    *   **El truco clave:** `while (getchar() != '\n');` recorre y limpia cualquier caracter residual en el buffer del teclado (por ejemplo, si el usuario ingresó "hola" en vez de un número). Sin esto, el programa entraría en un bucle infinito.
    *   El bucle `do-while` fuerza al usuario a repetir la entrada si `leidos != 1` (no tipeó un número) o si el número está fuera del rango de `min` y `max`.

---

## 3. `artemis.c` (Lógica Física y Cálculos)
Aquí se implementa la matemática del Escenario 4. Todas las funciones reciben un puntero constante `const ParametrosReingreso *params` (excepto la de inicializar), lo que significa que acceden a los datos originales por referencia, pero no pueden modificarlos accidentalmente.

*   **`inicializar_parametros(ParametrosReingreso *params)`:**
    *   Usa el operador flecha (`->`) para acceder a los campos del struct a través del puntero.
    *   Carga los datos estáticos (11000 m/s, 120000 m) y llama a `leer_flotante` para que el usuario ingrese el resto de los datos interactivos.
*   **`calcular_trabajo_rozamiento(...)`:**
    *   Calcula la Energía Mecánica Inicial ($E_{ci} + E_{pi}$) y la Final ($E_{cf} + E_{pf}$).
    *   Aplica la fórmula: $W_{roz} = E_{m\_final} - E_{m\_inicial}$. Imprime el resultado en notación científica (`%.2e`).
*   **`calcular_desaceleracion_media(...)`:**
    *   Calcula la aceleración: $a = |(V_f - V_i) / \Delta t|$. Usa `fabs()` (valor absoluto para flotantes) de la librería `<math.h>` para asegurar un resultado positivo.
    *   Lo divide por $9.80$ para obtener el valor en "fuerzas G".
*   **`calcular_fuerza_amerizaje(...)`:**
    *   Aplica el principio de trabajo-energía al impacto. La fuerza de frenado del agua tiene que contrarrestar la energía cinética final más el trabajo que hace el peso al hundirse. 
    *   $F_{prom} = (E_{c\_impacto} + Trabajo_{peso}) / d$.
*   **`analizar_angulo_reingreso(...)`:**
    *   Usa condicionales lógicos (`if/else if`) para clasificar el ángulo ingresado, cumpliendo con la ventana de seguridad (5.5° a 7.0°).
*   **`ejecutar_simulacion()`:**
    *   Es la función orquestadora. Declara la variable `sim` de tipo `ParametrosReingreso`.
    *   Llama a todas las funciones pasándoles la dirección de memoria de `sim` usando el operador ampersand (`&sim`).

---

## 4. `main.c` (Punto de Entrada e Interfaz)
*   **`main()`:** Solo tiene la responsabilidad de mostrar la interfaz visual y gestionar el flujo de la aplicación. No hay lógica de cálculos aquí.
*   Usa un bucle `do-while` para mantener el menú abierto hasta que el usuario elija salir (Opción `0`).
*   Usa la estructura `switch(opcion)` para derivar la ejecución. Si es `1`, llama a `ejecutar_simulacion()` del módulo de artemis.

## Pa compilar el proyecto
Mandele esto en la consola y te genera el .exe `gcc main.c artemis.c validaciones.c -o simulador_artemis -lm`
