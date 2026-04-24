#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool buscaLetra(char c, const char array[], int indice) 
{
    if (array[indice] == '\0') 
    {
        return false;
    }
    if (c == array[indice]) 
    {
        return true;
    }
    return buscaLetra(c, array, indice + 1);
}

bool vogaisRec(char string[], int indice) 
{
    if (string[indice] == '\0') 
    {
        return true;
    }
    if (!buscaLetra(string[indice], "AaEeIiOoUu", 0)) 
    {
        return false;
    }
    return vogaisRec(string, indice + 1);
}

bool vogais(char string[]) 
{
    if (string[0] == '\0') 
    {
        return false;
    }
    return vogaisRec(string, 0);
}

bool consoantesRec(char string[], int indice) 
{
    if (string[indice] == '\0') 
    {
        return true;
    }
    if (!buscaLetra(string[indice], "BbCcDdFfGgHhJjKkLlMmNnPpQqRrSsTtVvWwXxYyZz", 0)) 
    {
        return false;
    }
    return consoantesRec(string, indice + 1);
}

bool consoantes(char string[]) 
{
    if (string[0] == '\0') 
    {
        return false;
    }
    return consoantesRec(string, 0);
}

bool inteiroRec(char string[], int indice) 
{
    if (string[indice] == '\0') 
    {
        return true;
    }
    if (string[indice] < '0' || string[indice] > '9') 
    {
        return false;
    }
    return inteiroRec(string, indice + 1);
}

bool inteiro(char string[])
{
    if (string[0] == '\0' || string[0] == '\n') 
    {
        return false;
    }
    return inteiroRec(string, 0);
}

bool realRec(char string[], int indice, bool ponto, bool n) 
{
    if (string[indice] == '\0' || string[indice] == '\n') 
    {
        return (ponto && n);
    }
    
    if (string[indice] == '.' || string[indice] == ',') 
    {
        if (ponto) {
            return false;
        }
        return realRec(string, indice + 1, true, n);
    } else if (string[indice] >= '0' && string[indice] <= '9') 
    {
        return realRec(string, indice + 1, ponto, true);
    } else 
    {
        return false;
    }
}

bool real(char string[]) 
{
    return realRec(string, 0, false, false);
}

int main() 
{
    char string[200];

    while (true) 
    {
        if (fgets(string, 200, stdin) == NULL) 
        {
            break;
        }

        int len = strlen(string);
        if (len > 0 && string[len - 1] == '\n') 
        {
            string[len - 1] = '\0';
        }

        if (strcmp(string, "FIM") == 0) 
        {
            break;
        }

        printf("%s ", vogais(string) ? "SIM" : "NAO");
        printf("%s ", consoantes(string) ? "SIM" : "NAO");
        printf("%s ", inteiro(string) ? "SIM" : "NAO");
        printf("%s\n", real(string) ? "SIM" : "NAO");
    }

    return 0;
}
