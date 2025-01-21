#include <stdio.h>
#include <string.h>  
#include "funciones.h"

//Funcion caratula
void caratula(){
    printf("\n\n\tUniversidad De Las Americas\n");
    printf("\nFacultad de Ingenieria en Sistemas\n");
    printf("\n=========================================\n");
    printf("\nGrupo:\nMichael Cordova\nNicolas Cruz\n");
    printf("\n=========================================\n");
    printf("Sistema Integral de Gestion y Prediccion de Contaminacion \ndel Aire en Zonas Urbanas\n");
    printf("\n=========================================\n");
}   

// Funcion menu
void menu(){
    printf("\n");
    printf("1. Ingresar datos de contaminacion\n");
    printf("2. Ingresar datos climaticos\n");
    printf("3. Mostrar datos de contaminacion\n");
    printf("4. Mostrar datos de clima\n");
    printf("5. Calcular promedio de contaminacion\n");
    printf("6. Predecir contaminacion\n");
    printf("7. Generar recomendaciones\n");
    printf("8. Salir\n");
}

// Funcion para ingresar los datos de contaminacion de una zona
void ingresarDatosContaminacion(struct Contaminacion *contaminacion) {
    do {
        printf("Ingrese el nivel en ppb de CO2: ");
        scanf("%f", &contaminacion->co2);
        if (contaminacion->co2 < 0) {
            printf("No vale ingresar numeros negativos. Vuelva a ingresar.\n");
        }
    } while (contaminacion->co2 < 0);

    do {
        printf("Ingrese el nivel en ppb de SO2: ");
        scanf("%f", &contaminacion->so2);
        if (contaminacion->so2 < 0) {
            printf("No vale ingresar numeros negativos. Vuelva a ingresar.\n");
        }
    } while (contaminacion->so2 < 0);

    do {
        printf("Ingrese el nivel en ppb de NO2: ");
        scanf("%f", &contaminacion->no2);
        if (contaminacion->no2 < 0) {
            printf("No vale ingresar numeros negativos. Vuelva a ingresar.\n");
        }
    } while (contaminacion->no2 < 0);

    do {
        printf("Ingrese el nivel en ug/m^3 de PM2.5: ");
        scanf("%f", &contaminacion->pm25);
        if (contaminacion->pm25 < 0) {
            printf("No vale ingresar numeros negativos. Vuelva a ingresar.\n");
        }
    } while (contaminacion->pm25 < 0);
}

// Funcion para ingresar los datos climaticos
void ingresarDatosClima(struct Clima *clima) {
        
        printf("Ingrese la temperatura: ");
        scanf("%f", &clima->temperatura);

    do {
        printf("Ingrese la velocidad del viento: ");
        scanf("%f", &clima->velocidad_viento);
        if (clima->velocidad_viento < 0) {
            printf("No vale ingresar numeros negativos. Vuelva a ingresar.\n");
        }
    } while (clima->velocidad_viento < 0);

    do {
        printf("Ingrese el nivel de humedad: ");
        scanf("%f", &clima->humedad);
        if (clima->humedad < 0) {
            printf("No vale ingresar numeros negativos. Vuelva a ingresar.\n");
        }
    } while (clima->humedad < 0);
}

// Funcion para mostrar los datos de contaminacion
void mostrarDatosContaminacion(struct Contaminacion contaminacion) {
    printf("%.2f\t|\t%.2f\t|\t%.2f\t|\t%.2f\n", contaminacion.co2,
                                                 contaminacion.so2,
                                                 contaminacion.no2,
                                                 contaminacion.pm25);
}

// Funcion para mostrar los datos climaticos
void mostrarDatosClima(struct Clima clima) {
    printf("%.2f\t|\t\t%.2f\t\t|\t%.2f\n", clima.temperatura,
                                        clima.velocidad_viento,
                                        clima.humedad);
}
                    
