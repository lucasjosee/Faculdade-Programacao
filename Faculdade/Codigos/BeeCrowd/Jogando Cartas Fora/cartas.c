#include <stdio.h>
#include <stdlib.h>

int* empilhar(int n);
int desempilhar(int pilha[], int* n);
void trocar(int pilha[], int n);

int main()
{
    int n;
    scanf("%d", &n);
    int tamanho = n;
    while(n != 0)
    {
        int* pilha = empilhar(tamanho);
        printf("Discarded cards: ");
        while(tamanho >= 2)
        {            
            printf("%d", desempilhar(pilha, &tamanho));
            if(tamanho >= 2)
            {
                printf(", ");
            }
            trocar(pilha, tamanho);   
        } 
        printf("\n");
        printf("Remaining card: %d\n", pilha[0]);
        scanf("%d", &n);
        tamanho = n;
    }
}

int* empilhar(int n)
{
    int* pilha = (int*) malloc(n * sizeof(int));

    for(int i = 1; i <= n; i++)
    {
        pilha[i - 1] = i;
    }
    return pilha;
}

int desempilhar(int pilha[], int* n)
{
    int aux = pilha[0];
    for(int i = 0; i < *n - 1; i++)
    {
        pilha[i] = pilha[i + 1];
    }
    *n -= 1;
    return aux;
}

void trocar(int pilha[], int n)
{
    int aux = pilha[0];
    for(int i = 0; i < n - 1; i++)
    {
        pilha[i] = pilha[i + 1];
    }
    pilha[n - 1] = aux;
}

