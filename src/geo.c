#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Lê os argumentos do arquivo ".geo".
void readGeoArguments(FILE *geoFile) {
    char trash[10], line[200];
    char cep[100], fill[50], stroke[50], thickness[50];
    double x, y, width, height;

    while (fgets(line, sizeof(line), geoFile) != NULL) {
        // Insere uma quadra.
        if (strncmp(line, "q ", 2) == 0)
            sscanf(line, "%s %s %lf %lf %lf %lf", trash, cep, &x, &y, &width, &height);

        // Define aspectos visuais das quadras.
        if (strncmp(line, "cq ", 3) == 0)
            sscanf(line, "%s %s %s %s", trash, thickness, fill, stroke);
    }
}

// Abre o arquivo ".geo" e chama função de leitura de parâmetros.
int openGeo(char geoPath[]) {
    FILE *geoFile = fopen(geoPath, "r");

    if (geoFile == NULL) {
        printf("Geo file not found.\n\n");
        return 0;
    }

    readGeoArguments(geoFile);
    fclose(geoFile);

    return 1;
}