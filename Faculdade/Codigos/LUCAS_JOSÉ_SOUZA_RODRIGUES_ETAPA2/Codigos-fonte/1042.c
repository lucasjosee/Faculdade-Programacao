/*
 * Exercício: 1042 - Sort Simples
 * Autor: Lucas José Souza Rodrigues
 * Data: 11/03/2026
 *
 * Resumo do programa:
 * Programa lê uma certa quantidade de valores definida pela variavel tamanho 
 * e ordena de maneira crescente usando o bubble sort
*/

#include <stdio.h>

void imprimirArray(int array[], int n);
void sort(int array[], int n);
void swap(int *i, int *j);


int main()
{
    int tamanho = 3;
    int entrada[tamanho];

    int copia[tamanho]; //Cópia do array para imprimir depois da ordenação

    for(int i = 0; i < tamanho; i++) //lendo entrada
    {
        scanf("%d", &entrada[i]);
        copia[i] = entrada[i];
    }

    sort(entrada, tamanho);
    
    imprimirArray(entrada, tamanho);

    printf("\n");

    imprimirArray(copia, tamanho);

}

void sort(int array[], int n) //bubble sort 
{
    int i, j;
    for (i = 0; i < (n-1); i++) 
    {
        for (j = 0; j < (n-1); j++) 
        {
            if (array[j] > array[j + 1]) 
            {
                swap(&array[j], &array[j + 1]);
            }
        }
    }
}

void swap(int *i, int *j) //função que troca os valores do array
{
    int temp = *i;
    *i = *j;
    *j = temp;
}

void imprimirArray(int array[], int n) //função que imprime o array
{
    for(int i = 0; i < n; i++)
    {
        printf("%d\n", array[i]);
    }
}
