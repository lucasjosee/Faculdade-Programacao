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
        balanco(entrada, 1000);
    }
}

void balanco(char entrada[], int tamanho)
{
    int flag = 1;

    for(int i = 0; i < tamanho - 1; i++)
    {
        if(entrada[i] == '(')
        {
            for(int j = i + 1; j < tamanho; j++)
            {
                if(entrada[j] == ')')
                {
                    entrada[j] = 1;
                    flag = 0;
                    j = tamanho;
                }
                else
                {
                    flag = 1;
                }
            }
            if(flag == 1)
            {
                printf("incorrect\n");
                i = tamanho;
            }
        }
        if(entrada[i] == ')')
        {
            flag = 1;
            i = tamanho;
            printf("incorrect\n");
        }
    }
    if(flag == 0)
    {
        printf("correct\n");
    }
}
