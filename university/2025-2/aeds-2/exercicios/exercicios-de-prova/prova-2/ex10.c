void meiose()
{
    if(inicio == NULL)//erro a lista ta vazia
        return;

    for(Celula* i = inicio; i != null; i = i->prox->prox)
    {
        Celula* temp  = (Celula*) malloc(sizeof(Celula);
        
        temp->elemento = i->elemento / 2;
        i->elemento = i->elemento / 2;
        temp->prox = i->prox;
        i->prox = temp;
        temp = NULL;
    }

    Celula* aux = inicio;
    while(aux->prox != NULL)
        aux = aux->prox;

    fim = aux;
}
