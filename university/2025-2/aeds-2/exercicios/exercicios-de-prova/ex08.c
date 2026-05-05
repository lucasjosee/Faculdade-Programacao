void removerUltimaColuna(Matriz* matriz)
{
    if(matriz->inicio == NULL)
        return;

    for(Celula i = matriz->inicio; i != null; i = i->inf)
    {
        Celula j = i;
        for(; j ->prox != null; j = j->prox);
        
        j->ant->prox = NULL;
        j->ant = NULL;
        j->sup = NULL;
        j->inf = NULL;
    }

}
