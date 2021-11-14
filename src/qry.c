#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Lê os argumentos do arquivo ".qry".
void readQryArguments(FILE *qryFile) {
    
}

// Abre o arquivo ".qry" e chama função de leitura de parâmetros.
void openQry(char qryPath[]) {
    FILE *qryFile = fopen(qryPath, "r");

    if (qryFile == NULL) {
        printf("Qry file not found.\n\n");
        return;
    }

    readGeoArguments(qryFile);
    fclose(qryFile);
}