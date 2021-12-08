#ifndef __UNION_FIND_H
#define __UNION_FIND_H

#include "graph.h"

/*
Função: Cria uma lista com grafos que serve como base para o Union-Find;
Pré: Um void* com grafo;
Pós: Retorna um void* com a lista.
*/
List createUFind(Graph graph);

/*
Função: Une dois grafos com base em uma aresta;
Pré: Um void* com a lista, um void* com a aresta
Pós: Nenhum retorno.
*/
void UFUnion(List unionFind, Edge edge);

#endif
