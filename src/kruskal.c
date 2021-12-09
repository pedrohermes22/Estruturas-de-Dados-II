#include <stdio.h>
#include <string.h>

#include "graph.h"
#include "union-find.h"
#include "svg.h"

int sortingAux(List edges, int origin, int destiny){
    double p = getEdgeSize(getListInfo(getListLast(edges)));

    int pI = origin;

    for( int i = origin; i < destiny; i++){
        if(getEdgeSize(getListInfo(getListNodeByIndex(edges, i))) <= p){
            swapListInfo(getListNodeByIndex(edges, i), getListNodeByIndex(edges, pI));
            pI++;
        }
    }

    swapListInfo(getListNodeByIndex(edges, pI), getListNodeByIndex(edges, destiny));
    return pI;
}

void sorting(List edges, int origin, int destiny){
    if(origin >= destiny){
        return;
    }

    int p = sortingAux(edges, origin, destiny);

    sorting(edges, origin, p-1);
    sorting(edges, p+1, destiny);
}

// Retorna o subgrafo com os vértices que estão dentro da região especificada.
Graph areaVertices(Graph graph, double x, double y, double width, double height) {
    if (graph == NULL) return NULL;

    Graph final = createGraph();       // Retorno da função.
    List adjList = getAdjList(graph);  //

    for (NodeL nodeAux = getListFirst(adjList); nodeAux; nodeAux = getListNext(nodeAux)) {
        AdjList vertexAux = getListInfo(nodeAux);

        double xAux = getVertexX(vertexAux);
        double yAux = getVertexY(vertexAux);

        if (((x < xAux) && ((x + width) > xAux)) && ((y < yAux) && ((y + height) > yAux)))
            insertVertexGraph(final, getVertexId(vertexAux), xAux, yAux);
    }

    for (NodeL nodeAux = getListFirst(adjList); nodeAux; nodeAux = getListNext(nodeAux)) {
        AdjList vertexAux = getListInfo(nodeAux);

        double xAux = getVertexX(vertexAux);
        double yAux = getVertexY(vertexAux);

        if (((x < xAux) && ((x + width) > xAux)) && ((y < yAux) && ((y + height) > yAux))) {
            List edgeAux = getEdgeList(vertexAux);

            for (NodeL edgeNode = getListFirst(edgeAux); edgeNode; edgeNode = getListNext(edgeNode)) {
                Edge edge = getListInfo(edgeNode);
                insertEdgeGraph(final, getEdgeOrigin(edge), getEdgeDestiny(edge), getEdgeRightCep(edge), getEdgeLeftCep(edge), getEdgeSize(edge), getEdgeSpeed(edge),
                                getEdgeName(edge));
            }
        }
    }

    return final;
}

List createListEdge(Graph graph){
    List edges = createList();

    List adj = getAdjList(graph);
    for(NodeL nodeAux = getListFirst(adj); nodeAux; nodeAux = getListNext(nodeAux)){
        AdjList adjList = getListInfo(nodeAux);

        List edgeList = getEdgeList(adjList);

        for(NodeL nodeAux2 = getListFirst(edgeList); nodeAux2; nodeAux2 = getListNext(nodeAux2)){
            Edge edge = getListInfo(nodeAux2);

            insertListElement(edges, edge);
        }
    }

    return edges;
}

int findIndexA(Graph graph, char* destiny){
    for(NodeL nodeAux = getListFirst(getAdjList(graph)); nodeAux; nodeAux = getListNext(nodeAux)){

        if (strcmp(getVertexId(getListInfo(nodeAux)), destiny) == 0) {
            return getListIndexOf(nodeAux);
        }
    }

    return -1;
}

List kruskal(Graph graph){
    convertDigraphForGraph(graph);

    List edges = createListEdge(graph);
    sorting(edges, 0, (getListSize(edges) - 1));

    List uf = createUFind(graph);

    for(NodeL nodeAux = getListFirst(edges); nodeAux; nodeAux = getListNext(nodeAux)){
        Edge edge = getListInfo(nodeAux);
        UFUnion(uf, edge);
    }

    endList(edges);

    return uf;
}