#include <stdio.h>
#include <string.h>  
#include "funciones.h"

// Funcion menu
void menu(){
    printf("1. Ingresar datos de contaminacion\n");
    printf("2. Ingresar datos climaticos\n");
    printf("3. Mostrar datos de contaminacion\n");
    printf("4. Predecir contaminacion\n");
    printf("5. Calcular promedio de contaminacion\n");
    printf("6. Generar recomendaciones\n");
    printf("7. Salir\n");
}


// Funcion para ingresar los datos de contaminacion de una zona
void ingresarDatosContaminacion(struct Contaminacion *contaminacion) {
    do {
        printf("Ingrese el nivel en porcentaje de CO2: ");
        scanf("%f", &contaminacion->co2);
    } while (contaminacion->co2 < 0);

    do {
        printf("Ingrese el nivel en porcentaje de SO2: ");
        scanf("%f", &contaminacion->so2);
    } while (contaminacion->so2 < 0);

    do {
        printf("Ingrese el nivel en porcentaje de NO2: ");
        scanf("%f", &contaminacion->no2);
    } while (contaminacion->no2 < 0);

    do {
        printf("Ingrese el nivel en porcentaje de PM2.5: ");
        scanf("%f", &contaminacion->pm25);
    } while (contaminacion->pm25 < 0);
}

// Funcion para ingresar los datos climaticos
void ingresarDatosClima(struct Clima *clima) {
    do {
        printf("Ingrese la temperatura: ");
        scanf("%f", &clima->temperatura);
    } while (clima->temperatura < 0);

    do {
        printf("Ingrese la velocidad del viento: ");
        scanf("%f", &clima->velocidad_viento);
    } while (clima->velocidad_viento < 0);

    do {
        printf("Ingrese el nivel de humedad: ");
        scanf("%f", &clima->humedad);
    } while (clima->humedad < 0);
}

// Funcion para mostrar los datos de contaminacion
void mostrarDatosContaminacion(struct Contaminacion contaminacion) {
    printf("%.2f\t|\t%.2f\t|\t%.2f\t|\t%.2f\n", contaminacion.co2,
                                                 contaminacion.so2,
                                                 contaminacion.no2,
                                                 contaminacion.pm25);
}

// Funcion para predecir la contaminacion basada en los datos historicos y climaticos
void predecirContaminacion(struct Contaminacion zonas[], int n, struct Clima clima[], float predicciones[], int dias) {
    for (int i = 0; i < n; i++) {
        float suma = 0;
        for (int j = 0; j < dias; j++) {
            suma += (zonas[i].co2 + zonas[i].so2 + zonas[i].no2 + zonas[i].pm25) * (1 + clima[j].temperatura / 100.0);
        }
        predicciones[i] = suma / dias;
    }
}

// Funcion para calcular el promedio de contaminacion historica
void calcularPromedioContaminacion(struct Contaminacion zonas[], int n, float promedios[], int dias) {
    for (int i = 0; i < n; i++) {
        float suma = 0;
        for (int j = 0; j < dias; j++) {
            suma += (zonas[i].co2 + zonas[i].so2 + zonas[i].no2 + zonas[i].pm25);
        }
        promedios[i] = suma / dias;
    }
}

// Funcion para generar recomendaciones segun los niveles de contaminacion previstos
void generarRecomendaciones(float predicciones[], int n) {
    for (int i = 0; i < n; i++) {
        if (predicciones[i] > 100) {
            printf("Alerta en Zona %d: Se recomienda reducir el trafico vehicular y suspender actividades al aire libre.\n", i+1);
        } else {
            printf("Zona %d: Niveles de contaminacion aceptables.\n", i+1);
        }
    }
}

// Funcion para guardar los datos en un archivo
void guardarDatosArchivo(struct Contaminacion zonas[], int n, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(archivo, "%.2f %.2f %.2f %.2f\n", zonas[i].co2, zonas[i].so2, zonas[i].no2, zonas[i].pm25);
    }

    fclose(archivo);
}

// Funcion para leer los datos desde un archivo
void leerDatosArchivo(struct Contaminacion zonas[], int n, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fscanf(archivo, "%f %f %f %f", &zonas[i].co2, &zonas[i].so2, &zonas[i].no2, &zonas[i].pm25);
    }

    fclose(archivo);
}
