/*
 * Exercício: 1176 - Fibonacci em Vetor
 * Autor: Lucas José Souza Rodrigues
 * Data: 11/03/2026
 *
 * Resumo do programa:
 * Programa le um número de testes e a cada teste devolve o número exato da sequencia de fibonacci
*/

#include <stdio.h>

void preencherFib(unsigned long long array[]);

int main()
{
    unsigned long long fibonacci[61]; //Vetor de 64 bits para armazenar os números gigantescos da sequência de fibonacci
    preencherFib(fibonacci);

    int testes;
    scanf("%d", &testes);

    int n;

    for(int i = 0; i < testes; i++)
    {
        scanf("%d", &n);
        printf("Fib(%d) = %llu\n", n, fibonacci[n]); 
    }

}
        
void preencherFib(unsigned long long array[]) //Preenchendo o array de forma iterativa para evitar exeder o limite de tempo do exercício
{
    array[0] = 0;
    array[1] = 1;

    for(int i = 2; i <= 60; i++)
    {
        array[i] = array[i - 1] + array[i - 2];
    }

}
