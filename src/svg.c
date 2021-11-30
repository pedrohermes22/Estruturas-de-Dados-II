#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "block.h"
#include "graph.h"
#include "tree.h"

// Abre a tag <svg>.
void openSvg(FILE *svgFile) {
    if (svgFile == NULL) return;
    fprintf(svgFile, "<svg>\n");
}

// Fecha a tag <svg>.
void closeSvg(FILE *svgFile) {
    if (svgFile == NULL) return;
    fprintf(svgFile, "</svg>");
}

// Desenha as quadras recursivamente.
void recursiveDrawBlocks(FILE *svgFile, Node root) {
    if (root == NULL) return;

    recursiveDrawBlocks(svgFile, getTreeLeft(root));

    List list = getTreeNodeItens(root);

    for (NodeL nodeAux = getListFirst(list); nodeAux;
         nodeAux = getListNext(nodeAux)) {
        Block block = getTreeListItem(getListInfo(nodeAux));

        fprintf(svgFile,
                "\t<rect id=\"%s\" x=\"%lf\" y=\"%lf\" width=\"%lf\" "
                "height=\"%lf\" stroke=\"%s\" fill=\"%s\"/>\n",
                getBlockCep(block), getBlockX(block), getBlockY(block),
                getBlockWidth(block), getBlockHeight(block),
                getBlockStroke(block), getBlockFill(block));
    }

    recursiveDrawBlocks(svgFile, getTreeRight(root));
}

// Desenha as quadras.
void drawBlocks(Tree tree, FILE *svgFile) {
    if ((tree == NULL) || (svgFile == NULL)) return;

    Node root = getTreeRoot(tree);
    recursiveDrawBlocks(svgFile, root);
}

// Desenha círculos.
void drawCircle(FILE *svgFile, double x, double y, double r, char *fill) {
    if (svgFile == NULL) return;

    fprintf(svgFile,
            "\t<circle cx='%lf' cy='%lf' r='%lf' fill='%s' stroke-width='2'/>\n",
            x, y, r, fill);
}

// Desenha os pontos do grafo.
void drawDots(Graph graph, FILE *svgFile) {
    if ((graph == NULL) || (svgFile == NULL)) return;

    AdjList adjList = getAdjList(graph);

    for (NodeL nodeAux = getListFirst(adjList); nodeAux; nodeAux = getListNext(nodeAux)) {
        AdjList vertexAux = getListInfo(nodeAux);

        double x = getVertexX(vertexAux);
        double y = getVertexY(vertexAux);

        fprintf(svgFile,
                "\t<circle cx='%lf' cy='%lf' r='5' fill='red'/>\n",
                x - 2, y - 1);
    }
}

// Insere as linhas do TXT temporário no SVG.
void insertTempTxt(FILE *tempTxt, FILE *svgFile) {
    if (tempTxt == NULL) return;

    char line[200];

    while (fgets(line, sizeof(line), tempTxt) != NULL)
        fprintf(svgFile, "%s", line);

    fclose(tempTxt);
}