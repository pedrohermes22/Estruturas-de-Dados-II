#ifndef _SVG_H_
#define _SVG_H_

// #include <stdio.h>
#include "tree.h"

/* Abre a tag <svg>.
 *
 * FILE *svgFile: SVG alvo. */
void openSvg(FILE *svgFile);

/* Fecha a tag <svg>.
 * 
 * FILE *svgFile: SVG alvo. */
void closeSvg(FILE *svgFile);

/* Desenha as quadras.
 * 
 * Tree tree: Árvore com as quadras.
 * FILE *svgFile: SVG alvo. */
void drawBlocks(Tree tree, FILE *svgFile);

/* Desenha círculos.
 * 
 * FILE *svgFile: SVG alvo.
 * double x e double y: Coordenadas centrais.
 * double r: Raio.
 * char *fill: Cor do preenchimento. */
void drawCircle(FILE *svgFile, double x, double y, double r, char *fill);

// Desenha os pontos do grafo.
void drawDots(FILE *svgFile, Graph graph);

/* Insere as linhas do TXT temporário no SVG.
 *
 * FILE *tempTxt: TXT temporário.
 * FILE *svgFile: SVG alvo.*/
void insertTempTxt(FILE *tempTxt, FILE *svgFile);

#endif