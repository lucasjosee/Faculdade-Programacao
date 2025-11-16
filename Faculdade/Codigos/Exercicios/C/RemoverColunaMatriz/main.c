#include <stdio.h>
#include <stdlib.h>

void removerUltimoColuna(Celula* inicio)
{
	Celula* i, j;
	
	
	for(i = inicio; i != NULL; i = i->inf)
	{
		for(j = i; j->dir != NULL; j = j->dir);
		j->sup = NULL;
		j->dir = NULL;
		j->inf = NULL;
		j->esq = NULL;	
	}
	
	for(i = inicio; i != NULL; i = i->inf)
	{
		for(j = i; j->dir->dir != NULL; j = j->dir);
		
		free(j->dir);
	}
}
