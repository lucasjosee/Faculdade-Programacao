#include <stdio.h>
#include <string.h>

typedef struct palavra
{
    char portugues[80];
    char japones[80];
}palavra;

int main()
{
    int t;
    scanf("%d", &t);

    for(int i = 0; i < t; i++)
    {

        int m, n;
        scanf("%d %d", &m, &n);
        palavra dicionario[m];

        getchar();

        for(int j = 0; j < m; j++)
        {
            fgets(dicionario[j].japones, 80, stdin);
            dicionario[j].japones[strcspn(dicionario[j].japones, "\n")] = '\0';

            fgets(dicionario[j].portugues, 80, stdin);
            dicionario[j].japones[strcspn(dicionario[j].portugues, "\n")] = '\0';
        }

        char temp[80];

        for(int j = 0; j < 3; j++)
        {
            fgets(temp, 80, stdin);
            temp[strcspn(temp, "\n")] = '\0'; 

        }

    }
}

void compararString(char str1[], int tamanho1, str2[], int tamanho2)
{
    if(!strcpm(str1, str2))
    {



                    





