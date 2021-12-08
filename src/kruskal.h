#ifndef _KRUSKAL_H_
#define _KRUSKAL_H_

#include "graph.h"

/*
Função: Cria um subgrafo com as arestas e vértices da respectiva área;
Pré: Um void* com o grafo, um double com o x, um double com o y, um double com a largura, um double com a altura;
Pós: Retorna um void* com o subgrafo
*/
Graph areaVertices(Graph graph, double x, double y, double width, double height);

/*
Função: Ordena as arestas de uma lista de arestas;
Pré: Um void* com a lista, um int com o indice do primeiro nó, um int com o indice do ultimo nó;
Pós: Nenhum retorno.
*/
void sorting(List edges, int origin, int destiny);

/*
Função: Cria uma lista com todas as arestas de um grafo;
Pré: Um void* com o grafo;
Pós: Retorna um void* com a lista.
*/
List createListEdge(Graph graph);

/*
Função: Cria uma lista lista de subgrafos conectados em forma de árvores;
Pré: Um void* com o grafo;
Pós: Retorna um void* com a lista.
*/
List kruskal(Graph graph);

#endif