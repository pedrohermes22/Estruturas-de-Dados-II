#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "block.h"
#include "geo.h"
#include "graph.h"
#include "hashtable.h"
#include "map.h"
#include "path.h"
#include "qry.h"
#include "svg.h"
#include "text.h"
#include "tree.h"
#include "utils.h"

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

// Executa comandos referentes ao ".geo".
int geoCommands(Tree tree, HashTable *hash, FILE *svgFile, char *bed, char *bsd, char *geoName) {
    char *geoPath = catPath(bed, geoName);
    char *originalSvgPath = getSvgPath(bsd, geoName);

    if (!openGeo(tree, hash, geoPath)) {
        free(geoPath);
        return 0;
    }

    FILE *originalSvg = fopen(originalSvgPath, "w");
    openSvg(originalSvg);
    drawBlocks(tree, originalSvg);
    closeSvg(originalSvg);

    openSvg(svgFile);
    drawBlocks(tree, svgFile);

    free(originalSvgPath);
    free(geoPath);
    fclose(originalSvg);

    return 1;
}

// Executa comandos referentes ao ".via".
void mapCommands(Graph graph, FILE *svgFile, char *bed, char *bsd, char *mapName) {
    char *mapPath = catPath(bed, mapName);

    openMap(mapPath, graph, svgFile);
    free(mapPath);
}

// Executa os comandos do QRY.
void qryCommands(Tree tree, HashTable hash, Graph graph, char *bed, char *bsd, char *qryName) {
    char *qName = extractName(qryName);        // Nome do QRY.
    char *qryPath = catPath(bed, qryName);     // Diretório do QRY.
    char *svgPath = getSvgPath(bsd, qryName);  // Diretório do SVG.
    char dir[200];                             // Diretório do TXT temporário.
    FILE *svgFile = fopen(svgPath, "w");       // Ponteiro do SVG.

    sprintf(dir, "%s/TEMP_TXT.txt", bsd);  // Recebe o diretório do TXT temporário.

    // == Abertura de arquivos ==
    openTempTxt(bsd);
    openOutTxt(bsd, qName);
    openSvg(svgFile);
    // printf("%p\n", hash);
    openQry(tree, hash, graph, qryPath);
    // == Fim da abertura de arquivos ==

    drawBlocks(tree, svgFile);
    drawDots(graph, svgFile);
    closeTxt(getTempTxt());  // Fecha o TXT temporário.
    closeTxt(getOutTxt());   // Fecha o TXT de saída.
    insertTempTxt(fopen(dir, "r"), svgFile);
    closeSvg(svgFile);
    remove(dir);

    free(qName);
    free(qryPath);
    free(svgPath);
    fclose(svgFile);
}

// Manipula os parâmetros da execução.
void readParameters(Tree tree, int argc, char *argv[]) {
    char *bed = NULL, *geoName = NULL, *bsd = NULL, *qryName = NULL, *mapName = NULL;
    Graph graph = createGraph();
    HashTable hash = NULL;

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

    // Cria um SVG que receberá as informações gráficas do GEO, VIA e QRY.
    char *svgPath = getSvgPath(bsd, geoName);
    FILE *svgFile = fopen(svgPath, "w");

    if (!geoCommands(tree, &hash, svgFile, bed, bsd, geoName)) return;
    if (mapName != NULL) mapCommands(graph, svgFile, bed, bsd, mapName);
    if (qryName != NULL) qryCommands(tree, hash, graph, bed, bsd, qryName);

    // Fecha o SVG aberto anteriormente.
    closeSvg(svgFile);
    fclose(svgFile);

    freeAll(bed, geoName, bsd, qryName, mapName);
    free(svgPath);
    destroyGraph(graph);
    hashTableEnd(hash);
}

int main(int argc, char *argv[]) {
    if (argc == 1) return 0;

    Tree tree = treeCreate("Quadras");

    readParameters(tree, argc, argv);
    blockDeleteAll(getTreeRoot(tree));
    treeEnd(tree);

    return 0;
}