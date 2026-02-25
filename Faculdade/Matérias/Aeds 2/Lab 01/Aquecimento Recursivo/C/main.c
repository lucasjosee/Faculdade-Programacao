#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isFIM(char* palavra);
int contarMaiusculos(char* palavra, int n);

int main()
{
	char palavra[50] ;
	fgets(palavra, 50, stdin);
	palavra[strcspn(palavra, "\n")] = '\0';
	while(!isFIM(palavra))
	{
		int n = contarMaiusculos(palavra, 0);
		printf("%d\n", n);
		fgets(palavra, 50, stdin);
		palavra[strcspn(palavra, "\n")] = '\0';
	}
}

int contarMaiusculos(char* palavra, int n)
{
	int cont = 0;
	if(n < strlen(palavra))
	{
		if(palavra[n] >= 'A' && palavra[n] <= 'Z')
		{
			cont = 1 + contarMaiusculos(palavra, n + 1);
		}
		else
		{
			cont = 0 + contarMaiusculos(palavra, n + 1);
		}
	}
	return cont;
}

bool isFIM(char* palavra)
{
	if(palavra[0] == 'F' && palavra[1] == 'I' && palavra[2] == 'M')
	{
		return true;
	}
	else
	{
		return false;
	}
}
