#include <stdio.h>

#include "graph.h"

// Retorna o subgrafo com os vértices que estão dentro da região especificada.
Graph areaVertices(Graph graph, double x, double y, double width, double height) {
    if (graph == NULL) return;

    Graph final = createGraph();  // Retorno da função.
    AdjList adjList = getAdjList(graph);

    for (NodeL nodeAux = getListFirst(adjList); nodeAux; nodeAux = getListNext(nodeAux)) {
        AdjList vertexAux = getListInfo(nodeAux);

        double xAux = getVertexX(vertexAux);
        double yAux = getVertexY(vertexAux);

        if (((x < xAux) && ((x + width) > xAux)) && ((y < yAux) && ((y + height) > yAux)))
            insertVertexGraph(final, getVertexId(vertexAux), xAux, yAux);
    }

    return final;
}

//
void kruskal(Graph graph) {
    if ((graph == NULL) || (getAmountVertex(graph) == 0)) return;

    
}