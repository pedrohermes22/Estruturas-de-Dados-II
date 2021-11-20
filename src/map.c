#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "svg.h"

// Lê os argumentos do arquivo ".via".
void readMapArguments(FILE *mapFile, Graph graph, FILE *svgFile) {
    char command[50], line[200], trash[10];
    char id[100], name[100], cepRight[100], cepLeft[100], i[100], j[100];
    int vertex;
    double x, y, length, speed;

    while (fgets(line, sizeof(line), mapFile) != NULL) {
        // Comando "nv".
        if (strncmp(line, "nv ", 3) == 0) {
            sscanf(line, "%s %d", trash, &vertex);
        }

        // Comando "v".
        if (strncmp(line, "v ", 2) == 0) {
            sscanf(line, "%s %s %lf %lf", trash, id, &x, &y);
            drawCircle(svgFile, x - 2, y - 1, 4, "red");  // << Desenha os círculos.
            insertVertexGraph(graph, id, x, y);
        }

        // Comando "e".
        if (strncmp(line, "e ", 2) == 0) {
            sscanf(line, "%s %s %s %s %s %lf %lf %s", trash, i, j, cepRight, cepLeft, &length, &speed, name);
            insertEdgeGraph(graph, i, j, cepRight, cepLeft, length, speed, name);
        }
    }
}

// Abre o arquivo ".via" e chama função de leitura de parâmetros.
void openMap(char mapPath[], Graph graph, FILE *svgFile) {
    FILE *mapFile = fopen(mapPath, "r");

    if (mapFile == NULL) return;

    readMapArguments(mapFile, graph, svgFile);
    fclose(mapFile);
}