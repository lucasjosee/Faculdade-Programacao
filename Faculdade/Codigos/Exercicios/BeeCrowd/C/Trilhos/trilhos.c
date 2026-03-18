#include <stdio.h>

int reorganizacao(int entrada[], int n);


int main()
{
    int n;

    while(scanf("%d", &n) == 1 && n != 0)
    {
        int entrada[n];

        while (scanf("%d", &entrada[0]) == 1 && entrada[0] != 0)
        {
            for(int i = 1; i < n; i++)
            {
                scanf("%d", &entrada[i]);
            }

            if(reorganizacao(entrada, n))
            {
                printf("Yes\n");
            }
            else
            {
                printf("No\n");
            }
        } 
        printf("\n");
    }
}

int reorganizacao(int alvo[], int n)
{
    int pilha[n];
    int controle = -1;
    int vagaoA = 1;

    int i = 0;
    
    while(i < n)
    {
        if(controle != -1 && alvo[i] == pilha[controle])
        {
            controle--;
            i++;
        }
        else if(vagaoA <= n)
        {
            pilha[++controle] = vagaoA++;
        }
        else
        {
            return 0;
        }
    }
    return 1;


}

