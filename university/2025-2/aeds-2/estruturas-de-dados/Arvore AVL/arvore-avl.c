#include <stdio.h>

typedef struct No
{
    int num;
    int altura;
    struct No* esq;
    struct No* dir;
}No;

typedef struct Arvore
{
    No* raiz;
}Arvore;

No* newNo(int x);
Arvore* newArvore(int n);
void inserir(Arvore* a, int n);
No* inserirRec(No* raiz, int n);
No* rotacaoEsq(No* raiz);
No* rotacaoDir(No* raiz);
No* rotacaoDirEsq(No* raiz);
No* rotacaoEsqDir(No* raiz);
int calcularFb(No* raiz);
int obterAltura(No* alvo);
int maior(int a, int b);

No* newNo(int x)
{
    No* temp = (No*) malloc(sizeof(No));
    temp->num = x;
    temp->altura = 1;
    temp->esq = NULL;
    temp->dir = NULL;
    return temp;
}

Arvore* newArvore(int n)
{
    Arvore* temp = (Arvore*) malloc(sizeof(Arvore));
    temp->raiz = newNo(n);
    return temp;
}

void inserir(Arvore* a, int n)
{
    a->raiz = inserirRec(a->raiz, n);
}

No* rotacaoEsq(No* raiz)
{
    No* noDir = raiz->dir;
    No* noEsqDir = noDir->esq;

    raiz->dir = noEsqDir;
    noDir->esq = raiz;
    
    raiz->altura = 1 + maior(obterAltura(raiz->esq), obterAltura(raiz->dir);                                                                                                            
    noDir->altura = 1 + maior(obterAltura(noDir->esq), obterAltura(noDir->dir); 

    return noDir;
}   

No* rotacaoDir(No* raiz)
{
    No* noEsq = raiz->esq;
    No* noDirEsq = noEsq->dir;

    noEsq->dir = raiz;
    raiz->esq = noDirEsq;

    raiz->altura = 1 + maior(obterAltura(raiz->esq), obterAltura(raiz->dir);
    noEsq->altura = 1 + maior(obterAltura(noEsq->esq), obterAltura(noEsq->dir);

    return noEsq;
}

No* rotacaoDirEsq(No* raiz)
{
    raiz->dir = rotacaoDir(raiz->dir);
    return rotacaoEsq(raiz);
}

No* rotacaoEsqDir(No* raiz)
{
    raiz->esq = rotacaoEsq(raiz->esq);
    return rotacaoDir(raiz);
}

No* inserirRec(No* raiz, int n)
{
    if(raiz == NULL)
        raiz = newNo(n);
    else if(n < raiz->num)    
       root->esq = inserirRec(raiz->esq, n);
    else if(n > raiz->num)
        root->dir = inserirRec(raiz->dir, n);

    raiz->altura = 1 + maior(obterAltura(raiz->esq), obterAltura(raiz->dir));

    int fb = calcularFb(raiz);

    if(fb < -1 && n < raiz->esq->num)
        raiz = rotacaoDir(raiz);
    else if(fb < -1 && n > raiz->esq->num)
        raiz = rotacaoEsqDir(raiz);
    else if(fb > 1 && n > raiz->dir->num)
        raiz = rotacaoEsq(raiz);
    else if(fb > 1 && n < raiz->dir->num)
        raiz = rotacaoDirEsq(raiz); 
    
    return raiz;
}

int calcularFb(No* raiz)
{
    if(raiz == NULL) return 0;
    return obterAltura(raiz->dir) - obterAltura(raiz->esq);
}

int obterAltura(No* alvo)
{
    if(alvo == NULL)
        return 0;

    return alvo->altura;
}

int maior(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}
