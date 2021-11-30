#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "list.h"

// Estrutura do grapho
typedef struct graphStruct{

    int amountVertex;
    List adj;

}GraphStruct;

// Estrutura da aresta
typedef struct edgeStruct{
    char name[100];
    char cepRight[100];
    char cepLeft[100];

    char origin[100];
    char destiny[100];

    double size;
    double speed;

}EdgeStruct;

// Estrutura do vertice
typedef struct vertexStruct{
    char id[100];
    double x;
    double y;

}VertexStruct;

// Estrutura da lista de adjacência
typedef struct adjList{

    VertexStruct vertex;
    List edge;

}AdjListStruct;

// Cria um grapho
Graph createGraph(){
    GraphStruct* new = (GraphStruct* ) malloc(sizeof(GraphStruct));

    new->adj = createList();
    new->amountVertex = 0;

    return new;
}

// Deleta um grapho
int destroyGraph(Graph graph){
    GraphStruct* graphAux = (GraphStruct* ) graph;

    if(graphAux == NULL){
        return 0;
    }

    // Percorre a lista de adjacência (Vértices)
    for(NodeL nodeAux = getListFirst(graphAux->adj); nodeAux; nodeAux = getListNext(nodeAux)){
        AdjListStruct* adjAux = (AdjListStruct* ) getListInfo(nodeAux);

        // Percorre a lista das Arestas
        for(NodeL nodeAux2 = getListFirst(adjAux->edge); nodeAux2; nodeAux2 = getListNext(nodeAux2)){
            EdgeStruct* edge = (EdgeStruct* ) getListInfo(nodeAux2);

            // Libera uma aresta
            free(edge);
        }

        // Libera a lista de Aresta
        endList(adjAux->edge);
        free(adjAux);
    }

    // Libera o grapho
    endList(graphAux->adj);
    free(graphAux);

    return 1;
}

// Insere um vértice no grapho
int insertVertexGraph(Graph graph, char* id, double x, double y){
    GraphStruct* graphAux = (GraphStruct* ) graph;

    if(graphAux == NULL){
        return 0;
    }

    // Cria um novo nó na lista de adjacencia
    AdjListStruct* new = (AdjListStruct* ) malloc(sizeof(AdjListStruct));
    strcpy(new->vertex.id, id);
    new->vertex.x = x;
    new->vertex.y = y;

    // Cria um lista para as arestas
    new->edge = createList();

    insertListElement(graphAux->adj, new);

    graphAux->amountVertex++;

    return 1;
}

// Insere uma aresta no grapho
int insertEdgeGraph(Graph graph, char* origin, char* destiny, char* cepRight, char* cepLeft, double size, double speed, char* name){
    GraphStruct* graphAux = (GraphStruct* ) graph;

    if(graphAux == NULL){
        return 0;
    }

    AdjListStruct* originAdj = NULL;
    AdjListStruct* destinyAdj = NULL;

    // Percorre a lista e busca se as arestas de origem e destino existem e salva
    for(NodeL nodeAux = getListFirst(graphAux->adj); nodeAux; nodeAux = getListNext(nodeAux)){
        AdjListStruct* adjAux = (AdjListStruct* ) getListInfo(nodeAux);

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


    // Cria uma aresta e salva os dados
    EdgeStruct* new = (EdgeStruct* ) malloc(sizeof(EdgeStruct));

    new->size = size;
    new->speed = speed;

    strcpy(new->origin, origin);
    strcpy(new->destiny, destiny);
    strcpy(new->cepLeft, cepLeft);
    strcpy(new->cepRight, cepRight);
    strcpy(new->name, name);

    insertListElement(originAdj->edge, new);

    return 1;
}

// Deleta um vértice do grapho
int deleteVertexGraph(Graph graph, char* id){
    GraphStruct* graphAux = (GraphStruct* ) graph;

    if(graphAux == NULL){
        return 0;
    }

    // Percorre a lista de adjacência
    for(NodeL nodeAux = getListFirst(graphAux->adj); nodeAux; nodeAux = getListNext(nodeAux)){
        AdjListStruct* adjAux = (AdjListStruct* ) getListInfo(nodeAux);

        // Se achar o vértice, apaga suas arestas e ele mesmo
        if(strcmp(id, adjAux->vertex.id) == 0){
            for(NodeL nodeAux2 = getListFirst(adjAux->edge); nodeAux2; nodeAux2 = getListNext(nodeAux2)){
                EdgeStruct* edge = (EdgeStruct* ) getListInfo(nodeAux2);

                free(edge);
            }
            endList(adjAux->edge);
            free(adjAux);
            graphAux->amountVertex--;

        }else{
            // Se não, busca arestas que tem o vértice como destino e também apaga
            for(NodeL nodeAux2 = getListFirst(adjAux->edge); nodeAux2; nodeAux2 = getListNext(nodeAux2)){
                EdgeStruct* edge = (EdgeStruct* ) getListInfo(nodeAux2);

                if(strcmp(edge->destiny, id) == 0){
                    removeListNode(adjAux->edge, nodeAux2);
                    free(edge);
                }
            } 
        }
    }

    return 1;
}

// Deleta uma aresta do grapho
int deleteEdgeGraph(Graph graph, char* origin, char* destiny){
    GraphStruct* graphAux = (GraphStruct* ) graph;

    if(graphAux == NULL){
        return 0;
    }

    // Percorre a lista de adjacência
    for(NodeL nodeAux = getListFirst(graphAux->adj); nodeAux; nodeAux = getListNext(nodeAux)){
        AdjListStruct* adjAux = (AdjListStruct* ) getListInfo(nodeAux);

        // Achou o vértice de origem, busca a aresta e deleta
        if(strcmp(adjAux->vertex.id, origin) == 0){

            for(NodeL nodeAux2 = getListFirst(adjAux->edge); nodeAux2; nodeAux2 = getListNext(nodeAux2)){
                EdgeStruct* edge = (EdgeStruct* ) getListInfo(nodeAux2);

                if(strcmp(edge->destiny, destiny) == 0){
                    removeListNode(adjAux->edge, nodeAux2);
                    free(edge);
                    return 1;
                }
            } 
        }
    }

    return 0;
}

double getVertexX(AdjList adjLis){
    AdjListStruct* adjLisAux = (AdjListStruct* ) adjLis;

    return adjLisAux->vertex.x;
}

double getVertexY(AdjList adjLis){
    AdjListStruct* adjLisAux = (AdjListStruct* ) adjLis;

    return adjLisAux->vertex.y;
}

char* getVertexId(AdjList adjLis){
    AdjListStruct* adjLisAux = (AdjListStruct* ) adjLis;

    return adjLisAux->vertex.id;
}

int getAmountVertex(Graph graph){
    GraphStruct* graphAux = (GraphStruct* ) graph;

    return graphAux->amountVertex;
}

List getAdjList(Graph graph){
    GraphStruct* graphAux = (GraphStruct* ) graph;

    return graphAux->adj;
}

List getEdgeList(AdjList adjLis){
    AdjListStruct* adjLisAux = (AdjListStruct* ) adjLis;

    return adjLisAux->edge;
}

double getEdgeSize(Edge edge){
    EdgeStruct* edgeAux = (EdgeStruct* ) edge;

    return edgeAux->size;
}

double getEdgeSpeed(Edge edge){
    EdgeStruct* edgeAux = (EdgeStruct* ) edge;

    return edgeAux->speed;
}