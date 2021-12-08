#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "union-find.h"
#include "list.h"

List createUFind(Graph graph){
    List unionFind = createList();
    List adj = getAdjList(graph);

    for(NodeL nodeAux = getListFirst(adj); nodeAux; nodeAux = getListNext(nodeAux)){
        AdjList aux = getListInfo(nodeAux);
        Graph gr = createGraph();

        insertVertexGraph(gr, getVertexId(aux), getVertexX(aux), getVertexY(aux));
        insertListElement(unionFind, gr);
    }

    return unionFind;
}

int UFfind(List unionFind, char* id){

    for(NodeL nodeAux = getListFirst(unionFind); nodeAux; nodeAux = getListNext(nodeAux)){
        List adj = getAdjList(getListInfo(nodeAux));

        for(NodeL nodeAux2 = getListFirst(adj); nodeAux2; nodeAux2 = getListNext(nodeAux2)){
            AdjList aux = getListInfo(nodeAux2);
            if(strcmp(getVertexId(aux), id) == 0){
                return getListIndexOf(nodeAux);
            }
        }

    }

    return -1;
}

void UFUnion(List unionFind, Edge edge){
    char* originId = getEdgeOrigin(edge);
    char* destinyId = getEdgeDestiny(edge);

    int indexOrigin = UFfind(unionFind, originId);
    int indexDestiny = UFfind(unionFind, destinyId);

    if(indexDestiny != -1 && indexOrigin != -1){
        if(indexOrigin != indexDestiny){
            
            NodeL adjOriginNode = getListNodeByIndex(unionFind, indexOrigin);
            NodeL adjDestinyNode = getListNodeByIndex(unionFind, indexDestiny);

            Graph origin = getListInfo(adjOriginNode);
            Graph destiny = getListInfo(adjDestinyNode);

            List adjDestiny = getAdjList(destiny);
            List adjOrigin = getAdjList(origin);

            for(NodeL nodeAux = getListFirst(adjDestiny); nodeAux; nodeAux = getListNext(nodeAux)){
                AdjList adj = getListInfo(nodeAux);

                insertListElement(adjOrigin, adj);
            }
            insertEdgeGraph(origin, getEdgeOrigin(edge), getEdgeDestiny(edge), getEdgeRightCep(edge), getEdgeLeftCep(edge), getEdgeSize(edge), getEdgeSpeed(edge), getEdgeName(edge));
            destroyGraphWL(destiny);
            removeListNode(unionFind ,adjDestinyNode);
        }
    }
}
