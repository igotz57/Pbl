#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Este programa lee los valores float de un archivo ".csv" que este en la misma carpeta del ".c", los mete a una matriz y enseña la matriz por la consola.

int main()
{
    char str[100];
    char buffer[1024];
    char* record, * line;
    int filas = 0, columnas = 0, x = 0, y = 0;
    double mat[200][5];
    double v_end = 0;
    double v_max = 0;
    int fr = 0;
    double denbora_tarte = 0;
    int ardatza = 2;

    // abre el archivo "datos.csv" en modo lectura. El archivo tiene que estar en la misma carpeta del "main.c"
    FILE* fstream = fopen("datos.csv", "r");

    // si no hay fallo de lectura, leemos el archivo linea a linea
    if (fstream != NULL)
    {
        // este bucle se repite en cada linea del archivo y mete la linea en la variable "line"
        while ((line = fgets(buffer, sizeof(buffer), fstream)) != NULL)
        {
            // la variable "line" se separa por ";" y se mete cada valor en "record"
            record = strtok(line, ";");
            columnas = 0;

            // mientras record no sea "NULL" (vacio) vamos metiendo los valores en la matriz "mat"
            while (record != NULL)
            {
                mat[filas][columnas] = atof(record); // atof para convertir el string en float.
                record = strtok(NULL, ";");
                columnas++;
            }
            ++filas;
        }


    }
    else {
        printf("\n No se ha podido leer el archivo ");
        return -1;
    }

    printf("Sartu sentsorearen muestreo frekuentzia Hz-tan: ");
    fgets(str, 100, stdin);
    sscanf(str, "%i", &fr);

    printf("Aukeratu X edo Y ardatza(1 edo 2): ");
    fgets(str, 100, stdin);
    sscanf(str, "%i", &ardatza);

    
    if (ardatza == 1) {
        ardatza = 0;
    }
    if (ardatza == 2) {
        ardatza = 1;
    }

    denbora_tarte = (double) 1 / fr;
    printf("%lf", denbora_tarte);


    // Dibuja la matriz "mat" en pantalla
    for (x = 0; x < filas; x++) {
        printf(" (");

        for (y = 0; y < columnas; y++) {
            printf("%lf   ", mat[x][y]);
        }
        printf(")\n");

    }
    //abiadura finala
    for (x = 0; x < filas; x++) {
        v_end = v_end + denbora_tarte * mat[x][ardatza];
        if (v_end > v_max) {
            v_max = v_end;
        }
        printf("DEBUG V_END______________%lf\n", v_end);
    }

    printf("Abiadura finala: %lf m/s", v_end);
    printf("Abiadura maximoa: %lf m/s", v_max);
    return 0;
}
