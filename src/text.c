#include <stdio.h>
#include <stdlib.h>

FILE *tempTxt = NULL;

// Retorna um ponteiro para o arquivo temporário.
FILE *getTempTxt() { return tempTxt; }

/*
 * Cria o arquivo temporário ".txt".
 * O arquivo temporário armazenará os códigos SVG que são inseridos
 * ao final do ".svg" produzido pelas consultas.
 * Dessa forma não ocorre o problema das linhas ficarem por baixo dos
 * retângulos, ou outros objetos.
 */
void openTempTxt(char *bsd) {
    if (tempTxt == NULL) {
        char *tempPath = (char *)calloc(strlen(bsd) + 15, sizeof(char));
        sprintf(tempPath, "%s/TEMP_TXT.txt", bsd);

        tempTxt = fopen(tempPath, "w");
        free(tempPath);
    }
}

// Fecha o arquivo temporário ".txt".
void closeTempTxt() {
    if (tempTxt != NULL) {
        fclose(tempTxt);
        tempTxt = NULL;
    }
}

// Escreve linhas no arquivo temporário ".txt".
void writeTempTxt(char *text) {
    if (tempTxt == NULL) return;

    fprintf(tempTxt, text);
}