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
#include "union-find.h"

typedef struct r {
    char cep[100];
    char face;
    int number;
    double x, y;
} Register_R;

char color[][25]= {"pink", "blue", "red", "brown", "royalblue", "orange", "salmon", "yellow", "seagreen", "gray", "sienna", "skyblue", "slateblue", "slategray", "slategrey", "snow", "springgreen", "steelblue", "tan", "thistle", "tomato", "turquoise", "violet", "wheat", "whitesmoke"};

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
    char rect[200];

    // Desenha o retângulo com a área do rv.
    sprintf(rect,
            "\t<rect x='%lf' y='%lf' width='%lf' height='%lf' fill='none' stroke='#AA0044' stroke-width='5' stroke-dasharray='2' fill-opacity='0.5'/>\n",
            x, y, width, height);
    writeTxt(getTempTxt(), rect);

    Graph area = areaVertices(graph, x, y, width, height);
    List uf = kruskal(area);

    Graph gr = getListInfo(getListFirst(uf));
    
    List adj = getAdjList(gr);
    AdjList adjAux = getListInfo(getListFirst(adj));

    drawKruskal(gr, getTempTxt());

    drawCircle(getTempTxt(), getVertexX(adjAux), getVertexY(adjAux), 10, "green");

    HashTable visit = hashTableCreate(getAmountVertex(gr));

    convertDigraphForGraph(gr);

    dfs(graph, gr, adjAux, 0, factor, factor, visit);

    for(NodeL nodeAux = getListFirst(getAdjList(gr)); nodeAux; nodeAux = getListNext(nodeAux)){
        AdjList adj = getListInfo(nodeAux);

        for(NodeL nodeAux2 = getListFirst(getEdgeList(adj)); nodeAux2; nodeAux2 = getListNext(nodeAux2)){
            Edge edge = getListInfo(nodeAux2);
            fprintf(getOutTxt(),"\tAresta: Nome: %s Origem: %s Destino: %s Velocidade: %.2lf Tamanho: %.2lf Cep a Direita: %s Cep a Esquerda: %s \n", getEdgeName(edge), getEdgeOrigin(edge), getEdgeDestiny(edge), getEdgeSpeed(edge), getEdgeSize(edge), getEdgeRightCep(edge), getEdgeLeftCep(edge));
        }
    }


    for(NodeL nodeAux = getListFirst(uf); nodeAux; nodeAux = getListNext(nodeAux)){
        destroyGraph(getListInfo(nodeAux));
    }
    endList(uf);
    hashTableEnd(visit);
    destroyGraph(area);
}

