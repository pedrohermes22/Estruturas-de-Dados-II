#ifndef _UTILS_H_
#define _UTILS_H_

/*
 * Retorna o caminho para o SVG com o nome correto, de acordo com o parâmetro "name".
 * Necessário desalocar a memória após usar essa função.
 */
char *getSvgPath(char *bsd, char *name);

#endif