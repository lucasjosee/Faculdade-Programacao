#include <stdio.h>

int strlength(char s[]);
void removerQuebraLinha(char s[]);
int isFIM(char s[]);
void isAnagrama(char str1[], char str2[]);

int main()
{
    char entrada[100];
    char str1[50];
    char str2[50];
    
    fgets(entrada, 100, stdin);

    while(!isFIM(entrada))
    {
        removerQuebraLinha(entrada);

        sscanf(entrada, "%s - %s", str1, str2); //sscanf separa a string linha de acordo com o formato desejado
        
        isAnagrama(str1, str2);
        // printf("%s e %s\n", str1, str2);

        fgets(entrada, 100, stdin);
    }
    
}

void isAnagrama(char str1[], char str2[])
{
    int flag = 1;

    int tamanho1 = strlength(str1), tamanho2 = strlength(str2); //Tamanho das duas strings

    //o primeiro caractere sempre é maiusculo, somando 32 no seu numero ascii ele vira minusculo
    str1[0] = str1[0] + 32; 
    str2[0] = str2[0] + 32;

    if(tamanho1 != tamanho2)
    {
        flag = 0;
    }
    else
    {
        for(int i = 0; i < tamanho1; i++)
        {
            int encontrado = 0;
            for(int j = 0; j < tamanho2; j++)
            {
                if(str1[i] == str2[j])
                {
                    str2[j] = '0'; //Substitui o caractere atual para não comparado novamente depois
                    encontrado = 1;
                    j = tamanho2; //Para o loop
                }

            }
            if(!encontrado)
            {
                flag = 0;
                i = tamanho1;
            }
        }
    }
    
    if(flag) printf("SIM\n");
    else printf("N\xc3\x83O\n"); //imprime o NÃO
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
