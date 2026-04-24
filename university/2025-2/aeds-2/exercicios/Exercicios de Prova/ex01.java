CelulaLista maiorPilha()
{
    int maior = 0, cont;
    CelulaLista maiorCelula = inicio;
    for(CelulaLista i = inicio; i != null; i = i.prox)
    {
        cont = 0;
        for(CelulaPilha j = i.topo; j != null; j = j.prox)
        {
            cont++;
        }
        if(cont > maior)
        {
            maior = cont;
            maiorCelula = i;

        }
    }
    return maiorCelula;
}