//Funcion para comparar los datos de contaminacion con los limites de la OMS
void predecirContaminacion(struct Contaminacion zonas[], int n, struct Clima clima[], float predicciones[], int dias) {
    // Límites de contaminación basados en estándares (como los de la OMS)
    const float limiteCO2 = 405.0;
    const float limiteSO2 = 16.0;
    const float limiteNO2 = 10.0;
    const float limitePM25 = 15.0;

    for (int i = 0; i < n; i++) {
        float sumaCO2 = 0, sumaSO2 = 0, sumaNO2 = 0, sumaPM25 = 0;

        // Promediar los niveles históricos ajustados por factores climáticos
        for (int j = 0; j < dias; j++) {
            sumaCO2 += zonas[i].co2 * (1 + clima[j].temperatura / 100.0);
            sumaSO2 += zonas[i].so2 * (1 + clima[j].humedad / 100.0);
            sumaNO2 += zonas[i].no2 * (1 - clima[j].velocidad_viento / 100.0);
            sumaPM25 += zonas[i].pm25 * (1 + clima[j].temperatura / 100.0);
        }

        // Calcular los promedios para cada contaminante
        float promedioCO2 = sumaCO2 / dias;
        float promedioSO2 = sumaSO2 / dias;
        float promedioNO2 = sumaNO2 / dias;
        float promedioPM25 = sumaPM25 / dias;

        // Guardar el promedio total de contaminación para la zona
        predicciones[i] = promedioCO2 + promedioSO2 + promedioNO2 + promedioPM25;

        // Bandera para determinar si alguna alerta debe emitirse
        int alertaEmitida = 0;

        // Emitir alertas si los promedios exceden los límites
        if (promedioCO2 > limiteCO2) {
            if (!alertaEmitida) {
                printf("Zona %d:\n", i + 1);
                alertaEmitida = 1;
            }
            printf("  Alerta: CO2 (%.2f) supera el límite permitido (%.2f).\n", promedioCO2, limiteCO2);
        }
        if (promedioSO2 > limiteSO2) {
            if (!alertaEmitida) {
                printf("Zona %d:\n", i + 1);
                alertaEmitida = 1;
            }
            printf("  Alerta: SO2 (%.2f) supera el límite permitido (%.2f).\n", promedioSO2, limiteSO2);
        }
        if (promedioNO2 > limiteNO2) {
            if (!alertaEmitida) {
                printf("Zona %d:\n", i + 1);
                alertaEmitida = 1;
            }
            printf("  Alerta: NO2 (%.2f) supera el límite permitido (%.2f).\n", promedioNO2, limiteNO2);
        }
        if (promedioPM25 > limitePM25) {
            if (!alertaEmitida) {
                printf("Zona %d:\n", i + 1);
                alertaEmitida = 1;
            }
            printf("  Alerta: PM2.5 (%.2f) supera el límite permitido (%.2f).\n", promedioPM25, limitePM25);
        }
    }
}

// Funcion para calcular el promedio de contaminacion historica
void calcularPromedioContaminacion(struct Contaminacion zonas[], int n, float promedios[], int dias) {
    for (int i = 0; i < n; i++) {
        float sumaCO2 = 0, sumaSO2 = 0, sumaNO2 = 0, sumaPM25 = 0;

        // Sumar los datos históricos de contaminación para cada día
        for (int j = 0; j < dias; j++) {
            sumaCO2 += zonas[i].co2; // Cambiado zonas[j] por zonas[i]
            sumaSO2 += zonas[i].so2;
            sumaNO2 += zonas[i].no2;
            sumaPM25 += zonas[i].pm25;
        }

        // Calcular el promedio total para la zona
        promedios[i] = (sumaCO2 + sumaSO2 + sumaNO2 + sumaPM25) / dias;
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

// Funcion para guardar los datos de contaminacion en un archivo
void guardarDatosArchivo(struct Contaminacion zonas[], int n, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(archivo, "%.2f %.2f %.2f %.2f\n", 
                zonas[i].co2, zonas[i].so2, zonas[i].no2, zonas[i].pm25);
    }

    fclose(archivo);
    printf("Datos de contaminacion guardados en '%s'.\n", nombreArchivo);
}

// Funcion para guardar los datos climaticos en un archivo
void guardarDatosArchivoClima(struct Clima clima[], int n, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(archivo, "%.2f %.2f %.2f\n", 
                clima[i].temperatura, clima[i].velocidad_viento, clima[i].humedad);
    }

    fclose(archivo);
    printf("Datos climaticos guardados en '%s'.\n", nombreArchivo);
}

// Funcion para leer los datos desde el archivo contaminación
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
// Funcion para leer los datos desde el archivo clima
void leerDatosArchivoClima(struct Clima clima[], int n, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fscanf(archivo, "%f %f %f", &clima[i].temperatura, &clima[i].velocidad_viento, &clima[i].humedad);
    }

    fclose(archivo);
}
