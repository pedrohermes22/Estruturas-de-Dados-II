#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ponteiros para os parâmetros.
char *bed, *geoName, *bsd, *qryName, *mapName;

// Desaloca memória dos ponteiros.
void freeAll() {
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
    for (int i = 1; i < argc; i++) {
        // Diretório-base de entrada (BED).
        if (strcmp("-e", argv[i]) == 0) {
            bed = (char *)calloc((strlen(argv[++i])) + 1, sizeof(char));
            strcpy(bed, argv[i]);
        }

        // Arquivo com a descrição da cidade.
        if (strcmp("-f", argv[i]) == 0) {
            geoName = (char *)calloc((strlen(argv[++i])) + 1, sizeof(char));
            strcpy(geoName, argv[i]);
        }

        // Diretório-base de saída (BSD).
        if (strcmp("-o", argv[i]) == 0) {
            bsd = (char *)calloc((strlen(argv[++i])) + 1, sizeof(char));
            strcpy(bsd, argv[i]);
        }

        // Arquivo com consultas.
        if (strcmp("-q", argv[i]) == 0) {
            qryName = (char *)calloc((strlen(argv[++i])) + 1, sizeof(char));
            strcpy(qryName, argv[i]);
        }

        // Arquivo de vias (para construção do grafo).
        if (strcmp("-v", argv[i]) == 0) {
            mapName = (char *)calloc((strlen(argv[++i])) + 1, sizeof(char));
            strcpy(mapName, argv[i]);
        }
    }

    printf("BED = %s\n", bed);
    printf("GeoName = %s\n", geoName);
    printf("BSD = %s\n", bsd);
    printf("QryName = %s\n", qryName);
    printf("Map = %s\n\n", mapName);
    freeAll();
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Few arguments.\n\n");
        return 0;
    }

    readParameters(argc, argv);
    return 0;
}