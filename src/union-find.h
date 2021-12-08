#ifndef __UNION_FIND_H
#define __UNION_FIND_H

#include "graph.h"

List createUFind(Graph graph);

void UFUnion(List unionFind, Edge edge);

#endif
