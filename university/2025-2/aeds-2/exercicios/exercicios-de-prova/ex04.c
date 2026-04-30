Celula* encontrarRepetidos(No* raiz, CelulaMatriz* inicio)
{
    if(raiz == NULL || inicio == NULL)
        return NULL;

    Celula* cabecaLista = (Celula*) malloc(sizeof(Celula));
    cabecaLista->prox = NULL;
    
    for(CelulaMatriz* i = inicio; i != NULL; i = i->inf)
    {
        for(CelulaMatriz* j = i; j != NULL; j = j->prox)
        {
             if(temNaArvore(raiz, j->numero))
             {
                inserirOrdenado(cabecaLista, j->numero);
             }
        }
    }    
   
    
    return cabecaLista;    
}

void inserirOrdenado(Celula* cabeca, int n)
{
    Celula* cursor = cabeca;

    while(cursor->prox != NULL && n < cursor->prox->numero)
        cursor = cursor->prox;
    
    Celula* nova = (Celula*) malloc(sizeof(Celula));
    nova->numero = n;
    nova->prox = cursor->prox;
    cursor->prox = nova;

    nova = NULL;
}

int temNaArvore(No* root, int n)
{
    if(root == NULL) return 0;

    if(root->numero == n)
        return 1;
    else if(n < root->numero)
        return temNaArvore(root->esq, n);
    else
        return temNaArvore(root->dir, n);
}



