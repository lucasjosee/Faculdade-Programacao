public boolean isAVL()
{
    if(raiz != null)
        return isAVL(raiz);
    else
    {
        System.out.println("Arvore vazia");
        return false;
    }   
}

public boolean isAVL(No raiz)
{
    if(raiz == null) return true;
    
    int fb = getAltura(raiz.dir) - getAltura(raiz.esq);
    
    if(fb < -1 || fb > 1)
    {
        return false;
    }
    
    return isAVL(raiz.esq) && isAVL(raiz.dir);
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
