#include <stdio.h>
#include <stdlib.h>

FILE *tempTxt = NULL;  // Armazena comandos SVG.
FILE *outTxt = NULL;   // Armazena as saídas dos comandos do QRY.

// Retorna um ponteiro para o arquivo temporário.
FILE *getTempTxt() { return tempTxt; }

// Retorna um ponteiro para o arquivo de saída.
FILE *getOutTxt() { return outTxt; }

/*
 * Cria o arquivo temporário TXT.
 * O arquivo temporário armazenará os códigos que são inseridos ao final do SVG produzido pelas consultas.
 * Dessa forma não ocorre o problema das linhas ficarem por baixo dos retângulos, ou outros objetos.
 */
void openTempTxt(char *bsd) {
    if (tempTxt == NULL) {
        char *tempPath = (char *)calloc(strlen(bsd) + 15, sizeof(char));
        sprintf(tempPath, "%s/TEMP_TXT.txt", bsd);

        tempTxt = fopen(tempPath, "w");
        free(tempPath);
    }
}

// Cria o arquivo TXT com a saída dos comandos do QRY.
void openOutTxt(char *bsd, char *name) {
    if (outTxt == NULL) {
        char *outPath = (char *)calloc(strlen(bsd) + strlen(name) + 7, sizeof(char));
        sprintf(outPath, "%s/%s.txt", bsd, name);

        outTxt = fopen(outPath, "w");
        free(outPath);
    }
}

// Fecha o arquivo "file".
void closeTxt(FILE *file) {
    if (file != NULL) fclose(file);
}

// Escreve linhas no arquivo "file".
void writeTxt(FILE *file, char *text) {
    if (file == NULL) return;

    fprintf(file, text);
}