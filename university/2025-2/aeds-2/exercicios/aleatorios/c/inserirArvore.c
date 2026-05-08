void inserir(Matriz* m, int i, int j, int x)
{
    CelulaMatriz* cursor = m->inicio;

    int k = 0;
    int f = 0;

    while(k != i)
    {
        cursor = cursor->inf;
        k++;
    }
    while(f != j)
    {
        cursor = cursor->dir;
        f++;
    }
    
    inserirArvore(cursor, x);
}

void inserirArvore(CelulaMatriz* alvo, int x)
{
    alvo->raiz = inserirArvoreRec(alvo->raiz, x);
}

No* inserirArvoreRec(No* raiz, int x)
{
    if(raiz == NULL)
    {
        raiz = (No*) malloc(sizeof(No));
        raiz->elemento = x;
    }
    else if(x > raiz->elemento)
        raiz->dir = inserirArvoreRec(raiz->dir, x);
    else
        raiz->esq = inserirArvoreRec(raiz->esq, x);
    
    return raiz;
}

