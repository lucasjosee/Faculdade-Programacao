CelulaDupla diagUnificada()
{
    if(linha != coluna) //matriz não é quadratica
        return null;

    CelulaDupla inicioDupla = new CelulaDupla();
    CelulaDupla fimDupla = inicioDupla;

    CelulaMatriz cursorMatriz = inicio;

    while(cursorMatriz != null)
    {
        Celula cursorSimples = cursorMatriz.inicio.prox;
        while(cursorSimples != null)
        {
            CelulaDupla temp = new CelulaDupla();
            temp.elemento = cursorSimples.elemento;

            fimDupla.prox = temp;
            temp.ant = fimDupla;
            temp = null;
            fimDupla = fimDupla.prox;

            cursorSimples = cursorSimples.prox;
        }
        cursorMatriz = cursorMatriz.inf;
        if(cursorMatriz != null)
            cursorMatriz = cursorMatriz.dir;
    }   

    return inicioDupla;
}
