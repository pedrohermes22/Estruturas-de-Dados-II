#ifndef _TXT_H_
#define _TXT_H_

// #include <stdlib.h>

// Retorna o ponteiro do TXT temporário.
FILE *getTempTxt();

// Retorna o ponteiro do TXT de saída.
FILE *getOutTxt();

/* Cria o TXT temporário.
 * Função: O conteúdo desse TXT será adicionado ao arquivo SVG.
 * 
 * char *bsd: Diretório de saída.*/
void openTempTxt(char *bsd);

/* Cria o TXT de saída dos comandos QRY.
 *
 * char *bsd: Diretório de saída.
 * char *name: Nome do TXT de saída. */
void openOutTxt(char *bsd, char *name);

/* Fecha o TXT. 
 * 
 * FILE *file: TXT alvo.*/
void closeTxt(FILE *file);

/* Insere linhas no TXT.
 *
 * FILE *file: TXT alvo.
 * char *text: Texto a ser escrito. */
void writeTxt(FILE *file, char *text);

#endif