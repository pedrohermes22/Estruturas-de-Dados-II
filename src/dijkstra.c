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

void update(Graph graph, int* dist, int* back, int u, int v){
    int i = 0;
    AdjList adjU = NULL;
    for(NodeL nodeAux = getListFirst(getAdjList(graph)); nodeAux; nodeAux = getListNext(nodeAux)){
        if(i == u){
            adjU = getListInfo(nodeAux);
            break;
        }
        i++;
    }
    List edgeU = getEdgeList(adjU);
    i = 0;

    Edge edgeV = NULL;

    for(NodeL nodeAux = getListFirst(edgeU); nodeAux; nodeAux = getListNext(nodeAux)){
        if(v == i){
            edgeV = getListInfo(nodeAux);
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

int *dijstra(Graph graph, char* origin, char* destiny){

    int v = getAmountVertex(graph);
    
    int i = 0;
    int visit[v];
    int back[v];
    
    double* dist = (double* ) malloc(v * sizeof(double));

    for(NodeL nodeAux = getListFirst(getAdjList(graph)); nodeAux; nodeAux = getListNext(nodeAux)){
        visit[i] = 1;
        dist[i] = DOUBLE_MAX;
        back[i] = -1;
        if (strcmp(getVertexId(getListInfo(nodeAux)), origin)) {
            dist[i] = 0;
        }
        i++;
    }

    while(findVisit(graph, visit)){
        int u = searchLesserDist(graph, visit, dist);
        visit[u] = 0;

        int i = 0;
        AdjList adjU = NULL;
        for(NodeL nodeAux = getListFirst(getAdjList(graph)); nodeAux; nodeAux = getListNext(nodeAux)){
            if(i == u){
                adjU = getListInfo(nodeAux);
                break;
            }
            i++;
        }

        List edgeU = getEdgeList(adjU);
        i = 0;

        for(NodeL nodeAux = getListFirst(edgeU); nodeAux; nodeAux = getListNext(nodeAux)){
            update(graph, dist, back, u, i);
        }
    }
    return dist;
}