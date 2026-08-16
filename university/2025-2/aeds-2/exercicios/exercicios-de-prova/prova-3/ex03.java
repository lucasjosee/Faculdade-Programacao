void inserirVeiuculo(Veiculo veiculo)
{
    No noAlvo = buscarNo(raiz, veiculo.placa.charAt(0));

    int chaveT1 = noAlvo.t1.hashT1(veiculo.placa);
    if(noAlvo.t1.tabela[chaveT1] == null)
        noAlvo.t1.tabela[chaveT1] = veiculo;
    else
    {
        int chaveRehash = noAlvo.t1.rehashT1(veiculo.placa);
        if(noAlvo.t1.tabela[chaveRehash] == null)
            noAlvo.t1.tabela[chaveRehash] = veiculo;
        else
        {
            inserirT2(veiculo, noAlvo.t1.t2);
        }
    }
}

void inserirT2(Veiculo a, T2 t2)
{
    int chave = t2.hashT2(a.chassi);
    Lista tabela = t2.tabela[chave];
    
    tabela.fim.prox = new CelulaLista(a);
    tabela.fim = tabela.fim.prox;
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
