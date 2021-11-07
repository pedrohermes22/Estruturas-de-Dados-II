#ifndef __BLOCK_H
#define __BLOCK_H

typedef void* Block;

/*
Função: Cria e retorna uma quadra;
Pré: Um double com x, Um double com y, Um double com largura, Um double com altura, Um char* com cep,
Um char* com preenchimento, Um char* com borda, Um char* com largura da borda;
Pós: Retorna uma quadra.
*/
Block createBlock(double x, double y, double width, double height, char* cep, char* fill, char* stroke, char* thickness);

/*
Função: Deleta uma quadra;
Pré: Um void* com quadra;
Pós: Retorna 1 se sucesso ou 0 para falha.
*/
int destroyBlock(Block block);

/*
Função: Retorna o valor de x de uma quadra;
Pré: Um void* com quadra;
Pós: Retorna o x.
*/
double getBlockX(Block block);

/*
Função: Retorna o valor de y de uma quadra;
Pré: Um void* com quadra;
Pós: Retorna o y.
*/
double getBlockY(Block block);

/*
Função: Retorna o valor de largura de uma quadra;
Pré: Um void* com quadra;
Pós: Retorna a largura.
*/
double getBlockWidth(Block block);

/*
Função: Retorna o valor de altura de uma quadra;
Pré: Um void* com quadra;
Pós: Retorna a altura.
*/
double getBlockHeight(Block block);

/*
Função: Retorna o cep de uma quadra;
Pré: Um void* com quadra;
Pós: Retorna o cep.
*/
char* getBlockCep(Block block);

/*
Função: Retorna a cor de preenchimento de uma quadra;
Pré: Um void* com quadra;
Pós: Retorna a cor.
*/
char* getBlockFill(Block block);

/*
Função: Retorna a cor da borda de uma quadra;
Pré: Um void* com quadra;
Pós: Retorna a cor.
*/
char* getBlockStroke(Block block);

/*
Função: Retorna a espessura da borda de uma quadra;
Pré: Um void* com quadra;
Pós: Retorna a espessura.
*/
char* getBlockThickness(Block block);

#endif
