#include <cs50.h>
#include <stdio.h>
#include <string.h>

string compare(string p1, string p2);
int isPonto(char ponto[], char alvo, int n);

int main()
{
    string p1 = get_string("Player 1: ");
    string p2 = get_string("Player 2: ");

    string result = compare(p1, p2);

    printf("%s\n", result);
}

string compare(string p1, string p2)
{
    char umPonto[12] = {'A', 'E', 'I', 'O', 'U', 'L', 'N', 'S', 'T', 'R', '\0'};
    char doisPonto[3] = {'D', 'G', '\0'};
    char tresPonto[5] = {'B', 'C', 'M', 'P', '\0'};
    char quatroPonto[6] = {'F', 'H', 'V', 'W', 'Y', '\0'};
    char cincoPontos = 'K';
    char oitoPonto[3] = {'J', 'X', '\0'};
    char dezPonto[3] = {'Q', 'Z', '\0'};

    int soma1 = 0, soma2 = 0;

    for (int i = 0; i < strlen(p1); i++)
    {
        soma1 += isPonto(umPonto, p1[i], 1);
        soma1 += isPonto(doisPonto, p1[i], 2);
        soma1 += isPonto(tresPonto, p1[i], 3);
        soma1 += isPonto(quatroPonto, p1[i], 4);
        soma1 += isPonto(oitoPonto, p1[i], 8);
        soma1 += isPonto(dezPonto, p1[i], 10);
        if (p1[i] == cincoPontos || p1[i] == cincoPontos + 32)
        {
            soma1 += 5;
        }
    }

    for (int i = 0; i < strlen(p2); i++)
    {
        soma2 += isPonto(umPonto, p2[i], 1);
        soma2 += isPonto(doisPonto, p2[i], 2);
        soma2 += isPonto(tresPonto, p2[i], 3);
        soma2 += isPonto(quatroPonto, p2[i], 4);
        soma2 += isPonto(oitoPonto, p2[i], 8);
        soma2 += isPonto(dezPonto, p2[i], 10);
        if (p2[i] == cincoPontos || p2[i] == cincoPontos + 32)
        {
            soma2 += 5;
        }
    }

    if (soma1 == soma2)
    {
        return "Tie!";
    }
    else if (soma1 > soma2)
    {
        return "Player 1 wins!";
    }
    else
    {
        return "Player 2 wins!";
    }
}

int isPonto(char ponto[], char alvo, int n)
{
    for (int i = 0; ponto[i] != '\0'; i++)
    {
        if (alvo == ponto[i] || ponto[i] + 32 == alvo)
        {
            return n;
        }
    }
    return 0;
}
