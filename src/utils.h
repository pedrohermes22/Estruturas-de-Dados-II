#ifndef _UTILS_H_
#define _UTILS_H_

#include "block.h"

/*
 * Retorna o caminho para o SVG com o nome correto, de acordo com o parâmetro "name".
 * Necessário desalocar a memória após usar essa função.
 */
char *getSvgPath(char *bsd, char *name);

/*
Função: Retorna a coordenada X do registrador.
Pré: Um char com a face, um int com o numero, um void* com a quadra;
Pós: Retorna um double com o valor.
*/
double getXCoordinate(char face, int number, Block block);

/*
Função: Retorna a coordenada Y do registrador.
Pré: Um char com a face, um int com o numero, um void* com a quadra;
Pós: Retorna um double com o valor.
*/
double getYCoordinate(char face, int number, Block block);

/*
Função: Retorna o vértice mais próximo de um determinado ponto
Pré: Um void* com o grafo, um double com o x, um double com o y;
Pós: Retorna um void* com um nó da lista de adjacência.
*/
AdjList getClosestVertex(Graph graph, double x, double y);

#endif