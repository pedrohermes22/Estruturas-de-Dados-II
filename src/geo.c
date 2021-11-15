#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "block.h"
#include "tree.h"

// Lê os argumentos do arquivo ".geo".
void readGeoArguments(Tree *tree, FILE *geoFile) {
    char trash[10], line[200];
    char cep[100], fill[50], stroke[50], thickness[50];
    double x, y, width, height;

    while (fgets(line, sizeof(line), geoFile) != NULL) {
        // Insere uma quadra.
        if (strncmp(line, "q ", 2) == 0) {
            sscanf(line, "%s %s %lf %lf %lf %lf", trash, cep, &x, &y, &width, &height);

            treeInsert(tree, createBlock(x, y, width, height, cep, fill, stroke, thickness), x, y, width);
        }

        // Define aspectos visuais das quadras.
        if (strncmp(line, "cq ", 3) == 0)
            sscanf(line, "%s %s %s %s", trash, thickness, fill, stroke);
    }
}

// Abre o arquivo ".geo" e chama função de leitura de parâmetros.
int openGeo(Tree *tree, char geoPath[]) {
    FILE *geoFile = fopen(geoPath, "r");

    if (geoFile == NULL) {
        printf("Geo file not found.\n\n");
        return 0;
    }

    readGeoArguments(tree, geoFile);
    fclose(geoFile);

    return 1;
}