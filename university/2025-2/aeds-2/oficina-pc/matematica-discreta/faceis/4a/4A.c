#include <stdio.h>

int main()
{
    int n[4];

    int maior = 0;

    for(int i = 0; i < 4; i++)
    {
        scanf("%d", &n[i]);
        if(n[i] > n[maior])
            maior = i;
    }
    

}
                    

