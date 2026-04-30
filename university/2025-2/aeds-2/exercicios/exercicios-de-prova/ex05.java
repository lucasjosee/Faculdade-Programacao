//Estou considerando que a função pertence a class Matriz

void removerImpares()
{
    if(this.inicio == null)
        return;

    for(CelulaMat i = this.inicio; i != null; i = i.inf)
    {
        for(CelulaMat j = i; j!= null; j = j.prox)
        {
            removerLista(j);
        }
    }
}

void removerLista(CelulaMat j)
{
    if(j.primeiro == j.ultimo)
        return;

    Celula i = j.primeiro;

    while(i.prox != null)
    {
        if(i.prox % 2 == 0)
        {
            i.prox = i.prox.prox;
        }
        else
        {
            i = i.prox;
        }
    }

    j.ultimo = i;
}
