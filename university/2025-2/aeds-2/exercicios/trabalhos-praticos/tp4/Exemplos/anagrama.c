/*
 * Aluno: Lucas José Souza Rodrigues
 * TP 01 - Q6 - Verificação de Anagrama
 */

#include <stdio.h>

int strlength(char s[]);
void removerQuebraLinha(char s[]);
int isFIM(char s[]);
void isAnagrama(char str1[], char str2[]);
void converterParaMinusculo(char s[]);
void extrairDuasPalavras(char entrada[], char str1[], char str2[]);

int main()
{
    char entrada[150];
    char str1[50];
    char str2[50];
    
    // Leitura inicial protegida contra fim de arquivo
    if (fgets(entrada, 150, stdin) == NULL) return 0;

    while(!isFIM(entrada))
    {
        removerQuebraLinha(entrada);

        // Substituímos o sscanf frágil por um extrator robusto
        extrairDuasPalavras(entrada, str1, str2);
        
        // Só tenta verificar anagrama se conseguiu de fato extrair algo
        if(strlength(str1) > 0 && strlength(str2) > 0)
        {
            isAnagrama(str1, str2);
        }

        // Leitura do final do loop protegida
        if (fgets(entrada, 150, stdin) == NULL) break; 
    }
    
    return 0;
}

// Extrator blindado: ignora a formatação e puxa as duas palavras brutas
void extrairDuasPalavras(char entrada[], char str1[], char str2[]) 
{
    int i = 0, j = 0;
    
    // Pula possíveis espaços iniciais
    while(entrada[i] == ' ') i++;

    // Lê str1 (para quando achar espaço ou traço)
    while(entrada[i] != '\0' && entrada[i] != ' ' && entrada[i] != '-') {
        str1[j++] = entrada[i++];
    }
    str1[j] = '\0';

    // Pula a "sujeira" do Verde (espaços e o traço, se existir)
    while(entrada[i] == ' ' || entrada[i] == '-') {
        i++;
    }

    // Lê str2 (até acabar a palavra)
    j = 0;
    while(entrada[i] != '\0' && entrada[i] != ' ' && entrada[i] != '\n' && entrada[i] != '\r') {
        str2[j++] = entrada[i++];
    }
    str2[j] = '\0';
}

void isAnagrama(char str1[], char str2[])
{
    int flag = 1;

    int tamanho1 = strlength(str1); 
    int tamanho2 = strlength(str2);

    // Converte de forma segura usando a tabela ASCII
    converterParaMinusculo(str1);
    converterParaMinusculo(str2);

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
                    str2[j] = '0'; // Marca o caractere como usado
                    encontrado = 1;
                    break; 
                }
            }
            if(!encontrado)
            {
                flag = 0;
                break; 
            }
        }
    }
    
    if(flag) printf("SIM\n");
    else printf("NAO\n");
}

int isFIM(char s[])
{
    if(strlength(s) >= 3 && s[0] == 'F' && s[1] == 'I' && s[2] == 'M') return 1;
    return 0;
}

int strlength(char s[])
{
    int cont = 0;
    for(int i = 0; s[i] != '\0'; i++)
        cont++;
    return cont;
}

void removerQuebraLinha(char s[])
{
    int tam = strlength(s);
    if(tam > 0 && s[tam - 1] == '\n') 
    {
        s[tam - 1] = '\0';
        tam--;
    }
    if(tam > 0 && s[tam - 1] == '\r') 
    {
        s[tam - 1] = '\0';
    }
}

void converterParaMinusculo(char s[])
{
    for(int i = 0; s[i] != '\0'; i++)
    {
        if(s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] = s[i] + 32;
        }
    }
}
