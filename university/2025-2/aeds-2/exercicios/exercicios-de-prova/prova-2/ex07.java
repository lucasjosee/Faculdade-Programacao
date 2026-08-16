public void inserir(String palavra)
{
    raiz = inserir(raiz, palavra);    
}

No inserir(No raiz, String palavra)
{
    if(raiz == null)
    {
        raiz = new No();
        raiz.letra = palavra.charAt(0);
        inserirLista(raiz.primeiro, raiz.ultimo, palavra);
        return raiz;
    }
    else if(raiz.letra == palavra.charAt(0))
    {
        inserirLista(raiz.primeiro, raiz.ultimo, palavra);
    }
    else if(raiz.letra < palavra.charAt(0))
    {
        raiz.dir = inserir(raiz.dir, palavra);
    }
    else
    {
        raiz.esq = inserir(raiz.esq, palavra);
    } 

    return raiz;
}

void inserirLista(No raiz, String palavra)
{
    if(raiz.primeiro == raiz.ultimo)
    {
        Celula temp = new Celula();
        temp.palavra = palavra;

        raiz.primeiro.prox = temp;
        raiz.ultimo = temp;
        temp = null;
    }
    else if(palavra.compareTo(raiz.ultimo.palavra) > 0)
    {
        Celula temp = new Celula();
        temp.palavra = palavra;

        raiz.ultimo.prox = temp;
        raiz.ultimo = temp;
        temp = null;
    }
    else
    {
        Celula temp = new Celula();
        temp.palavra = palavra;

        Celula cursor = raiz.primeiro;
        while(cursor.prox != null && palavra.compareTo(cursor.prox.palavra) > 0)
        {
            cursor = cursor.prox;
        }
        
        temp.prox = cursor.prox;
        cursor.prox = temp;
        temp = null;
    }
}
