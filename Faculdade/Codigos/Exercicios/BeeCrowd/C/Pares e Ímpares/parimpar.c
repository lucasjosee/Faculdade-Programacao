#include <stdio.h>
#include <stdlib.h>

int* juntar(int array1[], int tam1, int array2[], int tam2);
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

    int *result = juntar(par, j, impar, k);

    for(int f = 0; f < n; f++)
    {
        printf("%d\n", result[f]);
    }

    free(result);
}

int* juntar(int array1[], int tam1, int array2[], int tam2)
{
    int *result = (int*) malloc((tam1 + tam2) * sizeof(int));

    int i;
    for(i = 0; i < tam1; i++)
    {
        result[i] = array1[i];
    }
    
    for(int f = 0; f < tam2; f++)
    {
        result[i + f] = array2[f];
    }

    return result;
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















