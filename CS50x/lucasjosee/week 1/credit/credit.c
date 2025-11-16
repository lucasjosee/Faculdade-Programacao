#include <cs50.h>
#include <stdio.h>

void verificarCartao(long int number);

int main()
{
    long int number;

    do
    {
        number = get_long("Number: ");
    }
    while (number <= 0);

    verificarCartao(number);
}

void verificarCartao(long int number)
{
    int soma1 = 0, soma2 = 0;
    int pos = 0;

    for (long int i = number; i > 0; i /= 10)
    {
        int dig = i % 10;

        if (pos % 2 == 1) // dígitos da direita em posição ímpar
        {
            dig *= 2;

            if (dig > 9)
            {
                dig = (dig % 10) + 1;
            }

            soma1 += dig;
        }
        else // dígitos em posição par soma direto
        {
            soma2 += dig;
        }

        pos++;
    }

    int length = 0;
    long int tmp = number;
    while (tmp > 0)
    {
        tmp /= 10;
        length++;
    }

    // pegar os primeiros dígitos
    long int firstTwo = number;
    while (firstTwo >= 100)
    {
        firstTwo /= 10;
    }

    long int first = number;
    while (first >= 10)
    {
        first /= 10;
    }

    if ((soma1 + soma2) % 10 == 0)
    {
        if (length == 15 && (firstTwo == 34 || firstTwo == 37))
        {
            printf("AMEX\n");
        }
        else if (length == 16 && (firstTwo >= 51 && firstTwo <= 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((length == 13 || length == 16) && first == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
