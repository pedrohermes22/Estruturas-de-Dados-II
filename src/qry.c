#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "block.h"
#include "list.h"
#include "text.h"
#include "tree.h"

// Executa comando "@o?".
void oCommand(char *cep, char face, int number) {
}

// Função recursiva do "catac".
void recursiveCatac(Tree tree, Node root, double x, double y, double width, double height) {
    treeRemove(tree, 905, 95);
    // if (root == NULL) return;

    // List list = getTreeNodeItens(root);
    // NodeL pointer = getListFirst(list);

    // while (pointer != NULL) {
    //     double xB = getBlockX(getListInfo(pointer));
    //     double yB = getBlockY(getListInfo(pointer));
    //     double x2B = xB + getBlockWidth(getListInfo(pointer));
    //     double y2B = yB + getBlockHeight(getListInfo(pointer));

    //     pointer = getListNext(pointer);

    //     if ((xB > x) && (yB > y) && (x2B < (x + width)) && (y2B < (y + height)))
    //         treeRemove(tree, xB, yB);
    // }

    // recursiveCatac(tree, getTreeRight(root), x, y, width, height);
    // recursiveCatac(tree, getTreeLeft(root), x, y, width, height);
}

// Executa comando "catac".
void catacCommand(Tree tree, double x, double y, double width, double height) {
    char rect[200];

    // Desenha o retângulo da área do CATAC.
    sprintf(rect,
            "\t<rect x='%lf' y='%lf' width='%lf' height='%lf' fill='#AB37C8' stroke='#AA0044' stroke-width='3' stroke-dasharray='2' fill-opacity='0.5'/>\n",
            x, y, width, height);
    writeTempTxt(rect);

    printf("Pre - Tree size: %d\n", getTreeSize(tree));
    recursiveCatac(tree, getTreeRoot(tree), x, y, width, height);
    printf("Pos - Tree size: %d\n", getTreeSize(tree));
}

// Executa comando "rv".
void rvCommand(double x, double y, double width, double height, double factor) {
}

// Executa comando "cx".
void cxCommand(char *limiar) {
}

// Executa comando "p?".
void pCommand(char *cep, char face, int number, char *shortest, char *fastest) {
}

// Lê os argumentos do arquivo ".qry".
void readQryArguments(FILE *qryFile, Tree tree) {
    char command[50], line[200], trash[10], limiar[100];  // << Corrigir o "limiar".
    char cep[100], face, shortest[50], fastest[50];
    int number;
    double x, y, width, height, factor;

    while (fgets(line, sizeof(line), qryFile) != NULL) {
        // Comando "@o?".
        if (strncmp(line, "@o? ", 4) == 0) {
            sscanf(line, "%s %s %c %d", trash, cep, &face, &number);
        }

        // Comando "catac".
        if (strncmp(line, "catac ", 6) == 0) {
            sscanf(line, "%s %lf %lf %lf %lf", trash, &x, &y, &width, &height);
            catacCommand(tree, x, y, width, height);
        }

        // Comando "rv".
        if (strncmp(line, "rv ", 3) == 0) {
            sscanf(line, "%s %lf %lf %lf %lf %lf", trash, &x, &y, &width, &height, &factor);
        }

        // Comando "cx".
        if (strncmp(line, "cx ", 3) == 0) {
            sscanf(line, "%s %s", trash, limiar);
        }

        // Comando "p?".
        if (strncmp(line, "p? ", 3) == 0) {
            sscanf(line, "%s %s %c %d %s %s", trash, cep, &face, &number, shortest, fastest);
        }
    }
}

// Abre o arquivo ".qry" e chama função de leitura de parâmetros.
void openQry(Tree tree, char *qryPath) {
    FILE *qryFile = fopen(qryPath, "r");

    if (qryFile == NULL)
        return;

    readQryArguments(qryFile, tree);
    fclose(qryFile);
}