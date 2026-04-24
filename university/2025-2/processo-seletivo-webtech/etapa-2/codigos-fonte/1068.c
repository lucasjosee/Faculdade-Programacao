/*
 * Exercício: 1068 - Balanço de Parênteses I
 * Autor: Lucas José Souza Rodrigues
 * Data: 13/03/2026
 *
 * Resumo do programa:
 * O programa lê uma expressão qualquer com parênteses e indica se a quantidade
 * de parênteses está correta ou não.
*/

#include <stdio.h>
#include <string.h>

void balanco(char entrada[]);

int main()
{
    char entrada[1000];

    while(fgets(entrada, 1000, stdin) != NULL)
    {
        entrada[strcspn(entrada, "\n")] = '\0';
        balanco(entrada);
    }
}

void balanco(char entrada[])
{
    char pilha[1000]; //Pilha que irá armazenar os parênteses que forem abertos
    int topo = -1;

    for(int i = 0; entrada[i] != '\0'; i++)
    {
        if(entrada[i] == '(')
        {
            topo++;
            pilha[topo] = '(';
        }
        else if(entrada[i] == ')')
        {
            if(topo == -1) //Se a pilha estiver vazia na hora que achar um ')', incorrect
            {
                printf("incorrect\n");
                return;
            }

            topo--; //Fecha os parênteses sem a necessidade de coloca-los na pilha
        }
    }

    if(topo == -1) //Se todos os parênteses forem fechados
    {
        printf("correct\n");
    }
    else //Se sobrar parênteses sem fechamento é incorrect
    {
        printf("incorrect\n");
    }
}

