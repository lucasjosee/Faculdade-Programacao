int contarPalavras(String padrao)
{
    if(raiz == null)
    {
        throw new RuntimeException("Erro: Arvore vazia.");
    }

    No i = raiz;
    char alvo = padrao.charAt(0);
    while(i != null && alvo != i.letra)
    {
        if(alvo < i.letra)
        {
            i = i.esq;
        }
        else if(alvo > i.letra)
        {
            i = i.dir;
        }
    }

    if(i != null)
    {
        return contarOcorrencias(i.raiz, padrao);
    }
    else
    {
        return 0;
    }
    
}

int contarOcorrencias(No2 raiz, String palavra)
{
    int soma = 0;

    if(raiz != null)
    {
        if(palavra.length() == raiz.palavra.length())
        {
            soma++;
        }
        soma += contarOcorrencias(raiz.esq, palavra) + contarOcorrencias(raiz.dir, palavra);
    }
    return soma;
}