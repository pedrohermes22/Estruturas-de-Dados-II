#ifndef _TXT_H_
#define _TXT_H_

#include <stdlib.h>

// Retorna um ponteiro para o arquivo temporário.
FILE *getTempTxt();

// Retorna um ponteiro para o arquivo de saída.
FILE *getOutTxt();

/*
 * Cria o arquivo temporário TXT.
 * O arquivo temporário armazenará os códigos que são inseridos ao final do SVG produzido pelas consultas.
 * Dessa forma não ocorre o problema das linhas ficarem por baixo dos retângulos, ou outros objetos.
 */
void openTempTxt(char *bsd);

// Cria o arquivo TXT com a saída dos comandos do QRY.
void openOutTxt(char *bsd, char *name);

// Fecha o arquivo "file".
void closeTxt(FILE *file);

// Escreve linhas no arquivo "file".
void writeTxt(FILE *file, char *text);

#endif