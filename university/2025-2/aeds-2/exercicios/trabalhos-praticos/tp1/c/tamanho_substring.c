#include <stdio.h>

int strlength(char s[]);
void removerQuebraLinha(char s[]);
int isFIM(char s[]);
int substring(char entrada[]);

int main()
{
    char entrada[50];

    fgets(entrada, 50, stdin);
    
    while(!isFIM(entrada))
    {
        removerQuebraLinha(entrada);

        int result = substring(entrada);

        printf("%d\n", result);

        fgets(entrada, 50, stdin);
    }
}

int substring(char entrada[])
{
    int n = strlength(entrada);
    int maximo = 0;
    int inicio = 0;

   
    int ultimaPosicao[256]; //Array onde cada indice é o codigo ascii de um caractere, iniciamos ele com -1
    for (int i = 0; i < 256; i++) 
    {
        ultimaPosicao[i] = -1;
    }

    for (int fim = 0; fim < n; fim++)
    {
        unsigned char c = (unsigned char)entrada[fim];

        if (ultimaPosicao[c] >= inicio)
        {
   
            inicio = ultimaPosicao[c] + 1;
        }

        // Atualizamos a última posição onde o caractere apareceu
        ultimaPosicao[c] = fim;

        
        int tamanhoJanela = fim - inicio + 1;

        if (tamanhoJanela > maximo)
        {
            maximo = tamanhoJanela;
        }
    }

    return maximo;
}

int isFIM(char s[])
{
    if(s[0] == 'F' && s[1] == 'I' && s[2] == 'M') return 1;

    return 0;
}

int strlength(char s[]) //Retorna o tamanho da string
{
    int cont = 0;
    for(int i = 0; s[i] != '\0'; i++)
        cont++;

    return cont;
}

void removerQuebraLinha(char s[]) //Remove o \n do final da string que o fgets le
{
    int i;
    for(i = 0; s[i] != '\n'; i++);

    s[i] = '\0';
}
