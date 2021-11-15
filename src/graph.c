#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

typedef struct graphStruct {
    int amountVertex;
    int amountEdge;
    List adj;
} GraphStruct;

typedef struct edgeStruct {
    char name[100];
    char cepRight[100];
    char cepLeft[100];

    double size;
    double speed;
} EdgeStruct;

typedef struct vertexStruct {
    char id[100];
    double x;
    double y;
} VertexStruct;

typedef struct adjList {
    VertexStruct vertex;
    List edge;

} AdjList;

Graph createGraph() {
    GraphStruct* new = (GraphStruct*)malloc(sizeof(GraphStruct));

    new->adj = createList();
    new->amountEdge = 0;
    new->amountVertex = 0;

    return new;
}

int insertVertexGraph(Graph graph, char* id, double x, double y) {
}