#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dijkstra.h"


int searchLesserDistance(float* dist, int* visit, int NV){
    int lesser = -1;
    int first = 1;

    for(int i = 0;  i < NV; i++){
        if(dist[i] >= 0 && visit[i]){
            if(first){
                lesser = i;
                first = 0;
            }else{
                if(dist[lesser] > dist[i]){
                    lesser = i;
                }
            }
        }
    }

    return lesser;
}

void findLesserDrive(Graph graph, int ini, int* back, float* dist){

    int cont, NV, ind, *visit, u;
    cont = NV = getAmountVertex(graph);
    visit = (int *) malloc(NV* sizeof(int));

    for(int i = 0; i < NV; i++){
        back[i] = -1;
        dist[i] = -1;
        visit[i]= 0;
    }
    dist[ini] = 0;
    
    while(cont > 0){
        u =searchLesserDistance(dist, visit, NV);
        if(u == -1){
            break;
        }

        visit[u] = -1;
        cont--;


    }

    free(visit);    

}