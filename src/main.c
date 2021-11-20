#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "block.h"
#include "geo.h"
#include "graph.h"
#include "map.h"
#include "path.h"
#include "qry.h"
#include "svg.h"
#include "tree.h"

// Desaloca memória alocada aos ponteiros.
void freeAll(char *bed, char *geoName, char *bsd, char *qryName, char *mapName) {
    if (bed != NULL) free(bed);

    if (geoName != NULL) free(geoName);

    if (bsd != NULL) free(bsd);

    if (qryName != NULL) free(qryName);

    if (mapName != NULL) free(mapName);
}

/* Verifica se os parâmetros obrigatórios foram preenchidos. Caso não tenham
   sido, libera a memória alocada aos demais.*/
int verify(char *bed, char *geoName, char *bsd, char *qryName, char *mapName) {
    if ((geoName == NULL) || (bsd == NULL)) {
        freeAll(bed, geoName, bsd, qryName, mapName);
        return 0;
    }

    return 1;
}

/* Chama as funções que fazem a leitura dos arquivos de entrada. Produz um SVG
   "original" do GEO.*/
void openFiles(Tree tree, char *bed, char *geoName, char *qryName, char *mapName, char *bsd) {
    char *geoPath = catPath(bed, geoName);

    if (!openGeo(tree, geoPath)) {
        free(geoPath);
        return;
    }

    char *geoOnlyName = extractName(geoName);
    char *svgName = (char *)calloc(strlen(geoOnlyName) + 5, sizeof(char));
    sprintf(svgName, "%s.svg", geoOnlyName);
    char *svgPath = catPath(bsd, svgName);

    FILE *svgFile = fopen(svgPath, "w");
    openSvg(svgFile);
    drawBlocks(tree, svgFile);

    Graph graph = createGraph();

    if (mapName != NULL) {
        char *mapPath = catPath(bed, mapName);
        openMap(mapPath, graph, svgFile);
        closeSvg(svgFile);
        free(mapPath);
    }

    if (qryName != NULL) {
        char *qryPath = catPath(bed, qryName);
        openQry(qryPath);
        free(qryPath);
    }

    free(svgName);
    free(geoOnlyName);
    free(geoPath);
    free(svgPath);
    destroyGraph(graph);
    fclose(svgFile);
}

// Manipula os parâmetros da execução.
void readParameters(Tree tree, int argc, char *argv[]) {
    char *bed = NULL, *geoName = NULL, *bsd = NULL, *qryName = NULL, *mapName = NULL;

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

    // Verifica se os parâmetros obrigatórios foram preenchidos.
    if (!verify(bed, geoName, bsd, qryName, mapName)) return;

    openFiles(tree, bed, geoName, qryName, mapName, bsd);
    freeAll(bed, geoName, bsd, qryName, mapName);
}

int main(int argc, char *argv[]) {
    if (argc == 1) return 0;

    Tree tree = treeCreate("Quadras");

    readParameters(tree, argc, argv);

    blockDeleteAll(getTreeRoot(tree));
    treeEnd(tree);

    return 0;
}