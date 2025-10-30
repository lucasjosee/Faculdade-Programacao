#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct No
{
	struct No* dir;
	struct No* esq;
	int elemento;
}No;

typedef struct Arvore
{
	struct No* root;
}Arvore;

No* newNo(int x);
Arvore* newArvore();
void inserir(int x, Arvore* arvore);
No* inserirRec(int x, No* root);
void  caminhamento(No* root);

No* newNo(int x)
{
	No* temp = (No*) malloc(sizeof(No));
	temp->dir = NULL;
	temp->esq = NULL;
	temp->elemento = x;
	return temp;
}

Arvore* newArvore()
{
	Arvore* temp = (Arvore*) malloc(sizeof(Arvore));
	temp->root = NULL;
	return temp;
}

void inserir(int x, Arvore* arvore)
{
	arvore->root = inserirRec(x, arvore->root);
}

No* inserirRec(int x, No* root)
{
	if(root == NULL)
	{
		root = newNo(x);
	}
	
	if(x < root->elemento)
	{
		root->esq = inserirRec(x, root->esq);
	}
	if(x > root->elemento)
	{
		root->dir = inserirRec(x, root->dir);
	}
	
	return root;
}

void  caminhamento(No* root)
{
	if(root != NULL)
	{
		printf("%d ", root->elemento);
		caminhamento(root->esq);
		caminhamento(root->dir);
	}
}

int nPares(No* root)
{
	int cont = 0;
	if(root != NULL)
	{
		if(root->elemento % 2 ==  0)
		{
			cont += 1 + nPares(root->esq) + nPares(root->dir);
		}
		else
		{
			cont += 0 + nPares(root->esq) + nPares(root->dir);
		}
	}
	return cont;
}

bool arvoresIguais(No* rootA, No* rootB)
{
	bool a;
	if(rootA != NUL && rootB != NULL)
	{
		a = (rootA->elemento == rootB->elemento) && arvoresIguais(rootA->esq, rootB->esq) && arvoresIguais(rootA->dir, rootB->dir);
	}
	else if(rootA == NULL && rootB == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
	return a;
}

int main()
{
	srand(time(NULL));
	Arvore* a1 = newArvore();
	Arvore* a2 = newArvore();
	int valor, valor2;
	for(int i = 0; i < 5; i++)
	{
		valor = rand() % 100;
		valor2 = rand() % 100;
		inserir(valor, a1);
		inserir(valor2, a2);
	}
	caminhamento(a1->root);
	printf("\n");
	caminhamento(a2->root);
	
	if(arvoresIguais(a1->root, a2->root))
	{
		printf("e igual\n");
	}
	else
	{
		printf("nao e igual\n");
	}
}