// Executa comando "cx".
void cxCommand(Graph graph, double limiar) {

    List edges = createListEdge(graph);
    sorting(edges, 0, (getListSize(edges) - 1));

    List uf = createUFind(graph);

    for(NodeL nodeAux = getListFirst(edges); nodeAux; nodeAux = getListNext(nodeAux)){
        Edge edge = getListInfo(nodeAux);
        UFUnion(uf, edge);
    }

    for(NodeL nodeAux = getListFirst(uf); nodeAux; nodeAux = getListNext(nodeAux)){
        Graph gr = getListInfo(nodeAux);

        int index = getListIndexOf(nodeAux);

        fprintf(getOutTxt(), "Região: %d\n", getListIndexOf(nodeAux));

        for(NodeL nodeAux2 = getListFirst(getAdjList(gr)); nodeAux2; nodeAux2 = getListNext(nodeAux2)){
            AdjList adj = getListInfo(nodeAux2);

            fprintf(getOutTxt(), "\t Vértice: %s\n", getVertexId(adj));
        }

        drawCxCommand(gr, getTempTxt(), color[index%25]);
    }

    for(NodeL nodeAux = getListFirst(edges); nodeAux; nodeAux = getListNext(nodeAux)){
        Edge edge = getListInfo(nodeAux);
        if(getEdgeSpeed(edge) < limiar){
            setEdgeValid(edge, 0);
            AdjList originAdj = searchVertex(graph, getEdgeOrigin(edge));
            AdjList destinyAdj = searchVertex(graph, getEdgeDestiny(edge));
            fprintf(getTempTxt(), "\t<line x1='%lf' y1='%lf' x2='%lf' y2='%lf' style='stroke:red;stroke-width:6' />\n", getVertexX(originAdj), getVertexY(originAdj), getVertexX(destinyAdj), getVertexY(destinyAdj));
        }
    }

    endList(edges);
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

    fprintf(getOutTxt(), "Caminho rapido:\n");
    if(getListSize(speed) > 1){
        for (NodeL nodeAux = getListFirst(speed); getListNext(nodeAux); nodeAux = getListNext(nodeAux)) {
            AdjList aux = getListInfo(nodeAux);
            AdjList aux2 = getListInfo(getListNext(nodeAux));

            Edge edge = searchEdge(aux2, getVertexId(aux));

            fprintf(getOutTxt(), "\tAresta Origem: %s Aresta Destino: %s Endereco: %s Tamanho: %.2lf Velocidade: %.2lf \n", getVertexId(aux), getVertexId(aux2), getEdgeName(edge), getEdgeSize(edge), getEdgeSpeed(edge));

            fprintf(getTempTxt(), "\t<line x1='%lf' y1='%lf' x2='%lf' y2='%lf' style='stroke:%s;stroke-width:5' />\n", getVertexX(aux), getVertexY(aux), getVertexX(aux2), getVertexY(aux2), fastest);
        }
    }

    fprintf(getOutTxt(), "Caminho curto:\n");
    if(getListSize(size) > 1){
        for (NodeL nodeAux = getListFirst(size); getListNext(nodeAux); nodeAux = getListNext(nodeAux)) {
            AdjList aux = getListInfo(nodeAux);
            AdjList aux2 = getListInfo(getListNext(nodeAux));

            Edge edge = searchEdge(aux2, getVertexId(aux));

            fprintf(getOutTxt(), "\tAresta Origem: %s Aresta Destino: %s Endereco: %s Tamanho: %.2lf Velocidade: %.2lf\n", getVertexId(aux), getVertexId(aux2), getEdgeName(edge), getEdgeSize(edge), getEdgeSpeed(edge));

            fprintf(getTempTxt(), "\t<line x1='%lf' y1='%lf' x2='%lf' y2='%lf' style='stroke:%s;stroke-width:5' />\n", getVertexX(aux) - 10, getVertexY(aux) - 10, getVertexX(aux2) - 10, getVertexY(aux2) - 10, shortest);
        }
    }

    if (getListSize(size) == 0) {
        fprintf(getTempTxt(), "\t<line x1='%lf' y1='%lf' x2='%lf' y2='%lf' style='stroke:%s;stroke-width:5;stroke-dasharray:4' />\n", x, y, r.x, r.y, "red");
        fprintf(getOutTxt(), "Destino inacessível\n");
    }

    endList(speed);
    endList(size);
}

// Lê os argumentos do arquivo QRY e executa os comandos.
void readQryArguments(Tree tree, HashTable hash, Graph graph, FILE *qryFile) {
    char line[200], trash[10], message[250];
    char cep[100], face, shortest[50], fastest[50];
    int number;
    double x, y, width, height, factor, limiar;
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
            sprintf(message, ">> COMANDO: %s\n", line);
            writeTxt(getOutTxt(), message);
            sscanf(line, "%s %lf %lf %lf %lf %lf", trash, &x, &y, &width, &height, &factor);
            rvCommand(graph, x, y, width, height, factor);
        }

        if (strncmp(line, "cx ", 3) == 0) {
            sprintf(message, ">> COMANDO: %s\n", line);
            writeTxt(getOutTxt(), message);
            sscanf(line, "%s %lf", trash, &limiar);
            cxCommand(graph, limiar);
        }

        if (strncmp(line, "p? ", 3) == 0) {
            sprintf(message, ">> COMANDO: %s\n", line);
            writeTxt(getOutTxt(), message);

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