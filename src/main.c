#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "geo.h"
#include "map.h"
#include "path.h"
#include "qry.h"

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

// Verifica se os parâmetros obrigatórios foram preenchidos. 0 = Não; 1 = Sim.
int verify(char *bed, char *geoName, char *bsd, char *qryName, char *mapName) {
    if ((geoName == NULL) || (bsd == NULL)) {
        freeAll(bed, geoName, bsd, qryName, mapName);
        return 0;
    }

    return 1;
}

// Abre os arquivos ".geo", ".qry" e ".via".
void openFiles(char *bed, char *geoName, char *qryName, char *mapName) {
    char *geoPath = catPath(bed, geoName);

    if (!openGeo(geoPath)) {
        free(geoPath);
        return;
    }

    char *qryPath = catPath(bed, qryName);
    char *mapPath = catPath(bed, mapName);

    openMap(mapPath);
    openQry(qryPath);

    free(geoPath);
    free(qryPath);
    free(mapPath);
}

// Manipula os parâmetros da execução.
void readParameters(int argc, char *argv[]) {
    char *bed, *geoName = NULL, *bsd = NULL, *qryName, *mapName;

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
    if (!verify(bed, geoName, bsd, qryName, mapName))
        return;

    openFiles(bed, geoName, qryName, mapName);
    freeAll(bed, geoName, bsd, qryName, mapName);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Few arguments.\n\n");
        return 0;
    }

    readParameters(argc, argv);
    return 0;
}