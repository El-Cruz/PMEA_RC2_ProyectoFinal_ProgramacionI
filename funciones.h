// Estructura para almacenar los datos de contaminacion
struct Contaminacion {
    float co2;
    float so2;
    float no2;
    float pm25;
};

// Estructura para almacenar las condiciones climaticas
struct Clima {
    float temperatura;
    float velocidad_viento;
    float humedad;
};

// Prototipos de las funciones
void menu();
void ingresarDatosContaminacion(struct Contaminacion *contaminacion);
void ingresarDatosClima(struct Clima *clima);
void mostrarDatosContaminacion(struct Contaminacion contaminacion);
void predecirContaminacion(struct Contaminacion zonas[], int n, struct Clima clima[], float predicciones[], int dias);
void calcularPromedioContaminacion(struct Contaminacion zonas[], int n, float promedios[], int dias);
void generarRecomendaciones(float predicciones[], int n);
void guardarDatosArchivo(struct Contaminacion zonas[], int n, const char *nombreArchivo);
void leerDatosArchivo(struct Contaminacion zonas[], int n, const char *nombreArchivo);