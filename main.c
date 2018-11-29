#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matriz_esparsa.h"
#include "matriz.h"

int main(){
    int menu = 0, mat =0;
    char nome[255];
    matriz_esparsa *matrizA = NULL;
    matriz_esparsa *matrizB = NULL;
    matriz_esparsa *matrizC = NULL;

    do{
        printf ("\t\t***Bem vindo ao programa de matrizes esparsas***");
        printf("\n\n\nDigite 1 para Ler Matriz");
        printf("\nDigite 2 para Imprimir Matriz");
        printf("\nDigite 3 para Apagar Matriz");
        printf("\nDigite 4 para Somar Matrizes");
        printf("\nDigite 5 para Multiplicar Matrizes");
        printf("\nDigite 0 para Sair   ");
        scanf("%d", &menu);
        switch(menu){
            case 1:{
                printf("digite o nome da matriz [A ,B ou C\n");
                scanf(" ");
                fgets(nome,255, stdin);
                nome[strlen(nome)-1] = '\0';
                strcat(nome, ".txt"); // coloca .txt no nome da matriz, para que o usuario informe so o necessario
                printf("Digite 1 para abrir na matriz A\nDigite 2 para abria na Matriz B\n");
                scanf("%d", &mat);
                switch(mat){
                    case 1:{
                        if (matrizA){
                            apagaMatriz(matrizA);
                        }
                        matrizA = lerMatriz(nome);
                        if(matrizA == NULL){
                            printf("NÃO FOI POSSIVEL ABRIR O ARQUIVO");
                        }
                        break;
                    }
                    case 2:{
                        if (matrizB){
                            apagaMatriz(matrizB);
                        }
                        matrizB = lerMatriz(nome);
                        if(matrizB == NULL){
                            printf("NÃO FOI POSSIVEL ABRIR O ARQUIVO");
                        }
                        break;
                    }
                }
                break;
            }
            case 2:{
                printf("Digite 1 para exibir a matriz A\nDigite 2 para exibir a Matriz B\nDigite 3 para exibir a matriz C  ");
                scanf("%d", &mat);
                switch(mat){
                    case 1:{
                        if (!matrizA){
                            printf("matriz A ainda nao foi carregada\n");
                            break;
                        }
                        imprimeMatriz(matrizA);
                        break;
                    }
                    case 2:{
                        if (!matrizB){
                            printf("matriz B ainda nao foi carregada\n");
                            break;
                        }
                        imprimeMatriz(matrizB);
                        break;
                    }
                    case 3:{
                        if (!matrizC){
                            printf("matriz C ainda nao foi carregada\n");
                            break;
                        }
                        imprimeMatriz(matrizC);
                        break;
                    }
                }

                break;
            }
            case 3:{
                printf("Digite 1 para apagar a matriz A\nDigite 2 para apagar a Matriz B\nDigite 3 para apagar a matriz C  ");
                scanf("%d", &mat);
                switch(mat){
                    case 1:{
                        if(matrizA){
                            printf("apagando...\n");
                            apagaMatriz(matrizA);
                        }
                        break;
                    }
                    case 2:{
                        if (matrizB){
                            printf("apagando...\n");
                            apagaMatriz(matrizB);
                        }
                        break;
                    }
                    case 3:{
                        if (matrizC){
                            printf("apagando...\n");
                            apagaMatriz(matrizC);
                        }
                        break;
                    }
                }

                break;
            }
            case 4:{

                if (matrizA && matrizB){
                    printf("O Valor dessa soma estara armazenado na matriz C \n");
                    matrizC = somaMatriz(matrizA, matrizB);
                }

                break;
            }
            case 5:{ //Multiplicar Matrizes

                if (matrizA && matrizB){
                    printf("O Valor dessa multiplicacao estara armazenado na matriz C \n");
                    matrizC = multiplicaMatriz(matrizA, matrizB);
                }
                break;
            }

        }
    }while(menu != 0);
    printf("\n\n");
    return 0;
}
