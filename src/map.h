#ifndef _MAP_H_
#define _MAP_H_

#include "graph.h"
/*
Função: Abre o arquivo ".via" e chama função de leitura de parâmetros;
Pré: Um char[] com o caminho do mapa viario, um void* com o grafo, um FILE* com o arquivo de svg;
Pós: Nenhum retorno.
*/
void openMap(char mapPath[], Graph graph, FILE *svgFile);

#endif