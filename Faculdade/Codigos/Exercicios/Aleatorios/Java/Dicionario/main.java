class Dicionario
{
    private No raiz;
    public void inserir(String palavra)
    {
        char letra = palavra.length;
        No alvo = buscarLetra(raiz, letra);

        if(alvo == null)
        {
            criarNo(raiz, letra, palavra);
        }
        else
        {
            inserirLista(alvo, palavra);
        }
    }

    public void inserirLista(No alvo, String palavra)
    {
        Celula i = alvo.primeiro.prox;
        Celula j = alvo.primeiro;
        if(palavra.compareTo(alvo.primeiro.palavra) < 0)
        {
            Celula temp = new Celula(palavra);
            temp.prox = alvo.primeiro;
            alvo.primeiro = temp;
            temp = null;
        }
        else if(palavra.compareTo(alvo.ultimo) > 0)
        {
            Celula temp = new Celula(palavra);
            alvo.ultimo = temp;
            temp = null;
        }
        else
        {
            while(i != null)
            {
                if(i != null && palavra.compareTo(i.palavra) > 0)
                {
                    Celula temp = new Celula(palavra);
                    temp.prox = i;
                    j.prox = temp;
                    temp = null;

                    return;
                }

                i = i.prox;
                j = j.prox;
                
            }
        }
    }

    public void criarNo(No raiz, char letra, String palavra)
    {
        if(raiz == null)
        {
            raiz = new No(letra);
            raiz.primeiro = raiz.ultimo = new Celula(palavra);
        }
        else if(letra > raiz.letra)
        {
            raiz.dir = criarNo(raiz.dir, letra);
        }
        else if(letra < raiz.letra)
        {
            raiz.esq = criarNo(raiz.esq, letra);
        }

        return raiz;
    }

    public No buscarLetra(No raiz, letra)
    {
        if(raiz == null)
        {
            return null;
        }
        else if(raiz.letra == letra)
        {
            return raiz;
        }
        else if(letra > raiz.letra)
        {
            return buscarLetra(raiz.dir, letra);
        }
        else if(letra < raiz.letra)
        {
            return buscarLetra(raiz.esq, letra);
        }

        return raiz;
    }
}
