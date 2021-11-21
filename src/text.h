#ifndef _TXT_H_
#define _TXT_H_

#include <stdlib.h>

// Retorna um ponteiro para o árquivo temporário.
FILE *getTempTxt();

// Retorna o caminho do arquivo temporário.
char *getTempPath();

/*
 * Cria o arquivo temporário ".txt".
 * O arquivo temporário armazenará os códigos SVG que são inseridos
 * ao final do ".svg" produzido pelas consultas.
 * Dessa forma não ocorre o problema das linhas ficarem por baixo dos
 * retângulos, ou outros objetos.
 */
void openTempTxt(char *bsd);

// Fecha o arquivo temporário ".txt", mas não o exclui.
void closeTempTxt();

// Escreve linhas no arquivo temporário ".txt".
void writeTempTxt(char *text);

#endif