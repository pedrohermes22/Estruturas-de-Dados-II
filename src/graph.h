#ifndef __GRAPH_H
#define __GRAPH_H

typedef void* Graph;

Graph createGraph();

int destroyGraph(Graph graph);

int insertVertexGraph(Graph graph, char* id, double x, double y);

int insertEdgeGraph(Graph graph, char* origin, char* destiny, char* cepRight, char* cepLeft, double size, double speed, char* name);

int deleteVertexGraph(Graph graph, char* id);

int deleteEdgeGraph(Graph graph, char* origin, char* destiny);

#endif
