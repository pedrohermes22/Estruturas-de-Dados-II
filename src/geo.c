#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "block.h"
#include "hashtable.h"
#include "tree.h"

// Lê os argumentos do arquivo ".geo".
void readGeoArguments(Tree tree, HashTable *hash, FILE *geoFile) {
    char trash[10], line[200];
    char cep[100], fill[50], stroke[50], thickness[50];
    double x, y, width, height;
    int nx;

    while (fgets(line, sizeof(line), geoFile) != NULL) {
        if (strncmp(line, "nx ", 3) == 0) {  // Cria a hash table com tamanho nx.
            sscanf(line, "%s %d", trash, &nx);

            if (*hash == NULL) *hash = hashTableCreate(nx);
        }

        if (strncmp(line, "q ", 2) == 0) {  // Insere uma quadra.
            sscanf(line, "%s %s %lf %lf %lf %lf", trash, cep, &x, &y, &width, &height);

            Block block = createBlock(x, y, width, height, cep, fill, stroke, thickness);
            treeInsert(tree, block, x, y, width);
            hashTableInsert(*hash, cep, block);
        }

        if (strncmp(line, "cq ", 3) == 0)  // Define aspectos visuais das quadras.
            sscanf(line, "%s %s %s %s", trash, thickness, fill, stroke);
    }
}

// Abre o arquivo GEO e chama função de leitura de parâmetros.
int openGeo(Tree tree, HashTable *hash, char *geoPath) {
    FILE *geoFile = fopen(geoPath, "r");

    if (geoFile == NULL) return 0;

    readGeoArguments(tree, hash, geoFile);
    fclose(geoFile);

    return 1;
}