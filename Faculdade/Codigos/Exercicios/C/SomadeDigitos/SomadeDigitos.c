//Aluno: Lucas José Souza Rodrigues
//Ex: Soma digitos - TP 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int somaDigito(int n) //Função recursiva
{
	if(n / 10 == 0)
	{
		return n;
	}
	
	return (n % 10) + somaDigito(n / 10); //Chamada Recursiva
}

int main()
{
	char entrada[50];
	int n;
	
	while(1)
	{
	
		fgets(entrada, 50, stdin);
		
		int len = strlen(entrada); //Pega o tamanho da string
		
		if (len > 0 && entrada[len - 1] == '\n') //Remove o '\n'
		{ 
            entrada[len - 1] = '\0';
        }
		
		if(strcmp(entrada, "FIM") == 0) //Caso oq for digitado for FIM o programa para
		{
			break;
		}
		
		n = atoi(entrada); //Converte a string para int	
		
		printf("%d\n",somaDigito(n)); //Chama a string	
	}
	
}
