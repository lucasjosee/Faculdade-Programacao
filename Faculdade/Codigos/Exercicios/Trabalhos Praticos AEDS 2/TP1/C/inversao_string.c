/*
 * Aluno: Lucas José Souza Rodrigues
 * TP 01 - Q4
*/

#include <stdio.h>

void inverterString(char s[]);
int strlength(char s[]);
void removerQuebraLinha(char s[]);
int isFIM(char s[]);

int main()
{
    char linha[50];
    fgets(linha, 50, stdin);
    while(!isFIM(linha))
    {
        removerQuebraLinha(linha);
        
        inverterString(linha);
        printf("\n");

        fgets(linha, 50, stdin);
    }
}

int isFIM(char s[])
{
    if(s[0] == 'F' && s[1] == 'I' && s[2] == 'M') return 1;

    return 0;
}

void inverterString(char s[]) //Inverte a string
{
    int n = strlength(s);

    for(int i = n - 1; i >= 0; i--)
    {
        printf("%c", s[i]); 
    }
    
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
