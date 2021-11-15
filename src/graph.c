#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct graphStruct{

    int amountVertex;
    int amountEdge;
    AdjList* adj;

}GraphStruct;

typedef struct adjList{

    VertexStruct vertex;
    EdgeStruct* edge;

}AdjList;

typedef struct vertexStruct{
    char id[100];
    double x;
    double y;

}VertexStruct;

typedef struct edgeStruct{
    char name[100];
    char cepRight[100];
    char cepLeft[100];

    double size;
    double speed;

    struct edgeStruct *next;
}EdgeStruct;
