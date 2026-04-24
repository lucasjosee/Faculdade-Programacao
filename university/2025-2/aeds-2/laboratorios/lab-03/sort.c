#include <stdio.h>

void selecao(int *array, int n, int m);
void swap(int *i, int *j);

int main()
{
    int n, m;

    scanf("%d %d", &n, &m);

    while(n != 0 && m != 0)
    {
        int array[n];

        for(int i = 0; i < n; i++)
        {
            scanf("%d", &array[i]);
        }
        selecao(array, n, m);

        printf("%d %d\n", n, m);

        for(int i = 0; i < n; i++)
        {
            printf("%d\n", array[i]); 
        }

        scanf("%d %d", &n, &m);
    }
}




void selecao(int *array, int n, int m)
{
    for (int i = 0; i < (n - 1); i++) 
    {
        int menor = i;
        for (int j = (i + 1); j < n; j++)
        {

            if(array[menor] % m > array[j] % m)
            {
                menor = j;
            }

            else if(array[menor] % m == array[j] % m) //modulos iguais
            {
                if(array[menor] % 2 != 0 && array[j] % 2 != 0) //Dois numeros impares
                {
                    if(array[menor] < array[j])
                        menor = j;
                }
                else if(array[menor] % 2 == 0 && array[j] % 2 == 0) //Dois numeros pares
                {
                    if(array[j] < array[menor])
                        menor = j;
                }
                else
                {
                    if(array[j] % 2 != 0)
                    {
                        menor = j;
                    }
                }
            }

        }
        swap(&array[menor], &array[i]);
    }
}


void swap(int *i, int *j) 
{
    int temp = *i;
    *i = *j;
    *j = temp;
}
