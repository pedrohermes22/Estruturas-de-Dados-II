#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "block.h"
#include "hashtable.h"
#include "list.h"
#include "text.h"
#include "tree.h"
#include "utils.h"

// Executa comando "@o?".
void oCommand(HashTable hash, char *cep, char face, int number) {
    if (hash == NULL) return;

    Block block = hashTableSearch(hash, cep);  // Recupera a quadra cujo a chave é "cep".

    if (block == NULL) return;

    double x = getXCoordinate(face, number, block);
    double y = getYCoordinate(face, number, block);
    char line[200];

    // Imprime a linha vertical.
    sprintf(line,
            "\t<line x1='%lf' y1='%lf' x2='%lf' y2='-10' stroke-width='5' stroke='red'/>\n",
            x, y, x);
    writeTxt(getTempTxt(), line);  // Escreve o código no TXT temporário.

    // Escreve o CEP da quadra no topo da linha.
    sprintf(line,
            "\t<text x='%lf' y='-10' font-size='12' font-weight='bold' fill='black'>%s</text>\n",
            x + 5, cep);
    writeTxt(getTempTxt(), line);  // Escreve o código no TXT temporário.
}

// Função recursiva do "catac".
void recursiveCatac(Tree tree, Node root, HashTable hash, double x, double y, double width, double height) {
    if (root == NULL) return;

    List list = getTreeNodeItens(root);  // Lista com as quadras.
    NodeL pointer = getListFirst(list);  // Ponteiro dos nós da lista.

    // Varre todas as posições da lista.
    while (pointer != NULL) {
        Block block = getTreeListItem(getListInfo(pointer));

        double xB = getBlockX(block);
        double yB = getBlockY(block);
        double x2B = xB + getBlockWidth(block);
        double y2B = yB + getBlockHeight(block);

        pointer = getListNext(pointer);  // Próximo nó da lista.

        // Se a quadra estiver inteiramente contida no retângulo do catac.
        if ((xB > x) && (yB > y) && (x2B < (x + width)) && (y2B < (y + height))) {
            char message[200];

            sprintf(message, "Quadra '%s' removida.\n", getBlockCep(block));
            writeTxt(getOutTxt(), message);

            destroyBlock(block);
            treeRemove(tree, xB, yB);
            hashTableRemove(hash, getBlockCep(block));
        }
    }

    recursiveCatac(tree, getTreeRight(root), hash, x, y, width, height);  // Executa função para o nó direito.
    recursiveCatac(tree, getTreeLeft(root), hash, x, y, width, height);   // Executa função para o nó esquerdo.
}

// Executa comando "catac".
void catacCommand(Tree tree, HashTable hash, double x, double y, double width, double height) {
    char rect[200];

    // Desenha o retângulo com a área do catac.
    sprintf(rect,
            "\t<rect x='%lf' y='%lf' width='%lf' height='%lf' fill='#AB37C8' stroke='#AA0044' stroke-width='3' stroke-dasharray='2' fill-opacity='0.5'/>\n",
            x, y, width, height);
    writeTxt(getTempTxt(), rect);

    recursiveCatac(tree, getTreeRoot(tree), hash, x, y, width, height);  // Chama função recursiva do catac.
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

// Lê os argumentos do arquivo QRY e executa os comandos.
void readQryArguments(Tree tree, HashTable hash, FILE *qryFile) {
    char line[200], trash[10], message[250], limiar[100];  // << Corrigir o "limiar".
    char cep[100], face, shortest[50], fastest[50];
    int number;
    double x, y, width, height, factor;

    while (fgets(line, sizeof(line), qryFile) != NULL) {
        if (strncmp(line, "@o? ", 4) == 0) {
            sscanf(line, "%s %s %c %d", trash, cep, &face, &number);
            oCommand(hash, cep, face, number);
        }

        if (strncmp(line, "catac ", 6) == 0) {
            sprintf(message, ">> COMANDO: %s\n", line);
            writeTxt(getOutTxt(), message);

            sscanf(line, "%s %lf %lf %lf %lf", trash, &x, &y, &width, &height);
            catacCommand(tree, hash, x, y, width, height);
        }

        if (strncmp(line, "rv ", 3) == 0) {
            sscanf(line, "%s %lf %lf %lf %lf %lf", trash, &x, &y, &width, &height, &factor);
        }

        if (strncmp(line, "cx ", 3) == 0) {
            sscanf(line, "%s %s", trash, limiar);
        }

        if (strncmp(line, "p? ", 3) == 0) {
            sscanf(line, "%s %s %c %d %s %s", trash, cep, &face, &number, shortest, fastest);
        }
    }
}

// Abre o arquivo QRY e chama função de leitura de parâmetros.
void openQry(Tree tree, HashTable hash, char *qryPath) {
    FILE *qryFile = fopen(qryPath, "r");

    if (qryFile == NULL) return;

    readQryArguments(tree, hash, qryFile);
    fclose(qryFile);
}