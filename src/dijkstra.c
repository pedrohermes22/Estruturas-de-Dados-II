#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DOUBLE_MAX 100000
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

    for(i = lesser + 1; i < getAmountVertex(graph); i++){
        if(visit[i] && (dist[lesser] > dist[i])){
            lesser = i;
        }
    }

    
    return lesser;
}

void updateSize(Graph graph, double* dist, int* back, AdjList adjU, int u, int v, int index){
    int i = 0;

    List edgeU = getEdgeList(adjU);

    Edge edgeV = NULL;

    for(NodeL nodeAux = getListFirst(edgeU); nodeAux; nodeAux = getListNext(nodeAux)){
        if(index == i){
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

void updateSpeed(Graph graph, double* dist, int* back, AdjList adjU, int u, int v, int index){
    int i = 0;

    List edgeU = getEdgeList(adjU);

    Edge edgeV = NULL;

    for(NodeL nodeAux = getListFirst(edgeU); nodeAux; nodeAux = getListNext(nodeAux)){
        if(index == i){
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

int findIndex(Graph graph, char* destiny){
    for(NodeL nodeAux = getListFirst(getAdjList(graph)); nodeAux; nodeAux = getListNext(nodeAux)){

        if (strcmp(getVertexId(getListInfo(nodeAux)), destiny) == 0) {
            return getListIndexOf(nodeAux);
        }
    }

    return -1;
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
        
        if (strcmp(getVertexId(getListInfo(nodeAux)), origin) == 0) {
            orig = i;
            dist[i] = 0;
        }

        if (strcmp(getVertexId(getListInfo(nodeAux)), destiny) == 0) {
            dest = i;
        }
    }

    while(findVisit(graph, visit)){
        int u = searchLesserDist(graph, visit, dist);
        visit[u] = 0;

        int index = 0;

        AdjList adjU = getListInfo(getListNodeByIndex(getAdjList(graph), u));

        List edgeU = getEdgeList(adjU);

        for(NodeL nodeAux = getListFirst(edgeU); nodeAux; nodeAux = getListNext(nodeAux)){
            index = getListIndexOf(nodeAux);
            int i = findIndex(graph, getEdgeDestiny(getListInfo(nodeAux)));
            updateSpeed(graph, dist, back, adjU, u, i, index);
        }
    }

    List dijkstra = createList();

    if(back[dest] > 0){
        for(int i = dest; i != -1; i = back[i]){
            AdjList adj = NULL;

            for(NodeL nodeAux = getListFirst(getAdjList(graph)); nodeAux; nodeAux = getListNext(nodeAux)){
                if(getListIndexOf(nodeAux) == i){
                    adj = getListInfo(nodeAux);
                    break;
                }
            }
            insertListElement(dijkstra, adj);

        }
    }

    return dijkstra;

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
        if (strcmp(getVertexId(getListInfo(nodeAux)), origin) == 0) {
            orig = i;
            dist[i] = 0;
        }

        if (strcmp(getVertexId(getListInfo(nodeAux)), destiny) == 0) {
            dest = i;
        }
    }

    while(findVisit(graph, visit)){
        int u = searchLesserDist(graph, visit, dist);
        visit[u] = 0;

        int index = 0;

        AdjList adjU = getListInfo(getListNodeByIndex(getAdjList(graph), u));

        List edgeU = getEdgeList(adjU);

        for(NodeL nodeAux = getListFirst(edgeU); nodeAux; nodeAux = getListNext(nodeAux)){
            index = getListIndexOf(nodeAux);
            int i = findIndex(graph, getEdgeDestiny(getListInfo(nodeAux)));
            updateSize(graph, dist, back, adjU, u, i, index);
        }
    }

    List dijkstra = createList();

    if(back[dest] > 0){
        for(int i = dest; i != -1; i = back[i]){
            AdjList adj = NULL;

            for(NodeL nodeAux = getListFirst(getAdjList(graph)); nodeAux; nodeAux = getListNext(nodeAux)){
                if(getListIndexOf(nodeAux) == i){
                    adj = getListInfo(nodeAux);
                    break;
                }
            }
            insertListElement(dijkstra, adj);

        }
    }

    return dijkstra;
}