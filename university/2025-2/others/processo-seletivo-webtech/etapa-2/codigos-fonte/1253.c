/*
 * Exercício: 1253 - Cifra de César
 * Autor: Lucas José Souza Rodrigues
 * Data: 12/03/2026
 *
 * Resumo do programa:
 * O programa le uma palavra criptografada pela Cifra de César e a descriptografa
*/

#include <stdio.h>
#include <string.h>

void descriptografia(char array[], int n);

int main()
{
    int testes;
    scanf("%d", &testes);
    getchar(); //limpando o buffer para que o fgets não consuma o '\n' do enter

    char palavra[55];
    int variacao;

    for(int i = 0; i < testes; i++)
    {
        fgets(palavra, 55, stdin);
        palavra[strcspn(palavra, "\n")] = '\0'; //Remocendo o \n que foi consumido pelo fgets
        
        scanf("%d", &variacao);
        getchar();

        descriptografia(palavra, variacao);
    }
}

void descriptografia(char array[], int n)
{
    for(int i = 0; array[i] != '\0'; i++)
    {
        array[i] -= n; //Fazendo o deslocamento inverso da cifra
                       
        if(array[i] < 'A') 
        {
            array[i] += 26; //Caso os avanços para a direita, na criptografia, foram suficientes para dar a volta no alfabeto, isso irá jogar a letra para o final dele. 
        }
        printf("%c", array[i]);
    }
    printf("\n");
}

