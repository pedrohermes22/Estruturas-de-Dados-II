#ifndef _UTILS_H_
#define _UTILS_H_

#include "block.h"

/*
 * Retorna o caminho para o SVG com o nome correto, de acordo com o parâmetro "name".
 * Necessário desalocar a memória após usar essa função.
 */
char *getSvgPath(char *bsd, char *name);

// Retorna a coordenada X do registrador.
double getXCoordinate(char face, int number, Block block);

// Retorna a coordenada Y do registrador.
double getYCoordinate(char face, int number, Block block);

AdjList getClosestVertex(Graph graph, double x, double y);

#endif