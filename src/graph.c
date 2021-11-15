#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "list.h"

typedef struct graphStruct{

    int amountVertex;
    int amountEdge;
    List adj;

}GraphStruct;

typedef struct edgeStruct{
    char name[100];
    char cepRight[100];
    char cepLeft[100];

    char origin[100];
    char destiny[100];

    double size;
    double speed;

}EdgeStruct;

typedef struct vertexStruct{
    char id[100];
    double x;
    double y;

}VertexStruct;
typedef struct adjList{

    VertexStruct vertex;
    List edge;

}AdjList;

Graph createGraph(){
    GraphStruct* new = (GraphStruct* ) malloc(sizeof(GraphStruct));

    new->adj = createList();
    new->amountEdge = 0;
    new->amountVertex = 0;

    return new;
}

int insertVertexGraph(Graph graph, char* id, double x, double y){
    GraphStruct* graphAux = (GraphStruct* ) graph;

    if(graphAux == NULL){
        return 0;
    }

    AdjList* new = (AdjList* ) malloc(sizeof(AdjList));
    strcpy(new->vertex.id, id);
    new->vertex.x = x;
    new->vertex.y = y;


    new->edge = createList();

    insertListElement(graphAux->adj, new);

    graphAux->amountVertex++;

    return 1;
}

int insertEdgeGraph(Graph graph, char* origin, char* destiny, char* cepRight, char* cepLeft, double size, double speed, char* name){
    GraphStruct* graphAux = (GraphStruct* ) graph;

    if(graphAux == NULL){
        return 0;
    }

    AdjList* originAdj = NULL;
    AdjList* destinyAdj = NULL;

    for(NodeL nodeAux = getListFirst(graphAux->adj); nodeAux; nodeAux = getListNext(nodeAux)){
        AdjList* adjAux = (AdjList* ) getListInfo(nodeAux);

        if(strcpy(origin, adjAux->vertex.id) == 0){
            originAdj = adjAux;
        }else{
            if(strcpy(destiny, adjAux->vertex.id) == 0){
                destinyAdj = adjAux;
            }
        }
    }

    if(originAdj == NULL || destinyAdj == NULL){
        return 0;
    }


    EdgeStruct* new = (EdgeStruct* ) malloc(sizeof(EdgeStruct));

    new->size = size;
    new->speed = speed;

    strcpy(new->origin, origin);
    strcpy(new->destiny, destiny);
    strcpy(new->cepLeft, cepLeft);
    strcpy(new->cepRight, cepRight);
    strcpy(new->name, name);

    insertListElement(originAdj->edge, new);

    graphAux->amountEdge++;

    return 1;
}

int deleteVertexGraph(Graph graph, char* id){
    GraphStruct* graphAux = (GraphStruct* ) graph;

    if(graphAux == NULL){
        return 0;
    }

    for(NodeL nodeAux = getListFirst(graphAux->adj); nodeAux; nodeAux = getListNext(nodeAux)){
        
    }
}