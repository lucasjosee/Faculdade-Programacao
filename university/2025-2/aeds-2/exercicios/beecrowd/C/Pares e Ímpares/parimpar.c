#include <stdio.h>
#include <stdlib.h>

void imprimir(int array[], int tam);
void ordenar(int n[], int tamanho);
void ordenarDecrescente(int n[], int tamanho);

int main()
{
    int n;
    scanf("%d", &n);

    int impar[n];
    int par[n];

    int temp;
    int i = 0, j = 0, k = 0;

    while(i < n)
    {
        scanf("%d",&temp);
        if(temp % 2 == 0)
        {
            par[j] = temp;
            i++;
            j++;
        }
        if(temp % 2 == 1)
        {
            impar[k] = temp;
            i++;
            k++;
        }
    }
    ordenar(par, j);
    ordenarDecrescente(impar, k);

    imprimir(par, j);
    imprimir(impar, k);
}

void imprimir(int array[], int tam)
{
    for(int i = 0; i < tam; i++)
    {
        printf("%d\n", array[i]);
    }
}

void ordenar(int n[], int tamanho)
{
    for(int i = 0; i < tamanho - 1; i++)
    {
        for(int j = i + 1; j < tamanho; j++)
        {
            if(n[j] < n[i])
            {
                int temp = n[j];
                n[j] = n[i];
                n[i] = temp;
            }
        }
    }
}

void ordenarDecrescente(int n[], int tamanho)
{
    for(int i = 0; i < tamanho - 1; i++)
    {
        for(int j = i + 1; j < tamanho; j++)
        {
            if(n[j] > n[i])
            {
                int temp = n[j];
                n[j] = n[i];
                n[i] = temp;
            }
        }
    }
}















