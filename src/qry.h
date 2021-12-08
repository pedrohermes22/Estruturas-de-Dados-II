#ifndef _QRY_H_
#define _QRY_H_

/* 
Função: Abre o arquivo QRY e chama função de leitura de parâmetros.
Pré: Um void* com a arvore, um void* com a tabela de espalhamento, um void* com o grafo, um char* com o caminho do qry;
Pós: Nenhum retorno.
*/
void openQry(Tree tree, HashTable hash, Graph graph, char *qryPath);

#endif