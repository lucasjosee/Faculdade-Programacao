public int contarNosNaoBalanceados()
{
    return contarNosNaoBalanceado(raiz);
}

public int contarNosNaoBalanceados(No raiz)
{
    if(raiz == null) return 0;

    int fb = getAltura(raiz.dir) - getAltura(raiz.esq);
    int soma = 0;
    if(fb < -1 || fb > 1)
    {
        soma = 1 + contarNosNaoBalanceados(raiz.esq) + contarNosNaoBalanceados(raiz.dir);
    }
    else
    {
        soma = 0 + contarNosNaoBalanceados(raiz.esq) + contarNosNaoBalanceados(raiz.dir);
    }

    return soma;
}

int getAltura(No raiz)
{
    if(raiz == null) return 0;
    return 1 + maior(getAltura(raiz.esq), getAltura(raiz.dir));
}

int maior(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}
