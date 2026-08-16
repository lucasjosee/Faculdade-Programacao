void inserir(String nome) //Era pra ser um pesquisar, mas eu sou um burro que não presta atenção no enunciado
{
    No alvo = buscarNo(raiz, nome.charAt(0));

    int chaveT1 = alvo.t1.hash(nome.length() - 1);

    if(alvo.t1.tabela[chaveT1] == null)
        alvo.t1.tabela[chaveT1] = nome;
    else
    {
        int chaveRehash = alvo.t1.rehash(nome.length() - 1);
        if(alvo.t1.tabela[chaveRehash] == null)
            alvo.t1.tabela[chaveRehash] = nome;
        else
        {
            T2 t2 = alvo.t1.t2;
            int chaveT2 = t2.hash(nome.length());
            inserirLista(t2.celulast2[chaveT2], nome);
        }
    }
}

void inserirLista(CelulaT2 a, String nome)
{
    if(a.inicio == a.fim || nome.compareTo(a.fim.palavra) > 0)
    {
        a.fim.prox = new Celula(nome);
        a.fim = a.fim.prox;
    }
    else
    {
        for(Celula i = a.inicio; i != null; i = i.prox)
        {
            if(nome.compareTo(i.prox.palavra < 0))
            {
                Celula temp = new Celula(nome);
                temp.prox = i.prox;
                i.prox = temp;
                temp = null;
            }
        }
    }

}

No buscarNo(No raiz, char letra)
{
    if(raiz == null)
        return null;
    else if(raiz.letra == letra)
        return raiz;
    else if(letra < raiz.letra)
        return buscarNo(raiz.esq, letra);
    else
        return buscarNo(raiz.dir, letra);
}
