#ifndef _SVG_H_
#define _SVG_H_

#include <stdio.h>
#include "tree.h"

// Abre a tag <svg> no arquivo SVG.
void openSvg(FILE *svgFile);

// Fecha a tag <svg> no arquivo SVG.
void closeSvg(FILE *svgFile);

// Desenha as quadras armazenadas na árvore.
void drawBlocks(Tree tree, FILE *svgFile);

// Desenha círculos no SVG.
void drawCircle(FILE *svgFile, double x, double y, double r, char *fill);

#endif