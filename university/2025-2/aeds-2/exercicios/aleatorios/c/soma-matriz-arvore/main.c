int somaMenor(Matriz* m)
{
    if(m->linha != m->coluna)
        return 0;

    CelulaMatriz* cursorDiag = m->inicio;
    
    int soma = 0;

    while(cursorDiag != NULL)
    {
        soma += buscarMenor(cursorDiag->raiz);

        if(cursorDiag->inf == NULL)
        {
            cursorDiag = NULL;
        }
        else
        {
            cursorDiag = cursorDiag->inf->dir;
        }
    }

    return soma;
}

int buscarMenor(No* raiz)
{
    int menor;
    if(raiz->esq == NULL)
        menor = raiz->elemento;
    else
    {
       menor = buscarMenor(raiz->esq);
    }
    return menor;
}
