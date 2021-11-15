#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "block.h"
#include "geo.h"
#include "map.h"
#include "path.h"
#include "qry.h"
#include "svg.h"
#include "graph.h"
#include "tree.h"

/*
 * Desaloca memória alocada aos ponteiros.
 */
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

/*
 * Verifica se os parâmetros obrigatórios para a execução foram inseridos.
 *
 * Retorno: 0 = Parâmetros faltando. 1 = Nenhum parâmetro faltando.
 * Quando 0: Desaloca a memória alocada aos ponteiros usando "freeAll".
 * Quando 1: Continua a execução do programa.
 */
int verify(char *bed, char *geoName, char *bsd, char *qryName, char *mapName) {
    if ((geoName == NULL) || (bsd == NULL)) {
        freeAll(bed, geoName, bsd, qryName, mapName);
        return 0;
    }

    return 1;
}

// Chama as funções que fazem a leitura dos arquivos de entrada. Produz um SVG "original" do GEO.
void openFiles(Tree tree, char *bed, char *geoName, char *qryName, char *mapName, char *bsd) {
    char *geoPath = catPath(bed, geoName);

    if (!openGeo(tree, geoPath)) {
        free(geoPath);
        return;
    }

    char *svgPath = catPath(bsd, "NOME_DO_SVG.svg");

    FILE *svgFile = fopen(svgPath, "w");
    drawBlocks(tree, svgFile);

    Graph graph = createGraph();

    char *qryPath = catPath(bed, qryName);
    char *mapPath = catPath(bed, mapName);

    openMap(mapPath, graph);
    openQry(qryPath);

    free(geoPath);
    free(qryPath);
    free(mapPath);
    free(svgPath);
    fclose(svgFile);
}

// Manipula os parâmetros da execução. Todos os ponteiros são alocados nessa função.
void readParameters(Tree tree, int argc, char *argv[]) {
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

    // Verifica se os parâmetros obrigatórios foram preenchidos.
    if (!verify(bed, geoName, bsd, qryName, mapName))
        return;

    openFiles(tree, bed, geoName, qryName, mapName, bsd);
    freeAll(bed, geoName, bsd, qryName, mapName);
}

int main(int argc, char *argv[]) {
    if (argc == 1)
        return 0;

    Tree tree = treeCreate("Quadras");

    readParameters(tree, argc, argv);

    blockDeleteAll(getTreeRoot(tree));
    treeEnd(tree);

    return 0;
}