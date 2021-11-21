#ifndef __GRAPH_H
#define __GRAPH_H

#include "list.h"

typedef void* Graph;
typedef void* Vertex;
typedef void* AdjList;
typedef void* Edge;

Graph createGraph();

int destroyGraph(Graph graph);

int insertVertexGraph(Graph graph, char* id, double x, double y);

int insertEdgeGraph(Graph graph, char* origin, char* destiny, char* cepRight, char* cepLeft, double size, double speed, char* name);

int deleteVertexGraph(Graph graph, char* id);

int deleteEdgeGraph(Graph graph, char* origin, char* destiny);

int getAmountVertex(Graph graph);

List getAdjList(Graph graph);

List getEdgeList(AdjList adjLis);

char* getVertexId(AdjList adjLis);

double getEdgeSize(Edge edge);

double getEdgeSpeed(Edge edge);

#endif
