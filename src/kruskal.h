#ifndef _KRUSKAL_H_
#define _KRUSKAL_H_

#include "graph.h"

Graph areaVertices(Graph graph, double x, double y, double width, double height);

void sorting(List edges, int origin, int destiny);

List createListEdge(Graph graph);

List kruskal(Graph graph);

#endif