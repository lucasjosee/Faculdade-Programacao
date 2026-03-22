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
    char linha[50];

    fgets(linha, 50, stdin);
    while(!isFIM(linha))
    {
        removerQuebraLinha(linha);       
        
        int soma = somarNum(linha);
        
        printf("%d\n", soma);

        fgets(linha, 50, stdin);
    }


}

int somarNum(char s[])
{
    int soma = 0;

    for(int i = 0; i < strlength(s); i++)
        soma += s[i] - '0';

    return soma;
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
