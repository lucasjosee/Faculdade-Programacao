#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int elemento;
    struct No* dir;
    struct No* esq;
}No;

typedef struct Arvore
{
    No* root;
}Arvore;

No* newNo(int n);
Arvore* newArvore();
void inserir(Arvore* a, int n);
No* inserirRec(No* root, int n);
void caminhamento(No* root);

int main()
{
    int n = 10;
    int i;

    Arvore* a = newArvore();

    inserir(a, 3);
    inserir(a, 7);
    inserir(a, 9);
    inserir(a, 4);
    inserir(a, 2);

    caminhamento(a->root);
}

No* newNo(int n)
{
    No* temp = (No*) malloc(sizeof(No));
    temp->esq = NULL;
    temp->dir = NULL;
    temp->elemento = n;

    return temp;
}

Arvore* newArvore()
{
    Arvore* temp = (Arvore*) malloc(sizeof(Arvore));
    temp->root = NULL;

    return temp;
}

void inserir(Arvore* a, int n)
{
    a->root = inserirRec(a->root, n);
}

No* inserirRec(No* root, int n)
{
    if(root == NULL)
        root = newNo(n);
    else if(n < root->elemento)
        root->esq = inserirRec(root->esq, n);
    else if(n > root->elemento)
        root->dir = inserirRec(root->dir, n);
    
    return root;
}

void caminhamento(No* root)
{
    if(root != NULL)
    {
        printf("%d\n", root->elemento);
        caminhamento(root->esq);
        caminhamento(root->dir);
    }
}       
