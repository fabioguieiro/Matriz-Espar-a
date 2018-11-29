#include <stdio.h>
#include <stdlib.h>
#include "matriz_esparsa.h"


int startHead(matriz_esparsa *matriz){
    int i=0;

    tipo_celula *cabeca;
    cabeca = (tipo_celula*)malloc(sizeof(tipo_celula));

    if (!cabeca){
        return 0;
    }

    cabeca->coluna = -1;
    cabeca->linha = -1;

    matriz->inicio = cabeca;
    matriz->fimLinha = cabeca;
    matriz->fimColuna = cabeca;

    for (i = 1; i <= matriz->col; i++){ //cabecas colunas, | | | |
        setCollumHead(matriz);
    }
    for (i = 1; i <= matriz->lin; i++){ //cabecas linhas
        rowHead(matriz);
    }
    return 1;
}

int setCollumHead(matriz_esparsa *matriz){ //cabecas colunas, | | | |
    tipo_celula *cabeca;
    cabeca = (tipo_celula*)malloc(sizeof(tipo_celula));

    if (!cabeca){
        return 0;

    }

    cabeca->coluna = -1;
    cabeca->linha = 0;

    matriz->fimColuna->direita = cabeca;
    matriz->fimColuna = cabeca;

    cabeca->direita = matriz->inicio;
    cabeca->abaixo = cabeca;
    return 1;
}
int imprimeMatriz(matriz_esparsa *matriz){
    int i, j;
    tipo_celula *pCelula;

    if (!matriz || !matriz->lin || !matriz->col){
        return 0;
    }

    pCelula = matriz->inicio->abaixo;

    printf("\n");
    printf("__________________________________\n");
    for (i = 1; i <= matriz->lin; i++){
        for (j = 1; j <= matriz->col; j++){
            if (pCelula->direita->linha == i && pCelula->direita->coluna == j){
                pCelula = pCelula->direita;
                printf("| %0.2f |", pCelula->valor);
            }
            else{
                printf("| %0.2f | ", 0.0F);
            }
        }
        printf("\n");
        printf("____________________________________\n");
        pCelula = pCelula->direita->abaixo;
    }

    return 1;
}

matriz_esparsa *cria(int lin, int col){
    matriz_esparsa *matriz;
	matriz = (matriz_esparsa *)malloc(sizeof(matriz_esparsa));

	if (!matriz || lin<=0 || col<=0){
        return 0;
	}


	matriz->inicio = NULL;
	matriz->fimLinha = NULL;
	matriz->fimColuna = NULL;
	matriz->lin = lin;
	matriz->col = col;

	startHead(matriz);

	return matriz;
}

int setElem(matriz_esparsa *matriz, int linha, int coluna, float valor){
    int i;

    if (!matriz || matriz->lin <= 0 || matriz->col <= 0 || !valor){
        return 0;
    }
    if (linha>matriz->lin || coluna>matriz->col || !valor || linha < 1 || coluna < 1){
        return 0;
    }

    tipo_celula *pCelula; //celula temporaria
    tipo_celula *pCelulaColuna; //celula temporaria para coluna
    tipo_celula *pCelulaLinha; //celula temporaria para linha

    pCelula = (tipo_celula*)malloc(sizeof(tipo_celula));

    if (!pCelula){
        return 0;
    }

    pCelula->linha = linha;
    pCelula->coluna = coluna;
    pCelula->valor = valor;

    pCelulaLinha = matriz->inicio->abaixo;
    pCelulaColuna = matriz->inicio->direita;


    for (i=0; i<linha-1; i++){
        pCelulaLinha = pCelulaLinha->abaixo;
    }
    i=0;
    while (i<coluna && pCelulaLinha->direita->linha != -1){
        if (pCelulaLinha->direita->coluna > pCelula->coluna){
            pCelula->direita = pCelulaLinha->direita;
            pCelulaLinha->direita = pCelula;
        }
        else{
            pCelulaLinha = pCelulaLinha->direita;
        }
        i++;
    }
    if (pCelulaLinha->direita->linha == -1){
        pCelula->direita = pCelulaLinha->direita;
        pCelulaLinha->direita = pCelula;
    }

    for (i = 0; i < coluna-1; i++){
        pCelulaColuna = pCelulaColuna->direita;
    }
    i=0;
    while (i<linha && pCelulaColuna->abaixo->coluna != -1){
        if (pCelulaColuna->abaixo->linha > pCelula->linha){
            pCelula->abaixo = pCelulaColuna->abaixo;
            pCelulaColuna->abaixo = pCelula;
        }
        else{
            pCelulaColuna = pCelulaColuna->abaixo;
        }
        i++;
    }
    if (pCelulaColuna->abaixo->coluna == -1){
        pCelula->abaixo = pCelulaColuna->abaixo;
        pCelulaColuna->abaixo = pCelula;
    }
    return 1;
}




