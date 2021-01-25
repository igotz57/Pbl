#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
float abiadura_final(float array[200][5], int filak, float denbora);
void abiadura_maximoa(float array[200][5], int filak, float denbora);
void azelerazio_maximoa(float array[200][5], int filak, float denbora);

// Este programa lee los valores float de un archivo ".csv" que este en la misma carpeta del ".c", los mete a una matriz y enseña la matriz por la consola.

int main()
{
    char str[100];
    char buffer[1024];
    char* record, * line;
    int filas = 0, columnas = 0, x = 0, y = 0;
    float mat[200][5];
    float v_end = 0;
    float fr = 0;
    float denbora_tarte = 0;
    int num_opcion = 0;
    int ardatza = 0;

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

    //DENBORA-TARTEA
    printf("Sartu sentsorearen muestreo frekuentzia Hz-tan: ");
    fgets(str, 100, stdin);
    sscanf(str, "%f", &fr);
    denbora_tarte = 1 / fr;
    printf("\n");

    //Ardatzak
    printf("Aukeratu X edo Y ardatza(1 edo 2): ");
    fgets(str, 100, stdin);
    sscanf(str, "%i", &ardatza);


    if (ardatza == 1) {
        ardatza = 0;
    }
    if (ardatza == 2) {
        ardatza = 1;
    }

    //MENUA
    printf(" Hurrengo aukeretatik jakin nahi duzun datuaren zenbakia idatzi:\n");
    printf(" 1 - Bukaerako abiadura\n");
    printf(" 2 - Abiadura maximoa eta zein unean den\n");
    printf(" 3 - Azelerazio maximoa eta zein unean den\n");
    printf(" 4 - Zein izan den datuak hartzreakoan denbora-tartea \n");

    printf("Idatzi ezazu jakin nahi duzun datuaren zenbakia\n");
    fgets(str, 100, stdin);
    sscanf(str, "%i", &num_opcion);
    printf("\n\n");


    //AUKERAK
    if (num_opcion == 1) {
        v_end = abiadura_final(mat, filas, denbora_tarte, ardatza);
        printf("Abiadura finala: %f m/s da\n", v_end);
    }
    if (num_opcion == 2) {
        abiadura_maximoa(mat, filas, denbora_tarte, ardatza);
    }
    if (num_opcion == 3) {
        azelerazio_maximoa(mat, filas, denbora_tarte, ardatza);
    }
    if (num_opcion == 4) {
        printf("Datuak hartzerakoan denbora-tartea %f segundu izan da\n\n", denbora_tarte);
    }

    return 0;
}

//Abiadura finala lortzeko
float abiadura_final(float array[200][5], int filak, float denbora) {
    float v_buk = 0;
    int x = 0;

    for (x = 0; x < filak; x++) {
        v_buk = v_buk + denbora * array[x][1];
    }
    return v_buk;
}
//Abiadura maximoa lortzeko
void abiadura_maximoa(float array[200][5], int filak, float denbora, int ardatza) {
    float v_max = 0;
    int x = 0;
    int y = 0;
    float v_buk = 0;
    float tiempo = 0;
    float t_max = 0;
    for (x = 0; x < filak; x++) {
        v_buk = v_buk + (denbora * array[x][ardatza]);
        tiempo = tiempo + denbora;
        if (v_buk > v_max) {
            v_max = v_buk;
            t_max = tiempo;
        }
    }

    printf("Abiadura maximoa %f m/s da eta %f segunduan gertatzen da.\n", v_max, t_max);
}
//Azelerazio maximoa lortzeko
void azelerazio_maximoa(float array[200][5], int filak, float denbora, int ardatza) {
    float a_max = 0;
    int x = 0;
    float tiempo = 0;
    float t_max = 0;

    for (x = 0; x < filak; x++) {
        tiempo = tiempo + denbora;
        if (array[x][1] > a_max) {
            a_max = array[x][ardatza];
            t_max = tiempo;
        }
    }

    printf("Azelerazio maximoa %f m/s da eta %f segunduan gertatzen da.\n", a_max, t_max);
}
