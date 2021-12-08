#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "list.h"
#include "hashtable.h"

// Estrutura do grapho
typedef struct graphStruct{

    int amountVertex;
    int amountEdge;
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
    
    int isActive;

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
    new->amountEdge = 0;

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

// Deleta um grapho mas sem apagar os vertices e arestas
int destroyGraphWL(Graph graph){
    GraphStruct* graphAux = (GraphStruct* ) graph;

    if(graphAux == NULL){
        return 0;
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

        if(strcmp(origin, adjAux->vertex.id) == 0){
            originAdj = adjAux;
        }else{
            if(strcmp(destiny, adjAux->vertex.id) == 0){
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
    new->isActive = 1;

    strcpy(new->origin, origin);
    strcpy(new->destiny, destiny);
    strcpy(new->cepLeft, cepLeft);
    strcpy(new->cepRight, cepRight);
    strcpy(new->name, name);

    insertListElement(originAdj->edge, new);

    graphAux->amountEdge++;
    return 1;
}

// Deleta um vértice do grapho
int deleteVertexGraph(Graph graph, char* id){
    GraphStruct* graphAux = (GraphStruct* ) graph;

    if(graphAux == NULL){
        return 0;
    }

    NodeL back = NULL;

    // Percorre a lista de adjacência
    for(NodeL nodeAux = getListFirst(graphAux->adj); nodeAux; nodeAux = getListNext(nodeAux)){
        AdjListStruct* adjAux = (AdjListStruct* ) getListInfo(nodeAux);

        // Se achar o vértice, apaga suas arestas e ele mesmo
        if(strcmp(id, adjAux->vertex.id) == 0){
            back = nodeAux;

        }else{
            // Se não, busca arestas que tem o vértice como destino e também apaga
            for(NodeL nodeAux2 = getListFirst(adjAux->edge); nodeAux2; nodeAux2 = getListNext(nodeAux2)){
                EdgeStruct* edge = (EdgeStruct* ) getListInfo(nodeAux2);

                if(strcmp(edge->destiny, id) == 0){
                    removeListNode(adjAux->edge, nodeAux2);
                    free(edge);
                    graphAux->amountEdge--;
                }
            } 
        }
    }
    if(back != NULL){
        AdjListStruct* adjAux = (AdjListStruct* ) getListInfo(back);

        for(NodeL nodeAux2 = getListFirst(adjAux->edge); nodeAux2; nodeAux2 = getListNext(nodeAux2)){
            EdgeStruct* edge = (EdgeStruct* ) getListInfo(nodeAux2);

            graphAux->amountEdge--;
            free(edge);
        }
        endList(adjAux->edge);
        free(adjAux);
        graphAux->amountVertex--;
        removeListNode(graphAux->adj, back);
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
                    graphAux->amountEdge--;
                    return 1;
                }
            } 
        }
    }

    return 0;
}

AdjList searchVertex(Graph graph, char* id){
    GraphStruct* graphAux = (GraphStruct* ) graph;

    if(graphAux == NULL){
        return 0;
    }

    // Percorre a lista de adjacência
    for(NodeL nodeAux = getListFirst(graphAux->adj); nodeAux; nodeAux = getListNext(nodeAux)){
        AdjListStruct* adjAux = (AdjListStruct* ) getListInfo(nodeAux);

        // Se achar o vértice, apaga suas arestas e ele mesmo
        if(strcmp(id, adjAux->vertex.id) == 0){
            return adjAux;
        }
    }
    return NULL;
}

Edge searchEdge(AdjList origin, char* destiny){
    AdjListStruct* originAux = (AdjListStruct* ) origin;

    if(originAux == NULL){
        return 0;
    }

    // Percorre de aresta
    for(NodeL nodeAux = getListFirst(originAux->edge); nodeAux; nodeAux = getListNext(nodeAux)){
        EdgeStruct* edge = (EdgeStruct* ) getListInfo(nodeAux);

        // Se achar o id de destino retorna a aresta
        if(strcmp(destiny, edge->destiny) == 0){
            return edge;
        }
    }
    return NULL;
}

void dfs(Graph graph, Graph agm, AdjList adj, int cd, double fatorIn, double fator, HashTable visit){

    List edges = getEdgeList(adj);

    hashTableInsert(visit, getVertexId(adj), adj);

    for(NodeL nodeAux = getListFirst(edges); nodeAux; nodeAux = getListNext(nodeAux)){
        Edge edge = getListInfo(nodeAux);
        AdjList adjToChange = searchVertex(graph, getEdgeOrigin(edge));
        Edge edgeFromGraph = searchEdge(adjToChange, getEdgeDestiny(edge));

        double speed = getEdgeSpeed(edge) - (getEdgeSpeed(edge) * fator);

        if(edgeFromGraph != NULL){
            setEdgeSpeed(edgeFromGraph, speed);
        }

        setEdgeSpeed(edge, speed);

        AdjList next = searchVertex(agm, getEdgeDestiny(edge));

        if(fator + fatorIn < 1){
            fator = fator + fatorIn;
        }

        if(hashTableSearch(visit, getVertexId(next)) == NULL){
            dfs(graph, agm, next, cd+1, fatorIn, fator, visit);
        }

    }

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

char* getEdgeDestiny(Edge edge){
    EdgeStruct* edgeAux = (EdgeStruct* ) edge;

    return edgeAux->destiny;
}

char* getEdgeOrigin(Edge edge){
    EdgeStruct* edgeAux = (EdgeStruct* ) edge;

    return edgeAux->origin;
}

char* getEdgeName(Edge edge){
    EdgeStruct* edgeAux = (EdgeStruct* ) edge;

    return edgeAux->name;
}

int getAmountEdge(Graph graph){
    GraphStruct* graphAux = (GraphStruct* ) graph;

    return graphAux->amountEdge;
}

char* getEdgeRightCep(Edge edge){
    EdgeStruct* edgeAux = (EdgeStruct* ) edge;

    return edgeAux->cepRight;
}

char* getEdgeLeftCep(Edge edge){
    EdgeStruct* edgeAux = (EdgeStruct* ) edge;

    return edgeAux->cepLeft;
}

void setEdgeSpeed(Edge edge, double speed){
    EdgeStruct* edgeAux = (EdgeStruct* ) edge;

    edgeAux->speed = speed;
}

int isEdgeValid(Edge edge){
    EdgeStruct* edgeAux = (EdgeStruct* ) edge;

    return edgeAux->isActive;
}

void setEdgeValid(Edge edge, int valid){
    EdgeStruct* edgeAux = (EdgeStruct* ) edge;

    edgeAux->isActive = valid;
}

void convertDigraphForGraph(Graph graph){
    for (NodeL nodeAux = getListFirst(getAdjList(graph)); nodeAux; nodeAux = getListNext(nodeAux)) {
        AdjList adj = getListInfo(nodeAux);


        for (NodeL nodeAux2 = getListFirst(getEdgeList(adj)); nodeAux2; nodeAux2 = getListNext(nodeAux2)) {
            Edge edge = getListInfo(nodeAux2);
            Edge aux = searchEdge(searchVertex(graph, getEdgeDestiny(edge)), getEdgeOrigin(edge));

            if(aux == NULL){
                insertEdgeGraph(graph, getEdgeDestiny(edge), getEdgeOrigin(edge), getEdgeRightCep(edge), getEdgeLeftCep(edge), getEdgeSize(edge), getEdgeSpeed(edge), getEdgeName(edge));
            }
        }
    }
}