#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "block.h"
#include "dijkstra.h"
#include "graph.h"
#include "hashtable.h"
#include "kruskal.h"
#include "list.h"
#include "svg.h"
#include "text.h"
#include "tree.h"
#include "utils.h"

typedef struct r {
    char cep[100];
    char face;
    int number;
    double x, y;
} Register_R;

// Executa comando "@o?".
void oCommand(Register_R *r, HashTable hash, char *cep, char face, int number) {
    if (hash == NULL) return;

    Block block = hashTableSearch(hash, cep);  // Recupera a quadra cujo a chave é "cep".

    if (block == NULL) return;

    double x = getXCoordinate(face, number, block);
    double y = getYCoordinate(face, number, block);
    char line[200];

    strcpy(r->cep, cep);
    r->face = face;
    r->number = number;
    r->x = x;
    r->y = y;

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
            char *cep = getBlockCep(block);

            sprintf(message, "Quadra '%s' removida.\n", cep);
            writeTxt(getOutTxt(), message);

            treeRemove(tree, xB, yB);
            hashTableRemove(hash, cep);
            destroyBlock(block);
        }
    }

    recursiveCatac(tree, getTreeRight(root), hash, x, y, width, height);  // Executa função para o nó direito.
    recursiveCatac(tree, getTreeLeft(root), hash, x, y, width, height);   // Executa função para o nó esquerdo.
}

// Executa comando "catac".
void catacCommand(Tree tree, HashTable hash, Graph graph, double x, double y, double width, double height) {
    char rect[200];

    // Desenha o retângulo com a área do catac.
    sprintf(rect,
            "\t<rect x='%lf' y='%lf' width='%lf' height='%lf' fill='#AB37C8' stroke='#AA0044' stroke-width='3' stroke-dasharray='2' fill-opacity='0.5'/>\n",
            x, y, width, height);
    writeTxt(getTempTxt(), rect);                                        // Insere "rect" no TXT temporário.
    recursiveCatac(tree, getTreeRoot(tree), hash, x, y, width, height);  // Deleta as quadras.

    // deleteVertexGraph(graph, "(b0|2,6)");
    AdjList adjList = getAdjList(graph);
    List listAux = createList();  // Lista com os pontos internos.

    for (NodeL nodeAux = getListFirst(adjList); nodeAux; nodeAux = getListNext(nodeAux)) {
        AdjList vertexAux = getListInfo(nodeAux);

        double xAux = getVertexX(vertexAux);
        double yAux = getVertexY(vertexAux);

        if (((x < xAux) && ((x + width) > xAux)) && ((y < yAux) && ((y + height) > yAux)))
            insertListElement(listAux, getVertexId(vertexAux));
    }

    for (NodeL nodeAux = getListFirst(listAux); nodeAux; nodeAux = getListNext(nodeAux)) {
        char *vertexId = getListInfo(nodeAux);
        deleteVertexGraph(graph, vertexId);
    }

    endList(listAux);
}

// Executa comando "rv".
void rvCommand(Graph graph, double x, double y, double width, double height, double factor) {
    if (graph == NULL) return;

    Graph area = areaVertices(graph, x, y, width, height);
    kruskal(area);

    destroyGraph(area);
}

// Executa comando "cx".
void cxCommand(char *limiar) {
}

// Executa comando "p?".
void pCommand(Register_R r, Graph graph, HashTable hash, char *cep, char face, int number, char *shortest, char *fastest) {
    Block block = hashTableSearch(hash, cep);  // Recupera a quadra cujo a chave é "cep".

    if (block == NULL) return;

    double x = getXCoordinate(face, number, block);
    double y = getYCoordinate(face, number, block);

    AdjList vertexP = getClosestVertex(graph, x, y);

    AdjList vertexR = getClosestVertex(graph, r.x, r.y);

    List speed = dijkstraSpeed(graph, vertexR, vertexP);

    List size = dijkstraSize(graph, vertexR, vertexP);

    for (NodeL nodeAux = getListFirst(speed); nodeAux; nodeAux = getListNext(nodeAux)) {
        AdjList aux = getListInfo(nodeAux);

        drawCircle(getTempTxt(), getVertexX(aux), getVertexY(aux), 10, "pink");

    }

    for (NodeL nodeAux = getListFirst(size); nodeAux; nodeAux = getListNext(nodeAux)) {
        AdjList aux = getListInfo(nodeAux);

        drawCircle(getTempTxt(), getVertexX(aux), getVertexY(aux), 10, "blue");
    }

    endList(speed);
    endList(size);
}

// Lê os argumentos do arquivo QRY e executa os comandos.
void readQryArguments(Tree tree, HashTable hash, Graph graph, FILE *qryFile) {
    char line[200], trash[10], message[250], limiar[100];  // << Corrigir o "limiar".
    char cep[100], face, shortest[50], fastest[50];
    int number;
    double x, y, width, height, factor;
    Register_R r;  // Armazena o ponto informado pelo comando "@o?".

    while (fgets(line, sizeof(line), qryFile) != NULL) {
        if (strncmp(line, "@o? ", 4) == 0) {
            sscanf(line, "%s %s %c %d", trash, cep, &face, &number);
            oCommand(&r, hash, cep, face, number);
        }

        if (strncmp(line, "catac ", 6) == 0) {
            sprintf(message, ">> COMANDO: %s\n", line);
            writeTxt(getOutTxt(), message);

            sscanf(line, "%s %lf %lf %lf %lf", trash, &x, &y, &width, &height);
            catacCommand(tree, hash, graph, x, y, width, height);
        }

        if (strncmp(line, "rv ", 3) == 0) {
            sscanf(line, "%s %lf %lf %lf %lf %lf", trash, &x, &y, &width, &height, &factor);
            rvCommand(graph, x, y, width, height, factor);
        }

        if (strncmp(line, "cx ", 3) == 0) {
            sscanf(line, "%s %s", trash, limiar);
        }

        if (strncmp(line, "p? ", 3) == 0) {
            sscanf(line, "%s %s %c %d %s %s", trash, cep, &face, &number, shortest, fastest);
            pCommand(r, graph, hash, cep, face, number, shortest, fastest);
        }
    }
}

// Abre o arquivo QRY e chama função de leitura de parâmetros.
void openQry(Tree tree, HashTable hash, Graph graph, char *qryPath) {
    FILE *qryFile = fopen(qryPath, "r");

    if (qryFile == NULL) return;

    readQryArguments(tree, hash, graph, qryFile);
    fclose(qryFile);
}