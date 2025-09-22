//Aluno: Lucas José Souza Rodrigues
//Ex: Is - TP 2

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
bool vogais(char string[])
{
    char vogais[] = {"AaEeIiOoUu"}; //Vetor com as vogais para comparar com a string
    
    bool n = false;
    
    for(int i = 0; string[i] != '\0'; i++)
    {
    	
        for(int j = 0; vogais[i] != '\0'; j++)
        {
            if(string[i] == vogais[j]) //Comparando as strings
            {
                n = true;
                break;
            }
            else
            {
                n = false;
                break;
            }
        }
    }
    
    return n;
    
}

bool consoantes(char string[])
{
	char consoantes[] = "BbCcDdFfGgHhJjKkLlMmNnPpQqRrSsTtVvWwXxYyZz"; //Vetor com as vogais para comparar com a string
	bool n = false;

    for(int i = 0; string[i] != '\0'; i++)
    {

        for(int j = 0; consoantes[i] != '\0'; j++)
        {
            if(string[i] == consoantes[j]) //Comparando as strings
            {
                n = true;
                break;
            }
            else
            {
                n = false;
                break;
            }
        }
    }
    return n;
}

bool inteiro(char string[])
{
	if (string[0] == '\0' || string[0] == '\n')
	{
		return false;
	}
    for(int i = 0; string[i] != '\0' && string[i] != '\n'; i++) //For le ate o '\0' ou '\n'
    {
       if(string[i] < '0' || string[i] > '9') //Se o elemento estiver fora do escopo de busca a função retorna falso
       {
       	return false;
	   }
	   
    }
    return true;
}

bool real(char string[])
{
    bool n = false; //É falsa enquanto não achar digito
    bool ponto = false; //É verdadeira se encontrar um ponto 

    for (int i = 0; string[i] != '\0' && string[i] != '\n'; i++) //For le ate o '\0' ou '\n'
	{
        if (string[i] == '.' || string[i] == ',') 
		{
            if (ponto)//Se ouver mais de um ponto, retorna false
			{
				return false;
			}  
            ponto = true;
        } else if (string[i] >= '0' && string[i] <= '9') //Verifica se todos os numeros da string são números
		{
            n = true;
        } 
		else 
		{
            return false;
        }
    }
    return (ponto && n);
}

int main()
{
	char string[200];
	
	while(1)
	{
		fgets(string, 200, stdin); //Le a string
		
		int len = strlen(string);
		
        if (len > 0 && string[len - 1] == '\n') { //Remove o '\n'
            string[len - 1] = '\0';
        }
		
		if(strcmp(string, "FIM") == 0) //Se FIM for digitado o programa acaba
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


