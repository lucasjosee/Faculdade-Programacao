#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void balanco(char entrada[], int tamanho);

int main()
{
    char entrada[1000];

    while(fgets(entrada, 1000, stdin) != NULL)
    {
        entrada[strcspn(entrada, "\n")] = '\0';
        balanco(entrada, strlen(entrada));
    }
}

void balanco(char entrada[], int tamanho)
{
    char pilha[1000];
    int topo = -1;

    for(int i = 0; i < tamanho; i++)
    {
        if(entrada[i] == '(')
        {
            topo++;
            pilha[topo] = '(';
        }
        else if(entrada[i] == ')')
        {
            if(topo == -1)
            {
                printf("incorrect\n");
                return;
            }
            topo--;
        }
    }
    if(topo == -1)
        printf("correct\n");
    else
        printf("incorrect\n");
}
