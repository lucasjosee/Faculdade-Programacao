
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* combinador(char* p1, char* p2);
void printar(char* s);

int main()
{
	char linha[1000];
	while(fgets(linha, 1000, stdin) != NULL)
	{
		linha[strcspn(linha, "\n")] = '\0';
		
		//Arrays das duas palavras
		char p1[1000];
		char p2[1000];
		//
		
		
		if(sscanf(linha, "%s %s", p1, p2) == 2) //Fazendo a separação das palavras
		{
			char* result = combinador(p1, p2);
			printar(result);
			printf("\n");
		}	
		else
		{
			printf("Erro ao ler ao separar as strings.");
			return 1;
		}
	}
}

void printar(char* s)
{
	for(int i = 0; s[i] != '\0'; i++)
	{
		printf("%c", s[i]);
	}
}


char* combinador(char* p1, char* p2)
{
	char* result;
	result = (char*) malloc(100 * sizeof(char));
	if(result == NULL)
	{
		printf("ERRO: Memoria não alocada.\n");
		return NULL;
	}
	
	int i = 0;
	int j = 0;
	
	while(p1[i] != '\0' || p2[i] != '\0')
	{
		result[j] = p1[i];
		j++;
		result[j] = p2[i];
		j++;
		i++;
	}
	
	while(p1[i] != '\0')
	{
		result[j] = p1[i];
		j++;
		i++;
	}
	
	while(p2[i] != '\0')
	{
		result[j] = p2[i];
		j++;
		i++;
	}
	return result;
}

















