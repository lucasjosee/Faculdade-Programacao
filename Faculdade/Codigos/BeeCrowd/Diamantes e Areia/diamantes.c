#include <stdio.h>
#include <string.h>

int extracao(char*p);

int main()
{
    int n;
    scanf("%d", &n);
    getchar();
    for(int i = 0; i < n; i++)
    {
        char entrada[1000];
        fgets(entrada, 1000, stdin);
        entrada[strcspn(entrada, "\n")] = '\0';
    
        int resp = extracao(entrada);
        printf("%d\n", resp);
    }
    
}

int extracao(char* p)
{
    
    int cont = 0;
   
    for(int i = 0; p[i] != '\0'; i++)
    {
        if(p[i] == '<')
        {
            for(int j = i + 1; p[j] != '\0'; j++)
            {
                if(p[j] == '>')
                {
                    cont++;
                    p[j] = '.';
                    break;
                }
            }
        }
    }
    return cont;
}












