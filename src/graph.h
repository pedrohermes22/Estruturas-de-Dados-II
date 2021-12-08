#ifndef __GRAPH_H
#define __GRAPH_H

#include "list.h"
#include "hashtable.h"

typedef void* Graph;
typedef void* Vertex;
typedef void* AdjList;
typedef void* Edge;

/*
Função: Cria um grafo;
Pré: Nenhum requesito;
Pós: Retorna um void* com o grafo.
*/
Graph createGraph();

/*
Função: Apaga um grafo e seus vértices e arestas;
Pré: Um void* com o grafo;
Pós: Retorna 1 se sucesso ou 0 para falha.
*/
int destroyGraph(Graph graph);

/*
Função: Apaga um grafo;
Pré: Um void* com o grafo;
Pós: Retorna 1 se sucesso ou 0 para falha.
*/
int destroyGraphWL(Graph graph);

/*
Função: Insere um vértice no grafo;
Pré: Um void* com o grafo, um char* com o id, um double com o x, um double com o y;
Pós: Retorna 1 se sucesso ou 0 para falha.
*/
int insertVertexGraph(Graph graph, char* id, double x, double y);

/*
Função: Insere uma aresta no grafo;
Pré: Um void* com o grafo, um char* com a origem, um char* com o destino, um char* com o cep a direita, um char* com o cep a esquerda;
     Um double com o comprimento, um double com a velocidade, um char* com o nome;
Pós: Retorna 1 se sucesso ou 0 para falha.
*/
int insertEdgeGraph(Graph graph, char* origin, char* destiny, char* cepRight, char* cepLeft, double size, double speed, char* name);

/*
Função: Apaga um vértice grafo;
Pré: Um void* com o grafo, um char* com o id;
Pós: Retorna 1 se sucesso ou 0 para falha.
*/
int deleteVertexGraph(Graph graph, char* id);

/*
Função: Apaga um vértice grafo;
Pré: Um void* com o grafo, um char* com a origem, um char* com o destino;
Pós: Retorna 1 se sucesso ou 0 para falha.
*/
int deleteEdgeGraph(Graph graph, char* origin, char* destiny);

/*
Função: Busca uma instancia da lista de adjacência;
Pré: Um void* com o grafo, um char* com o id;
Pós: Retorna um void* com um nó da lista.
*/
AdjList searchVertex(Graph graph, char* id);

/*
Função: Busca uma estrutura de uma aresta;
Pré: Um void* com o nó da lista de adjacência, um char* com o destino;
Pós: Retorna um void* com a aresta.
*/
Edge searchEdge(AdjList origin, char* destiny);

/*
Função: Um algoritmo de busca de profundidade que atualiza as velocidades do comando rv;
Pré: Um void* com o grafo, um void* com a árvore minima gerada, um void* com o nó da lista de adjacência;
    Um int com a profundidade, um double com o fator original, um double com o fator, um void* com a tabela de vértices visitados;
Pós: Nenhum retorno.
*/
void dfs(Graph graph, Graph agm, AdjList adj, int cd, double fatorIn, double fator, HashTable visit);

/*
Função: Retorna o X de um vértice;
Pré: Um void* com o nó da lista de adjacência;
Pós: Retorna um double com valor.
*/
double getVertexX(AdjList adjLis);

/*
Função: Retorna o Y de um vértice;
Pré: Um void* com o nó da lista de adjacência;
Pós: Retorna um double com valor.
*/
double getVertexY(AdjList adjLis);

/*
Função: Retorna o id de um vértice;
Pré: Um void* com o nó da lista de adjacência;
Pós: Retorna um char* com valor.
*/
char* getVertexId(AdjList adjLis);

/*
Função: Retorna a quantidade de vértices no grafo;
Pré: Um void* com o grafo;
Pós: Retorna um int com valor.
*/
int getAmountVertex(Graph graph);

/*
Função: Retorna a lista de adjacência;
Pré: Um void* com o grafo;
Pós: Retorna um void* com a lista.
*/
List getAdjList(Graph graph);

/*
Função: Retorna a lista de arestas;
Pré: Um void* com o nó da lista de adjacência;
Pós: Retorna um void* com a lista.
*/
List getEdgeList(AdjList adjLis);

/*
Função: Retorna o comprimento da aresta;
Pré: Um void* com a aresta;
Pós: Retorna um double com valor.
*/
double getEdgeSize(Edge edge);

/*
Função: Retorna a velocidade da aresta;
Pré: Um void* com a aresta;
Pós: Retorna um double com valor.
*/
double getEdgeSpeed(Edge edge);

/*
Função: Retorna o destino da aresta;
Pré: Um void* com a aresta;
Pós: Retorna um char* com valor.
*/
char* getEdgeDestiny(Edge edge);

/*
Função: Retorna a origem da aresta;
Pré: Um void* com a aresta;
Pós: Retorna um char* com valor.
*/
char* getEdgeOrigin(Edge edge);

/*
Função: Retorna o nome da aresta;
Pré: Um void* com a aresta;
Pós: Retorna um char* com valor.
*/
char* getEdgeName(Edge edge);

/*
Função: Retorna a quantidade de arestas no grafo;
Pré: Um void* com o grafo;
Pós: Retorna um int com valor.
*/
int getAmountEdge(Graph graph);

/*
Função: Retorna o cep a direita da aresta;
Pré: Um void* com a aresta;
Pós: Retorna um char* com valor.
*/
char* getEdgeRightCep(Edge edge);

/*
Função: Retorna o cep a esquerda da aresta;
Pré: Um void* com a aresta;
Pós: Retorna um char* com valor.
*/
char* getEdgeLeftCep(Edge edge);

/*
Função: Altera o valor da velocidade da aresta;
Pré: Um void* com a aresta, um double com a nova velocidade;
Pós: Nenhum retorno.
*/
void setEdgeSpeed(Edge edge, double speed);

/*
Função: Verifica se a aresta é válida;
Pré: Um void* com a aresta;
Pós: Retorna 1 se for válida ou 0 caso não seja.
*/
int isEdgeValid(Edge edge);

/*
Função: Altera o estado de validação da aresta;
Pré: Um void* com a aresta;
Pós: Nenhum retorno
*/
void setEdgeValid(Edge edge, int valid);

/*
Função: Converte um digrafo em um grafo;
Pré: Um void* com o grafo;
Pós: Nenhum retorno.
*/
void convertDigraphForGraph(Graph graph);

#endif
