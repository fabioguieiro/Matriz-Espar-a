#ifndef MATRIZ_ESPARSA_H_INCLUDED
#define MATRIZ_ESPARSA_H_INCLUDED
typedef struct t_celula{
    struct t_celula *direita, *abaixo;
    int linha, coluna;
    float valor;
}tipo_celula;

typedef struct{
    int lin, col;
    tipo_celula *inicio, *fimLinha, *fimColuna;
}tipo_matriz_esparsa;

typedef tipo_matriz_esparsa matriz_esparsa;


matriz_esparsa *cria(int m, int n);
matriz_esparsa *lerMatriz(char *nome);
int startHead(matriz_esparsa *mat);
int rowHead(matriz_esparsa *mat);
int setCollumHead(matriz_esparsa *mat);

int setElem(matriz_esparsa *mat, int linha, int coluna, float valor);
int imprimeMatriz(matriz_esparsa *mat);
int apagaMatriz(matriz_esparsa *mat);
matriz_esparsa *somaMatriz(matriz_esparsa *matA, matriz_esparsa *matB);
matriz_esparsa *multiplicaMatriz(matriz_esparsa *matA, matriz_esparsa *matB);

float getIndice(matriz_esparsa *mat, int linha, int coluna);

#endif
