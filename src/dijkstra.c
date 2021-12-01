#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DOUBLE_MAX 10000000
#include "dijkstra.h"

int findVisit(Graph graph, int* visit){
    for(int i = 0; i < getAmountVertex(graph); i++){
        if(visit[i] == 1){
            return 1;
        }
    }
    return 0;
}

int searchLesserDist(Graph graph, int* visit, double* dist){

    int i;
    for(i = 0; i < getAmountVertex(graph); i++){
        if(visit[i] == 1){
            break;
        }
    }
    
    if(i == getAmountVertex(graph)){
        return -1;
    }

    int lesser = i;

    for(i = lesser+1; i < getAmountVertex(graph); i++){
        if(visit[i] && (dist[lesser] > dist[i])){
            lesser = i;
        }
    }

    
    return lesser;
}

void updateSize(Graph graph, int* dist, int* back, AdjList adjU, int u, int v){
    int i = 0;

    List edgeU = getEdgeList(adjU);

    Edge edgeV = NULL;

    for(NodeL nodeAux = getListFirst(edgeU); nodeAux; nodeAux = getListNext(nodeAux)){
        if(v == i){
            edgeV = getListInfo(nodeAux);
            break;
        }
        i++;
    }

    if(edgeV){
        if(dist[v] > dist[u] + getEdgeSize(edgeV)){
            dist[v] = dist[u] + getEdgeSize(edgeV);
            back[v] = u;
        }
    }

}

void updateSpeed(Graph graph, int* dist, int* back, AdjList adjU, int u, int v){
    int i = 0;

    List edgeU = getEdgeList(adjU);

    Edge edgeV = NULL;

    for(NodeL nodeAux = getListFirst(edgeU); nodeAux; nodeAux = getListNext(nodeAux)){
        if(v == i){
            edgeV = getListInfo(nodeAux);
            break;
        }
        i++;
    }

    if(edgeV){
        if(dist[v] > dist[u] + getEdgeSpeed(edgeV)){
            dist[v] = dist[u] + getEdgeSpeed(edgeV);
            back[v] = u;
        }
    }

}

List dijkstraSpeed(Graph graph, char* origin, char* destiny){

    int v = getAmountVertex(graph);

    int visit[v];
    int back[v];

    double dist[v];
    int dest;
    int orig;

    for(NodeL nodeAux = getListFirst(getAdjList(graph)); nodeAux; nodeAux = getListNext(nodeAux)){
        int i = getListIndexOf(nodeAux);

        visit[i] = 1;
        dist[i] = DOUBLE_MAX;
        back[i] = -1;
        if (strcmp(getVertexId(getListInfo(nodeAux)), origin)) {
            orig = i;
            dist[i] = 0;
        }

        if (strcmp(getVertexId(getListInfo(nodeAux)), destiny)) {
            dest = i;
        }
    }

    while(findVisit(graph, visit)){
        int u = searchLesserDist(graph, visit, dist);
        visit[u] = 0;

        int i = 0;
        AdjList adjU = getListInfo(getListNodeByIndex(getAdjList(graph), u));

        List edgeU = getEdgeList(adjU);
        i = 0;

        for(NodeL nodeAux = getListFirst(edgeU); nodeAux; nodeAux = getListNext(nodeAux)){
            updateSpeed(graph, dist, back, adjU, u, i);
        }
    }

    List dijkstra = createList();

    if(back[dest] > 0){
        for(int i = back[dest]; dist[i] == 0; i = back[i]){
            AdjList adj = getListInfo(getListNodeByIndex(getAdjList(graph), i));
            insertListElement(dijkstra, adj);

        }
    }

    return dijkstra;
}

List dijkstraSize(Graph graph, char* origin, char* destiny){

    int v = getAmountVertex(graph);

    int visit[v];
    int back[v];

    double dist[v];
    int dest;
    int orig;

    for(NodeL nodeAux = getListFirst(getAdjList(graph)); nodeAux; nodeAux = getListNext(nodeAux)){
        int i = getListIndexOf(nodeAux);

        visit[i] = 1;
        dist[i] = DOUBLE_MAX;
        back[i] = -1;
        if (strcmp(getVertexId(getListInfo(nodeAux)), origin)) {
            orig = i;
            dist[i] = 0;
        }

        if (strcmp(getVertexId(getListInfo(nodeAux)), destiny)) {
            dest = i;
        }
    }

    while(findVisit(graph, visit)){
        int u = searchLesserDist(graph, visit, dist);
        visit[u] = 0;

        int i = 0;
        AdjList adjU = getListInfo(getListNodeByIndex(getAdjList(graph), u));

        List edgeU = getEdgeList(adjU);
        i = 0;

        for(NodeL nodeAux = getListFirst(edgeU); nodeAux; nodeAux = getListNext(nodeAux)){
            updateSize(graph, dist, back, adjU, u, i);
        }
    }

    List dijkstra = createList();

    if(back[dest] > 0){
        for(int i = back[dest]; dist[i] == 0; i = back[i]){
            AdjList adj = getListInfo(getListNodeByIndex(getAdjList(graph), i));
            printf("%s", getVertexId(adj));
            insertListElement(dijkstra, adj);

        }
    }

    return dijkstra;
}