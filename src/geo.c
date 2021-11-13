#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Lê os argumentos do arquivo ".geo".
void readGeoArguments(FILE *geoFile) {
    char command[50], cep[100], fill[50], stroke[50], thickness[50];
    double x, y, width, height;

    while (fscanf(geoFile, "%s", command) != EOF) {
        // Insere uma quadra.
        if (strcmp(command, "q") == 0) {
            fscanf(geoFile, "%s %lf %lf %lf %lf", cep, &x, &y, &width, &height);

            // if (*hashCityBlocks == NULL)
            //     *hashCityBlocks = createHash(nx);

            // insertBlock(tree, *hashCityBlocks, cep, strokeWidth, colorFill, colorStroke, x, y, w, h);
        }

        // Define aspectos visuais das quadras.
        if (strcmp(command, "cq") == 0)
            fscanf(geoFile, "%s %s %s", thickness, fill, stroke);
    }
}

// Abre o arquivo ".geo" e chama função de leitura de parâmetros.
void openGeo(char geoPath[]) {
    FILE *geoFile = fopen(geoPath, "r");

    if (geoFile == NULL) {
        printf("Geo file not found.\n\n");
        return;
    }

    readGeoArguments(geoFile);
    fclose(geoFile);
}