/*
 * Exercício: 1087 - Dama
 * Autor: Lucas José Souza Rodrigues
 * Data: 12/03/2026
 *
 * Resumo do programa:
 * O programa lê a posição de origem e de destino de uma
 * dama em um tabuleiro de xadrez e retorna quantidade de 
 * movimentos necessários para chegar ao destino
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x1, y1, x2, y2;

    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    while(x1 != 0)
    {
        if(x1 == x2 && y1 == y2) //Caso a dama não tenha se movido
        {
            printf("0\n");
        }
        else if(x1 == x2 || y1 == y2) //Caso a dama se mova horizontalmente ou verticalmente
        {
            printf("1\n");
        }
        else if(abs(x1 - x2) == abs(y1 - y2)) //Caso a dama se mova diagonalmente
        {
            printf("1\n");
        }
        else //A dama consegue chegar em qualquer casa do tabuleiro em no maximo dois movimentos
        {
            printf("2\n");
        }

        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    }
}