int apagaMatriz(matriz_esparsa *matriz){
    int i = 1;
    int j = 1;
    tipo_celula *pCelula, *aux;

    if (!matriz || !matriz->lin || !matriz->col){
        return 0;
    }

    pCelula = matriz->inicio->abaixo;
    pCelula = pCelula->direita;

    for (i = 1; i <= matriz->lin; i++){
        for (j = 1; j <= matriz->col; j++){
            if (pCelula->linha == i && pCelula->coluna == j){
                aux = pCelula;
                pCelula = pCelula->direita;
                free(aux);
            }
        }
        pCelula = pCelula->abaixo->direita;
    }
    pCelula = matriz->inicio->direita;

    for (i = 0; i < matriz->col; i++){
        aux = pCelula;
        pCelula = pCelula->direita;
        free(aux);
    }

    pCelula = matriz->inicio->abaixo;
    for (i = 0; i < matriz->lin; i++){
        aux = pCelula;
        pCelula = pCelula->abaixo;
        free(aux);
    }

    pCelula = matriz->inicio;
    free(pCelula);

    matriz->fimColuna = matriz->fimLinha = matriz->inicio = NULL;
    matriz->lin = matriz->col = 0;
    matriz = NULL;

    return 1;
}


matriz_esparsa *multiplicaMatriz(matriz_esparsa *matrizA, matriz_esparsa *matrizB){
    int i=0, j=0, k=0;
    float tot;
    matriz_esparsa *matrizC;

    if (matrizA->col != matrizB->lin){
        printf("\nNao e possivel multiplicar estaduas matrizes, o numero de colunas de A e diferente do numero de linhas de B\n");
        return NULL;
    }

    if (!matrizA || !matrizB || !matrizA->lin || !matrizA->col || !matrizB->col){
        return NULL;
    }

    matrizC = cria(matrizA->lin, matrizB->col);

    for (i = 1; i <= matrizA->lin; i++){
        for (j = 1; j <= matrizB->col; j++){
            tot = 0;
            for (k = 1; k <= matrizA->col; k++){
                tot += getIndice(matrizA,i,k) * getIndice(matrizB,k,j);
            }
            if (tot){
                setElem(matrizC,i,j,tot);
            }
        }
    }
    return matrizC;
}
matriz_esparsa *somaMatriz(matriz_esparsa *matrizA, matriz_esparsa *matrizB){
    int i, j;
    float soma;
    matriz_esparsa *matrizC;
    tipo_celula *celA, *celB;

    if (matrizA->lin != matrizB->lin || matrizA->col != matrizB->col){
        printf("\nAs matrizes nao sao do mesmo tamanho .\nNAO FOI POSSIVEL SOMAR AS MATRIZESm\n");
        return NULL;
    }

    if (!matrizA || !matrizB || !matrizA->lin || !matrizA->col){
        return NULL;
    }

    matrizC = cria(matrizA->lin, matrizB->col);

    celA = matrizA->inicio->abaixo;
    celB = matrizB->inicio->abaixo;

    for (i = 1; i <= matrizA->lin; i++){
        for (j = 1; j <= matrizA->col; j++){
            if (j == celA->direita->coluna && j == celB->direita->coluna){
                soma = celA->direita->valor + celB->direita->valor;
                if (soma){
                    setElem(matrizC, i, j, soma);
                }
                celA = celA->direita;
                celB = celB->direita;
            }
            else if (j == celA->direita->coluna){
                setElem(matrizC, i, j, celA->direita->valor);
                celA = celA->direita;
            }
            else if (j == celB->direita->coluna){
                setElem(matrizC, i, j, celB->direita->valor);
                celB = celB->direita;
            }
        }
        celA = celA->direita->abaixo;
        celB = celB->direita->abaixo;
    }

    return matrizC;
}


float getIndice(matriz_esparsa *matriz, int linha, int coluna){
    tipo_celula *cel;
    int i = 0;

    cel = matriz->inicio->direita;

    for (i = 0; i < coluna-1; i++){
        cel = cel->direita;
    }

    do{
        cel = cel->abaixo;
        if (cel->linha == linha){
            return cel->valor;
        }
    }while(cel->coluna != -1);

    return 0;
}
int rowHead(matriz_esparsa *matriz){
    tipo_celula *cabeca;
    cabeca = (tipo_celula*)malloc(sizeof(tipo_celula));

    if (!cabeca){
        return 0;
    }

    cabeca->coluna = 0;
    cabeca->linha = -1;

    matriz->fimLinha->abaixo = cabeca;
    matriz->fimLinha = cabeca;

    cabeca->abaixo = matriz->inicio;
    cabeca->direita = cabeca;

    return 1;
}
