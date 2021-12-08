#ifndef __GRAPH_H
#define __GRAPH_H

#include "list.h"
#include "hashtable.h"

typedef void* Graph;
typedef void* Vertex;
typedef void* AdjList;
typedef void* Edge;

Graph createGraph();

int destroyGraph(Graph graph);

int destroyGraphWL(Graph graph);

int insertVertexGraph(Graph graph, char* id, double x, double y);

int insertEdgeGraph(Graph graph, char* origin, char* destiny, char* cepRight, char* cepLeft, double size, double speed, char* name);

int deleteVertexGraph(Graph graph, char* id);

int deleteEdgeGraph(Graph graph, char* origin, char* destiny);

AdjList searchVertex(Graph graph, char* id);

Edge searchEdge(AdjList origin, char* destiny);

void dfs(Graph graph, Graph agm, AdjList adj, int cd, double fatorIn, double fator, HashTable visit);

double getVertexX(AdjList adjLis);

double getVertexY(AdjList adjLis);

char* getVertexId(AdjList adjLis);

int getAmountVertex(Graph graph);

List getAdjList(Graph graph);

List getEdgeList(AdjList adjLis);

double getEdgeSize(Edge edge);

double getEdgeSpeed(Edge edge);

char* getEdgeDestiny(Edge edge);

char* getEdgeOrigin(Edge edge);

char* getEdgeName(Edge edge);

int getAmountEdge(Graph graph);

char* getEdgeRightCep(Edge edge);

char* getEdgeLeftCep(Edge edge);

int isEdgeValid(Edge edge);

void setEdgeValid(Edge edge, int valid);

void convertDigraphForGraph(Graph graph);

#endif
