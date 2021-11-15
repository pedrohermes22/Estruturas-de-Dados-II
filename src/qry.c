#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Executa comando "@o?".
void oCommand(char cep[], char face, int number) {
}

// Executa comando "catac".
void catacCommand(double x, double y, double width, double height) {
}

// Executa comando "rv".
void rvCommand(double x, double y, double width, double height, double factor) {
}

// Executa comando "cx".
void cxCommand(char limiar[]) {
}

// Executa comando "p?".
void pCommand(char cep[], char face, int number, char shortest[], char fastest[]) {
}

// Lê os argumentos do arquivo ".qry".
void readQryArguments(FILE *qryFile) {
    char command[50], line[200], trash[10], limiar[100];  // << Corrigir o "limiar".
    char cep[100], face, shortest[50], fastest[50];
    int number;
    double x, y, width, height, factor;

    while (fgets(line, sizeof(line), qryFile) != NULL) {
        // Comando "@o?".
        if (strncmp(line, "@o? ", 4) == 0) {
            sscanf(line, "%s %s %c %d", trash, cep, &face, &number);
        }

        // Comando "catac".
        if (strncmp(line, "catac ", 6) == 0) {
            sscanf(line, "%s %lf %lf %lf %lf", trash, &x, &y, &width, &height);
        }

        // Comando "rv".
        if (strncmp(line, "rv ", 3) == 0) {
            sscanf(line, "%s %lf %lf %lf %lf %lf", trash, &x, &y, &width, &height, &factor);
        }

        // Comando "cx".
        if (strncmp(line, "cx ", 3) == 0) {
            sscanf(line, "%s %s", trash, limiar);
        }

        // Comando "p?".
        if (strncmp(line, "p? ", 3) == 0) {
            sscanf(line, "%s %s %c %d %s %s", trash, cep, &face, &number, shortest, fastest);
        }
    }
}

// Abre o arquivo ".qry" e chama função de leitura de parâmetros.
void openQry(char qryPath[]) {
    FILE *qryFile = fopen(qryPath, "r");

    if (qryFile == NULL)
        return;

    readQryArguments(qryFile);
    fclose(qryFile);
}