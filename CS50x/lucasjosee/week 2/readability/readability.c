#include <cs50.h>
#include <math.h>
#include <stdio.h>

void getGrade(string frase);
int getTotalSentences(string frase);
int getTotalPalavras(string frase);
int getPalavras(string frase);

int main()
{
    string frase = get_string("Text: ");

    getGrade(frase);
}

void getGrade(string frase)
{
    int palavras = getPalavras(frase);

    int totalLetras = getTotalPalavras(frase);

    int totalSentences = getTotalSentences(frase);

    float L = ((float) totalLetras / (float) palavras) * 100.0;
    float S = ((float) totalSentences / (float) palavras) * 100.0;

    float result = (0.0588 * L) - (0.296 * S) - 15.8;

    int grade = round(result);
    if (grade <= 0)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }
}

int getTotalSentences(string frase)
{
    int soma = 0;
    for (int i = 0; frase[i] != '\0'; i++)
    {
        if (frase[i] == '.' || frase[i] == '!' || frase[i] == '?')
        {
            soma++;
        }
    }
    return soma;
}

int getTotalPalavras(string frase)
{
    int soma = 0, i = 0;

    while (frase[i] != '\0')
    {
        if ((frase[i] >= 'A' && frase[i] <= 'Z') || (frase[i] >= 'a' && frase[i] <= 'z'))
        {
            soma++;
            i++;
        }
        else
        {
            i++;
        }
    }

    return soma;
}

int getPalavras(string frase)
{
    int espacos = 1;
    for (int i = 0; frase[i] != '\0'; i++)
    {
        if (frase[i] == ' ')
        {
            espacos++;
        }
    }

    return espacos;
}
