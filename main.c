#include <stdio.h>
#include "funciones.h"

#define ZONAS 5
#define DIAS 30

int main() {
    struct Contaminacion zonas[ZONAS];
    struct Clima clima[DIAS];
    float predicciones[ZONAS];
    float promedios[ZONAS];

    // Ingresar datos de contaminacion para cada zona
    for (int i = 0; i < ZONAS; i++) {
        printf("\nIngrese los datos de contaminacion para la Zona %d:\n", i+1);
        ingresarDatosContaminacion(&zonas[i]);
    }

    // Ingresar datos climaticos para cada día
    for (int i = 0; i < DIAS; i++) {
        printf("\nIngrese los datos climaticos para el Dia %d:\n", i+1);
        ingresarDatosClima(&clima[i]);
    }

    // Mostrar los datos de contaminacion
    for (int i = 0; i < ZONAS; i++) {
        printf("\nDatos de la Zona %d:\n", i+1);
        mostrarDatosContaminacion(zonas[i]);
    }

    // Calcular promedios de contaminacion
    calcularPromedioContaminacion(zonas, ZONAS, promedios, DIAS);

    // Predecir contaminacion futura
    predecirContaminacion(zonas, ZONAS, clima, predicciones, DIAS);

    // Generar recomendaciones
    generarRecomendaciones(predicciones, ZONAS);

    // Guardar los datos en un archivo
    guardarDatosArchivo(zonas, ZONAS, "contaminacion.txt");

    return 0;
}
