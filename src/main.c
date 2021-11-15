#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "geo.h"
#include "path.h"

// Desaloca memória dos ponteiros.
void freeAll(char *bed, char *geoName, char *bsd, char *qryName, char *mapName) {
    if (bed != NULL)
        free(bed);

    if (geoName != NULL)
        free(geoName);

    if (bsd != NULL)
        free(bsd);

    if (qryName != NULL)
        free(qryName);

    if (mapName != NULL)
        free(mapName);
}

// Manipula os parâmetros da execução.
void readParameters(int argc, char *argv[]) {
    char *bed, *geoName, *bsd, *qryName, *mapName;

    for (int i = 1; i < argc; i++) {
        // Diretório-base de entrada (BED).
        if (strcmp("-e", argv[i]) == 0) {
            bed = (char *)calloc((strlen(argv[++i])) + 2, sizeof(char));
            strcpy(bed, argv[i]);
        }

        // Arquivo com a descrição da cidade.
        if (strcmp("-f", argv[i]) == 0) {
            geoName = (char *)calloc((strlen(argv[++i])) + 2, sizeof(char));
            strcpy(geoName, argv[i]);
        }

        // Diretório-base de saída (BSD).
        if (strcmp("-o", argv[i]) == 0) {
            bsd = (char *)calloc((strlen(argv[++i])) + 2, sizeof(char));
            strcpy(bsd, argv[i]);
        }

        // Arquivo com consultas.
        if (strcmp("-q", argv[i]) == 0) {
            qryName = (char *)calloc((strlen(argv[++i])) + 2, sizeof(char));
            strcpy(qryName, argv[i]);
        }

        // Arquivo de vias (para construção do grafo).
        if (strcmp("-v", argv[i]) == 0) {
            mapName = (char *)calloc((strlen(argv[++i])) + 2, sizeof(char));
            strcpy(mapName, argv[i]);
        }
    }

    // Parâmetros obrigatórios.
    if ((geoName == NULL) || (bsd == NULL)) {
        printf("Faltando algo.\n\n");
        return;
    }

    char *geoAux = catPath(bed, geoName);
    openGeo(geoAux);
    freeAll(bed, geoName, bsd, qryName, mapName);
    free(geoAux);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Few arguments.\n\n");
        return 0;
    }

    readParameters(argc, argv);
    return 0;
}