#include <stdio.h>

void removerQuebraLinha(char array[]);
void copiarArray(char array1[], char array2[]);
int main()
{
    int n;

    while(scanf("%d", &n) == 1)
    {   
        getchar();
        char controle[200];
        char numeroProx[200];

        fgets(controle, 200, stdin);
        removerQuebraLinha(controle);

        int cont = 0;

        for(int i = 1; i < n; i++)
        {
            fgets(numeroProx, 200, stdin);
            removerQuebraLinha(numeroProx);
                        
            int k = 0, j = 0;
            while(controle[k] != '\0')
            {
                if(controle[k] == numeroProx[j])
                {
                    cont++;
                    k++;
                    numeroProx[j] = 'a';
                    j++;
                }
                else
                {
                    k++;
                    j++;
                }
            }
            copiarArray(controle, numeroProx);
        }
        printf("%d\n", cont);
    }
}

void copiarArray(char array1[], char array2[])
{
    for(int i = 0; array1[i] != '\0'; i++)
    {
        array1[i] = array2[i];
    }
}


void removerQuebraLinha(char array[])
{
    int i;
    for(i = 0; array[i] != '\n'; i++);
    array[i] = '\0';
}
