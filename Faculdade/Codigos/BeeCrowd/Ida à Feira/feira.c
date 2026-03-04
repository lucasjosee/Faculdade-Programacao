#include <stdio.h>
#include <string.h>

typedef struct produtoAlvo
{
    char nome[100];
    int quantidade;
}produtoAlvo;

typedef struct produtoDis
{
    char nome[100];
    double preco;
}produtoDis;

double calcularPreco(produtoDis array1[], produtoAlvo array2[], int m, int p);

int main()
{
    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        int m;
        scanf("%d", &m);
        getchar();
        produtoDis pDisponivel[m];
        for(int j = 0; j < m; j++)
        {
            char linha[100];
            fgets(linha, sizeof(linha), stdin); 
            sscanf(linha, "%s %lf", pDisponivel[j].nome, &pDisponivel[j].preco);
        }
        
        int p;
        scanf("%d", &p);
        getchar();
        produtoAlvo pAlvo[p];
        for(int j = 0; j < p; j++)
        {
            char linha[100];
            fgets(linha, sizeof(linha), stdin); 
            sscanf(linha, "%s %d", pAlvo[j].nome, &pAlvo[j].quantidade);

        }
        
        printf("R$ %.2lf\n", calcularPreco(pDisponivel, pAlvo, m, p));
    }
}

double calcularPreco(produtoDis array1[], produtoAlvo array2[], int m, int p)
{
    double valor = 0.0;
    for(int i = 0; i < p; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(strcmp(array2[i].nome, array1[j].nome) == 0)
            {
                valor += array1[j].preco * array2[j].quantidade;
                break;
            }
         }
    }
    return valor;

}


                





              















