// Inclui todas as funções que serão úteis ao desenvolvimento do projeto.

#include <stdio.h>

#include "block.h"

/*
 * Retorna o caminho para o SVG com o nome correto, de acordo com o parâmetro "name".
 * Necessário desalocar a memória após usar essa função.
 */
char *getSvgPath(char *bsd, char *name) {
    char *newName = extractName(name);
    char *svgName = (char *)calloc(strlen(newName) + 6, sizeof(char));
    sprintf(svgName, "%s.svg", newName);

    char *svgPath = catPath(bsd, svgName);

    free(svgName);
    free(newName);

    return svgPath;
}

// Retorna a coordenada X do registrador.
double getXCoordinate(char face, int number, Block block) {
    if (block == NULL) return -1;

    double x = getBlockX(block);

    switch (face) {
        case 'S':
            return x + number;

        case 'N':
            return x + number;

        case 'L':
            return x + (number / 2);

        case 'O':
            return x + getBlockWidth(block) - (number / 2);

        default:
            return -1;
    }
}

// Retorna a coordenada Y do registrador.
double getYCoordinate(char face, int number, Block block) {
    if (block == NULL) return -1;

    double y = getBlockY(block);

    switch (face) {
        case 'S':
            return y + (number / 2);

        case 'N':
            return y + getBlockHeight(block) - (number / 2);

        case 'L':
            return y + number;

        case 'O':
            return y + number;

        default:
            return -1;
    }
}