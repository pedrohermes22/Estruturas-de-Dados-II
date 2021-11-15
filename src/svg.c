#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "block.h"
#include "tree.h"

// Desenha as quadras recursivamente.
void recursiveDrawBlocks(FILE *svgFile, Node root) {
    if (root == NULL)
        return;

    recursiveDrawBlocks(svgFile, getTreeLeft(root));

    List list = getTreeNodeItens(root);

    for (NodeL nodeAux = getListFirst(list); nodeAux; nodeAux = getListNext(nodeAux)) {
        Block block = getTreeListItem(getListInfo(nodeAux));

        fprintf(svgFile, "\t<rect id=\"%s\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\"/>\n",
                getBlockCep(block), getBlockX(block), getBlockY(block), getBlockWidth(block), getBlockHeight(block),
                getBlockStroke(block), getBlockFill(block));
    }

    recursiveDrawBlocks(svgFile, getTreeRight(root));
}

// Desenha as quadras armazenadas na árvore.
void drawBlocks(Tree tree, FILE *svgFile) {
    if ((tree == NULL) || (svgFile == NULL))
        return;

    Node root = getTreeRoot(tree);

    fprintf(svgFile, "<svg>\n");
    recursiveDrawBlocks(svgFile, root);
    fprintf(svgFile, "\n</svg>");
}