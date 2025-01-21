#include <stdio.h>
#include "funciones.h"

#define ZONAS 5
#define DIAS 30

int main()
{
    struct Contaminacion zonas[ZONAS];
    struct Clima clima[DIAS];
    float predicciones[ZONAS];
    float promedios[ZONAS];
    int opcion;

    leerDatosArchivo(zonas, ZONAS, "contaminacion.txt");
    leerDatosArchivoClima(clima, DIAS, "clima.txt");
    caratula();
    do
    {
        printf("\n=========================================\n");
        menu();
        scanf("%d", &opcion);
        printf("\n=========================================\n");
        switch (opcion)
        {
        case 1:
            // Ingresar datos de contaminacion
            for (int i = 0; i < ZONAS; i++)
            {
                printf("\nIngrese los datos de contaminacion para la Zona %d:\n", i + 1);
                ingresarDatosContaminacion(&zonas[i]);
            }
            break;
        case 2:
            // Ingresar datos climaticos para cada dia
            for (int i = 0; i < DIAS; i++)
            {
                printf("\nIngrese los datos climaticos para el Dia %d:\n", i + 1);
                ingresarDatosClima(&clima[i]);
            }
            break;
        case 3:
            // Mostrar los datos de contaminacion
            printf("\nDatos de Contaminacion:\n");
            printf("\t\tCO2\t|\tSO2\t|\tNO2\t|\tPM2.5\n");
            for (int i = 0; i < ZONAS; i++)
            {
                printf("Zona %d:\t\t", i + 1);
                mostrarDatosContaminacion(zonas[i]);
            }
            break;
        case 4:
            // Mostrar los datos climaticos
            printf("\nDatos Climaticos:\n");
            printf("\tTemperatura\t|\tVelocidad Viento\t|\tHumedad\n");
            for (int i = 0; i < DIAS; i++)
            {
                printf("Dia %d:\t\t", i + 1);
                mostrarDatosClima(clima[i]);
            }
            break;
        case 5:
            // Calcular promedios de contaminacion
            printf("\nCalculando promedios de contaminacion...\n");
            calcularPromedioContaminacion(zonas, ZONAS, promedios, DIAS);
            printf("Promedios calculados exitosamente.\n\n");
            for (int i = 0; i < ZONAS; i++)
            {
                printf("Promedio de contaminacion en Zona %d: %.2f\n", i + 1, promedios[i]);
            }
            printf("\n");
            break;
        case 6:
            // Predecir contaminacion futura
            printf("\nCalculando predicciones de contaminacion futura...\n");
            predecirContaminacion(zonas, ZONAS, clima, predicciones, DIAS);
            printf("\n");
            printf("Predicciones calculadas exitosamente.\n\n");
            for (int i = 0; i < ZONAS; i++)
            {
                printf("Prediccion para la Zona %d: %.2f\n", i + 1, predicciones[i]);
            }
            printf("\n");
            break;
        case 7:
            // Generar recomendaciones
            printf("\nGenerando recomendaciones basadas en las predicciones...\n");
            generarRecomendaciones(predicciones, ZONAS);
            printf("Recomendaciones generadas exitosamente.\n");
            break;
        case 8:
            printf("Saliendo del programa...\n");
            break;
        }
    } while (opcion != 8);

    // Guardar los datos en un archivo
    guardarDatosArchivo(zonas, ZONAS, "contaminacion.txt");
    guardarDatosArchivoClima(clima, DIAS, "clima.txt");
    return 0;
}
