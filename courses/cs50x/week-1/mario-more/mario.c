#include <stdio.h>

void construirPiramide(int n);

int main()
{
    int n;
    scanf("%d", &n);

    construirPiramide(n);
}

void construirPiramide(int n)
{
    for(int i = n; i > 0; i--)
    {
        for(int j = 0; j < i - 1; j++)
        {
            printf(" ");
        }
        for(int j = n; j >= i; j--)
        {
            printf("#");
        }

        printf("  ");

        for(int j = n; j >= i; j--)
        {
            printf("#");
        }

        for(int j = 0; j < i - 1; j++)
        {
            printf(" ");
        }

        printf("\n");
    }
}