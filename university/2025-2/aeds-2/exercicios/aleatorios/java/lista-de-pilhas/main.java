CelulaLista maiorPilha()
{
    if(inicio == fim)
    {
        throw new RuntimeException("Erro: Lista vazia");
    }

    CelulaLista maiorCel == null;
    int maiorCont = -1;
    
    for(CelulaLista i = inicio; i != null; i = i.prox)
    {
        if(i.topo != null)
        {
            int cont = 1;
            for(CelulaPilha j = i.topo.prox; j != null; j = j.prox)
            {
                cont++;
            }
            if(cont > maiorCont)
            {
                maiorCont = cont;
                maiorCel = i;
            }
        }
    }
    return maiorCel;
}