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
    /* As remoções abaixo são testes pra ver como a árvore se comporta quando os elementos
     * são removidos.
     * A remoção não tá dando problema na hora de produzir o SVG, mas o TreeSize fica negativo.
     * Mostra que tem 10 nós na árvore, e tá certo, tem 10 listas. Porém, quando se remove um
     * retângulo da árvore (que está armazenado em uma lista) o TreeSize diminui como se uma
     * lista tivesse sido removida. Com essa lógica, se restasse só um retângulo na árvore, o
     * TreeSize ficaria -89.
     * Tem que arrumar a forma como o TreeSize é decrementado. Acredito que isso não vá
     * interferir no funcionamento do projeto, mas é bom deixar certinho.
     * 
     * Estou estudando a forma como você implementou a árvore pra saber a melhor forma de remover
     * os retângulos que estiverem dentro da área do "catac".
     */
    
    Block a = treeSearch(tree, 905, 95);
    destroyBlock(a);

    treeRemove(tree, 905, 95);

    a = treeSearch(tree, 905, 190);
    destroyBlock(a);

    treeRemove(tree, 905, 190);

    a = treeSearch(tree, 905, 285);
    destroyBlock(a);

    treeRemove(tree, 905, 285);

    a = treeSearch(tree, 905, 380);
    destroyBlock(a);

    treeRemove(tree, 905, 380);

    a = treeSearch(tree, 905, 475);
    destroyBlock(a);

    treeRemove(tree, 905, 475);

    a = treeSearch(tree, 905, 570);
    destroyBlock(a);

    treeRemove(tree, 905, 570);

    a = treeSearch(tree, 905, 665);
    destroyBlock(a);

    treeRemove(tree, 905, 665);

    a = treeSearch(tree, 905, 855);
    destroyBlock(a);

    treeRemove(tree, 905, 855);

    a = treeSearch(tree, 905, 760);
    destroyBlock(a);

    treeRemove(tree, 905, 760);

    a = treeSearch(tree, 905, 950);
    destroyBlock(a);

    treeRemove(tree, 905, 950);

    a = treeSearch(tree, 770, 95);
    destroyBlock(a);

    treeRemove(tree, 770, 95);

    a = treeSearch(tree, 635, 95);
    destroyBlock(a);

    treeRemove(tree, 635, 95);

    a = treeSearch(tree, 500, 95);
    destroyBlock(a);

    treeRemove(tree, 500, 95);

    a = treeSearch(tree, 365, 95);
    destroyBlock(a);

    treeRemove(tree, 365, 95);

    a = treeSearch(tree, 230, 95);
    destroyBlock(a);

    treeRemove(tree, 230, 95);

    a = treeSearch(tree, 95, 95);
    destroyBlock(a);

    treeRemove(tree, 95, 95);
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