#include <stdio.h>
#include <stdbool.h>
#include <string.h>
bool isFIM(char* palavra);
int contarMaiusculos(char* palavra);
int main()
{
	char palavra[50] ;
	fgets(palavra, 50, stdin);
	palavra[strcspn(palavra, "\n")] = '\0';
	while(!isFIM(palavra))
	{
		int n = contarMaiusculos(palavra);
		printf("%d\n", n);
		fgets(palavra, 50, stdin);
		palavra[strcspn(palavra, "\n")] = '\0';
	}
}

int contarMaiusculos(char* palavra)
{
	int n = 0;
	for(int i = 0; i < strlen(palavra); i++)
	{
		if(palavra[i] >= 'A' && palavra[i] <= 'Z')
		{
			n++;
		}
	}
	return n;
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
