#ifndef __DIJKSTRA_H
#define __DIJKSTRA_H

#include "graph.h"

/*
Função: Roda um algoritmo de dijkstra usando como parametro o comprimento das arestas;
Pré: Um void* com o grafo, um char* com o id do vértice de origem, um char* com o id do vértice de destino;
Pós: Retorna uma lista com os vértices na qual forma o caminho
*/
List dijkstraSize(Graph graph, char* origin, char* destiny);

/*
Função: Roda um algoritmo de dijkstra usando como parametro a velocidade das arestas;
Pré: Um void* com o grafo, um char* com o id do vértice de origem, um char* com o id do vértice de destino;
Pós: Retorna uma lista com os vértices na qual forma o caminho
*/
List dijkstraSpeed(Graph graph, char* origin, char* destiny);

#endif
