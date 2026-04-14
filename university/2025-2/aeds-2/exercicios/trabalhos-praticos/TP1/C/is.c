#include <stdio.h>

int vogal(char *str, int i);
int cons(char *str, int i);
int numInt(char *str, int i);
int numReal(char *str, int i, int cont);
int isFim(char *str);
void rql(char *s);

int main()
{
    char str[500];

    if (fgets(str, sizeof(str), stdin) != NULL)
    {
        rql(str);
    }

    while(!isFim(str))
    {
        if(vogal(str, 0))
        {
            printf("SIM ");
        }
        else
        {
            printf("NAO ");
        } 

        if(cons(str, 0))
        {
            printf("SIM ");
        }
        else
        {
            printf("NAO ");
        } 

        if(numInt(str, 0))
        {
            printf("SIM ");
        }
        else
        {
            printf("NAO ");
        } 

        if(numReal(str, 0, 0))
        {
            printf("SIM\n");
        }
        else
        {
            printf("NAO\n");
        }

        if (fgets(str, sizeof(str), stdin) != NULL)
        {
            rql(str);
        }
    }

    return 0;
}

int vogal(char *str, int i)
{
    if(str[i] == '\0')
    {
        return 1;
    }
    else if(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' ||
            str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U')
    {
        return vogal(str, i + 1);
    }
    else
    {
        return 0;
    } 
}

int cons(char *str, int i)
{
    if(str[i] == '\0')
    {
        return 1;
    }
    
    char c = str[i];
    int isLetra = ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
    int isVogal = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                   c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');

    if(isLetra && !isVogal)
    {
        return cons(str, i + 1);
    }
    else
    {
        return 0;
    } 
}

int numInt(char *str, int i)
{
    if(str[i] == '\0')
    {
        return 1;
    }
    else if(str[i] >= '0' && str[i] <= '9')
    {
        return numInt(str, i + 1);
    }
    else
    {
        return 0;
    } 
}

int numReal(char *str, int i, int cont) 
{
    if(str[i] == '\0')
    {
        return 1;
    }
    else if(str[i] == '.' || str[i] == ',')
    {
        cont++;
        if (cont > 1) 
        {
            return 0;
        }
        else
        {
            return numReal(str, i + 1, cont);
        } 
    }
    else if(str[i] >= '0' && str[i] <= '9')
    {
        return numReal(str, i + 1, cont);
    }
    else
    {
        return 0;
    } 
}

int isFim(char *str) 
{
    return (str[0] == 'F' && str[1] == 'I' && str[2] == 'M' && str[3] == '\0');
}

void rql(char *s)
{
    for(int i = 0; s[i] != '\0'; i++)
    {
        if(s[i] == '\n')
        {
            s[i] = '\0';
        }
    }
}
