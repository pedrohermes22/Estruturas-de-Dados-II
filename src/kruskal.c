#include <stdio.h>
#include <string.h>

#include "graph.h"
#include "svg.h"

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
                insertEdgeGraph(final, getEdgeOrigin(edge), getEdgeDestiny(edge), "a", "b", getEdgeSize(edge), getEdgeSpeed(edge),
                                getEdgeName(edge));
            }
        }
    }

    return final;
}

void mst(Graph graph) {
    if (graph == NULL) return;
    
    
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

int findIndexA(Graph graph, char* destiny){
    for(NodeL nodeAux = getListFirst(getAdjList(graph)); nodeAux; nodeAux = getListNext(nodeAux)){

        if (strcmp(getVertexId(getListInfo(nodeAux)), destiny) == 0) {
            return getListIndexOf(nodeAux);
        }
    }

    return -1;
}

void kruskal(Graph graph) {
    if ((graph == NULL) || (getAmountVertex(graph) == 0)) return;

    int vertices = getAmountVertex(graph);
    int orig = 0;
    int dest = 0;
    int primeiro = 1;
    double menorPeso = 0;

    int pai[vertices];
    int arv[vertices];

    for (int i = 0; i < vertices; i++) {
        arv[i] = i;
        pai[i] = -1;
    }
    pai[orig] = orig;

    while (1) {
        primeiro = 1;
        for (NodeL nodeAux = getListFirst(getAdjList(graph)); nodeAux; nodeAux = getListNext(nodeAux)) {
            AdjList adj = getListInfo(nodeAux);
            int u = getListIndexOf(nodeAux);

            for (NodeL nodeAux2 = getListFirst(getEdgeList(adj)); nodeAux2; nodeAux2 = getListNext(nodeAux2)) {
                Edge edge = getListInfo(nodeAux2);
                int v = findIndexA(graph, getEdgeDestiny(edge));

                if (arv[u] != arv[v]) {
                    if(primeiro){
                        menorPeso = getEdgeSize(edge);
                        orig = u;
                        dest = v;
                        primeiro = 0;
                    }else{
                        if(menorPeso > getEdgeSize(edge)){
                            menorPeso = getEdgeSize(edge);
                            orig = u;
                            dest = v;
                        }
                    }
                }
            }
        }

        if (primeiro == 1) break;

        if(pai[orig] == -1) pai[orig] = dest;
        else pai[dest] = orig;

        for(int i = 0; i < vertices; i++){
            if(arv[i] == arv[dest]){
                arv[i] = arv[orig];
            }
        }
    }

//     printf("Vertices amount: %d\n\n", vertices);

//     FILE *svg = fopen("../graph.svg", "w");
//     openSvg(svg);

//     drawDots(graph, svg);

//     closeSvg(svg);
//     if (svg != NULL) fclose(svg);

//     List adjList = getAdjList(graph);
//     AdjList aux = getListInfo(getListFirst(adjList));  // Primeiro vértice.
}