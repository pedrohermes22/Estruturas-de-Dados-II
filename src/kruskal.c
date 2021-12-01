#include <stdio.h>

#include "graph.h"
#include "svg.h"

typedef struct eNode {
    char edgeName[100];
    double size;  // Será usado como peso da aresta.
    struct lEdges *next, *previous;
} EdgeNode;

typedef struct eList {
    EdgeNode *first;
    int size;
} EdgesList;

EdgesList *createEdgesList() {
    EdgesList *eL = (EdgesList *)calloc(1, sizeof(EdgesList));

    eL->first = NULL;
    eL->size = 0;

    return eL;
}

void insertEdgesList(EdgesList *eList, char *edgeName, double size) {
    if (eList == NULL) return;

    // Insere primeiro elemento.
    if (eList->size == 0) {
        return;
    }
}

// Retorna o subgrafo com os vértices que estão dentro da região especificada.
Graph areaVertices(Graph graph, double x, double y, double width, double height) {
    if (graph == NULL) return NULL;

    Graph final = createGraph();  // Retorno da função.
    AdjList adjList = getAdjList(graph);

    for (NodeL nodeAux = getListFirst(adjList); nodeAux; nodeAux = getListNext(nodeAux)) {
        AdjList vertexAux = getListInfo(nodeAux);

        double xAux = getVertexX(vertexAux);
        double yAux = getVertexY(vertexAux);

        if (((x < xAux) && ((x + width) > xAux)) && ((y < yAux) && ((y + height) > yAux))) {
            insertVertexGraph(final, getVertexId(vertexAux), xAux, yAux);
            List edgeAux = getEdgeList(vertexAux);

            for (NodeL edgeNode = getListFirst(edgeAux); edgeNode; edgeNode = getListNext(edgeNode)) {
                Edge edge = getListInfo(edgeNode);
                insertEdgeGraph(final, "a", "b", "c", "d", getEdgeSize(edge), getEdgeSpeed(edge), "Qualquer coisa");
            }
        }
    }

    return final;
}

// void makeEdges(Graph graph) {
//     if (graph == NULL) return;

//     AdjList adjList = getAdjList(graph);

//     for (NodeL nodeAux = getListFirst(adjList); nodeAux; nodeAux = getListNext(nodeAux)) {
//         AdjList vertexAux = getListInfo(nodeAux);

//         double xAux = getVertexX(vertexAux);
//         double yAux = getVertexY(vertexAux);
//     }
// }

void kruskal(Graph graph) {
    if ((graph == NULL) || (getAmountVertex(graph) == 0)) return;

    printf("Vertices amount: %d\n\n", getAmountVertex(graph));

    FILE *svg = fopen("../graph.svg", "w");
    openSvg(svg);

    drawDots(graph, svg);

    closeSvg(svg);
    if (svg != NULL) fclose(svg);
}