/*
 * Aluno: Lucas José Souza Rodrigues
 * TP 01 - Q5
 */

#include <stdio.h>

int strlength(char s[]);
void removerQuebraLinha(char s[]);
int isFIM(char s[]);
int somarNum(char s[]);

int main()
{
    char linha[100];


    while(fgets(linha, 100, stdin) != NULL)
    {
        removerQuebraLinha(linha);       
        
        if(isFIM(linha)) 
        {
            break;
        }
        
        printf("%d\n", somarNum(linha));
    }
    return 0;
}

int somarNum(char s[])
{
    int soma = 0;
    int tam = strlength(s);
    
    for(int i = 0; i < tam; i++)
    {
        if(s[i] >= '0' && s[i] <= '9') 
        {
            soma += s[i] - '0';
        }
    }
    return soma;
}

int isFIM(char s[])
{
    if(strlength(s) == 3 && s[0] == 'F' && s[1] == 'I' && s[2] == 'M') 
    {
        return 1;
    }
    return 0;
}

int strlength(char s[]) //Retorna o tamanho da string
{
    int cont = 0;
    for(int i = 0; s[i] != '\0'; i++)
        cont++;

    return cont;
}

void removerQuebraLinha(char s[])
{
    int tamanho = strlength(s);
    
    // Remove o \n se existir no final
    if(tamanho > 0 && s[tamanho - 1] == '\n') 
    {
        s[tamanho - 1] = '\0';
        tamanho--;
    }
    
}
