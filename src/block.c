#include "block.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

// Estrutura da quadra
typedef struct blockStruct {
    double x;
    double y;
    double width;
    double height;

    char cep[100];
    char fill[50];
    char stroke[50];
    char thickness[50];
} BlockStruct;

// Cria a quadra
Block createBlock(double x, double y, double width, double height, char* cep, char* fill, char* stroke, char* thickness) {
    BlockStruct* new = (BlockStruct*)malloc(sizeof(BlockStruct));

    new->x = x;
    new->y = y;
    new->width = width;
    new->height = height;

    strcpy(new->cep, cep);
    strcpy(new->fill, fill);
    strcpy(new->stroke, stroke);
    strcpy(new->thickness, thickness);

    return new;
}

// Destrói a quadra
int destroyBlock(Block block) {
    BlockStruct* blockAux = (BlockStruct*)block;

    if (blockAux == NULL) {
        return 0;
    }

    free(blockAux);
    return 1;
}

// Percorre uma estrutura de árvore e vai deletando todas as quadras das listas
void blockDeleteAll(Node root){
    if(root == NULL){
        return;
    }

    blockDeleteAll(getTreeRight(root));
    blockDeleteAll(getTreeLeft(root));

    List* list = getTreeNodeItens(root);

    if(list == NULL){
        return;
    }

    for(NodeL* nodeAux = getListFirst(list); nodeAux; nodeAux = getListNext(nodeAux)){
        Info block = getTreeListItem(getListInfo(nodeAux));
        
        destroyBlock(block);
    }
}

// Pega o X da quadra
double getBlockX(Block block) {
    BlockStruct* blockAux = (BlockStruct*)block;

    return blockAux->x;
}

// Pega o Y da quadra
double getBlockY(Block block) {
    BlockStruct* blockAux = (BlockStruct*)block;

    return blockAux->y;
}

// Pega a largura da quadra
double getBlockWidth(Block block) {
    BlockStruct* blockAux = (BlockStruct*)block;

    return blockAux->width;
}

// Pega a altura da quadra
double getBlockHeight(Block block) {
    BlockStruct* blockAux = (BlockStruct*)block;

    return blockAux->height;
}

// Pega o Cep da quadra
char* getBlockCep(Block block) {
    BlockStruct* blockAux = (BlockStruct*)block;

    return blockAux->cep;
}

// Pega a cor de preenchimento da quadra
char* getBlockFill(Block block) {
    BlockStruct* blockAux = (BlockStruct*)block;

    return blockAux->fill;
}

// Pega a cor da borda da quadra
char* getBlockStroke(Block block) {
    BlockStruct* blockAux = (BlockStruct*)block;

    return blockAux->stroke;
}

// Pega a espessura da borda
char* getBlockThickness(Block block) {
    BlockStruct* blockAux = (BlockStruct*)block;

    return blockAux->thickness;
}