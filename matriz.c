#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include "matriz_esparsa.h"

matriz_esparsa *lerMatriz(char *nome){ //nome ou endereco do arquivo
    matriz_esparsa *matriz;
    char row[255];
    int m=0, n=0, line=0, collum=0;
    float valor=0.0;

    FILE *file;
    file = fopen(nome,"r");
    if (!file){
      file = fopen("file.txt","w");
      fprintf(file, "NÃO FOI POSSIVEL ABRIR O ARQUIVO\n");
      fclose(file);
      return NULL;
    }

    fgets(row, 255, file);
    sscanf(row, "%d %d", &m, &n);

    if (m<=0 || n<=0){
        return 0;
    }

    matriz = cria(m, n);

    while(fgets(row, 255, file)){
        sscanf(row, "%d %d %f", &line, &collum, &valor);
        if (valor){
            setElem(matriz, line, collum, valor);
        }
    }
    fclose(file);
    return matriz;
}

