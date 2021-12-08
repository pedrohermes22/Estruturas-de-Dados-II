#ifndef _GEO_H_
#define _GEO_H_

#include "tree.h"
#include "hashtable.h"

/*
Função: Abre o arquivo GEO e chama função de leitura de parâmetros;
Pré: Um void* com a árvore, um void* com a tabela de espalhamento, um char* com o caminho de entrada;
Pós: Retorna 1 se sucesso ou 0 para falha.
*/
int openGeo(Tree tree, HashTable hash, char *geoPath);

#endif