/*
 * Tradutor de .ula para .hex
 * Le um programa fonte no formato .ula e gera o arquivo .hex
 * que sera carregado no Arduino para execucao na ULA.
 */

#include <stdio.h>
#include <stdlib.h>

// Declaracoes antecipadas para poder usar as funcoes antes de defini-las
int meu_strlen(char* str);
int meu_strcmp(char* s1, char* s2);
void limpar_string(char* dest, char* src);
void extrair_mnemonico(char* dest, char* src);
int obter_codigo_mnemonico(char* m);

int main()
{
    // Abre o programa fonte para leitura e cria o arquivo de saida
    FILE *arquivo_entrada = fopen("testeula.ula", "r");
    FILE *arquivo_saida = fopen("testeula.hex", "w");

    if (!arquivo_entrada)
    {
        printf("Erro: Nao foi possivel abrir o arquivo testeula.ula\n");
        return 1;
    }
    if (!arquivo_saida)
    {
        printf("Erro: Nao foi possivel criar o arquivo testeula.hex\n");
        fclose(arquivo_entrada);
        return 1;
    }

    char linha_bruta[256];  // linha como lida do arquivo, com espacos e \n
    char linha_limpa[256];  // mesma linha apos remover espacos e quebras
    int numero_linha = 0;   // usado nas mensagens de erro para indicar onde falhou

    // X e Y guardam o ultimo valor atribuido a cada variavel.
    // Quando aparece um W=, usamos esses valores para montar a instrucao.
    int X = 0;
    int Y = 0;

    // Usamos uma flag em vez de break para sair do loop ao encontrar "fim."
    int fim = 0;
    while (!fim && fgets(linha_bruta, sizeof(linha_bruta), arquivo_entrada))
    {
        numero_linha++;

        // Remove espacos e quebras de linha para facilitar a comparacao
        limpar_string(linha_limpa, linha_bruta);

        // Linha em branco nao e permitida no meio do programa
        if (meu_strlen(linha_limpa) == 0)
        {
            printf("Erro: Linha em branco encontrada na linha %d.\n", numero_linha);
            fclose(arquivo_entrada);
            fclose(arquivo_saida);
            exit(1);
        }

        // "fim." encerra a traducao, tudo depois e ignorado
        if (meu_strcmp(linha_limpa, "fim.") == 0)
        {
            fim = 1;
        }
        else if (meu_strcmp(linha_limpa, "inicio:") != 0) // ignora a tag de abertura
        {
            // Toda instrucao valida termina com ';'
            int tam = meu_strlen(linha_limpa);
            if (linha_limpa[tam - 1] != ';')
            {
                printf("Erro: Faltando ';' na linha %d.\n", numero_linha);
                fclose(arquivo_entrada);
                fclose(arquivo_saida);
                exit(1);
            }

            if (linha_limpa[0] == 'X' && linha_limpa[1] == '=')
            {
                // Atualiza X; o valor so vai para o .hex quando vier um W=
                X = atoi(&linha_limpa[2]);
            }
            else if (linha_limpa[0] == 'Y' && linha_limpa[1] == '=')
            {
                // Mesmo comportamento do X: guarda o valor ate o proximo W=
                Y = atoi(&linha_limpa[2]);
            }
            else if (linha_limpa[0] == 'W' && linha_limpa[1] == '=')
            {
                char mnemonico[50];
                extrair_mnemonico(mnemonico, linha_limpa); // pega so o nome, sem "W=" e sem ";"

                int S = obter_codigo_mnemonico(mnemonico);
                if (S == -1)
                {
                    // Mnemonico digitado errado ou nao existe na tabela da ULA
                    printf("Erro: Mnemonico '%s' invalido na linha %d.\n", mnemonico, numero_linha);
                    fclose(arquivo_entrada);
                    fclose(arquivo_saida);
                    exit(1);
                }

                // Grava a instrucao no .hex: X, Y e S cada um como 1 digito hex
                fprintf(arquivo_saida, "%X%X%X\n", X, Y, S);
            }
        }
    }

    printf("Compilacao bem-sucedida! Arquivo testeula.hex gerado.\n");

    fclose(arquivo_entrada);
    fclose(arquivo_saida);

    return 0;
}

// Conta o tamanho de uma string sem usar strlen da biblioteca
int meu_strlen(char* str)
{
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}

// Compara duas strings caractere a caractere, igual ao strcmp padrao
int meu_strcmp(char* s1, char* s2)
{
    // Avanca enquanto os caracteres forem iguais e nao chegar no fim
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    // Se forem iguais, a subtracao retorna 0
    return *s1 - *s2;
}

// Copia src para dest pulando espacos, tabs e quebras de linha
void limpar_string(char* dest, char* src)
{
    int i = 0, j = 0;
    while (src[i] != '\0')
    {
        // So copia o caractere se nao for um separador
        if (src[i] != ' ' && src[i] != '\n')
        {
            dest[j] = src[i];
            j++;
        }
        i++;
    }
    dest[j] = '\0'; // termina a string corretamente
}

// Extrai o mnemonico de uma linha no formato "W=Mnemonico;"
void extrair_mnemonico(char* dest, char* src)
{
    int i = 2; // pula o "W="
    int j = 0;
    while (src[i] != ';' && src[i] != '\0')
    {
        dest[j] = src[i];
        i++;
        j++;
    }
    dest[j] = '\0';
}

// Converte o nome do mnemonico para o codigo hex da instrucao da ULA.
// Retorna -1 se o mnemonico nao existir na tabela.
int obter_codigo_mnemonico(char* m)
{
    // Cada mnemonico corresponde a uma operacao logica diferente na ULA
    if (meu_strcmp(m, "CopiaA") == 0) return 0x0;  // W = X
    if (meu_strcmp(m, "CopiaB") == 0) return 0x1;  // W = Y
    if (meu_strcmp(m, "AxB") == 0) return 0x2;     // W = X XOR Y
    if (meu_strcmp(m, "nAxnB") == 0) return 0x3;   // W = XNOR(X, Y)
    if (meu_strcmp(m, "AeBn") == 0) return 0x4;    // W = NAND(X, Y)
    if (meu_strcmp(m, "nB") == 0) return 0x5;      // W = NOT Y
    if (meu_strcmp(m, "nAonB") == 0) return 0x6;   // W = (NOT X) OR (NOT Y)
    if (meu_strcmp(m, "nA") == 0) return 0x7;      // W = NOT X
    if (meu_strcmp(m, "AonB") == 0) return 0x8;    // W = X OR (NOT Y)
    if (meu_strcmp(m, "UmL") == 0) return 0x9;     // W = 1111 (todos os bits em 1)
    if (meu_strcmp(m, "ZeroL") == 0) return 0xA;   // W = 0000 (todos os bits em 0)
    if (meu_strcmp(m, "AeB") == 0) return 0xB;     // W = X AND Y
    if (meu_strcmp(m, "nAeB") == 0) return 0xC;    // W = (NOT X) AND Y
    if (meu_strcmp(m, "AenB") == 0) return 0xD;    // W = X AND (NOT Y)
    if (meu_strcmp(m, "AoB") == 0) return 0xE;     // W = X OR Y
    if (meu_strcmp(m, "nAenB") == 0) return 0xF;   // W = NOR(X, Y)
    return -1;
}
