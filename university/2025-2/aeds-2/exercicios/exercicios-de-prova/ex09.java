CelulaDupla intercalarReverso(CelulaDupla c1, CelulaDupla c2)
{
    CelulaDupla headNew = new CelulaDupla();
    CelulaDupla cursorNew = headNew;
    
    CelulaDupla cursor1 = c1.prox;
    CelulaDupla cursor2 = c2.prox;

    for(; cursor1.prox != null; cursor1 = cursor1.prox);
    for(; cursor2.prox != null; cursor2 = cursor2.prox);

    while(cursor1 != c1 && cursor1 != null && cursor2 != c2 && cursor2 != null)
    {
        CelulaDupla temp = new CelulaDupla();
        temp.elemento = cursor1.elemento;
        cursorNew.prox = temp;
        temp.ant = cursorNew;
        
        cursorNew = cursorNew.prox;
        cursor1 = cursor1.ant;

        temp = new CelulaDupla();
        temp.elemento = cursor2.elemento;
        cursorNew.prox = temp;
        temp.ant = cursorNew;
       
        cursorNew = cursorNew.prox;
        cursor2 = cursor2.ant;
            
        temp = null;
    }

    while(cursor1 != c1 && cursor1 != null)
    {
        CelulaDupla temp = new CelulaDupla();
        temp.elemento = cursor1.elemento;
        cursorNew.prox = temp;
        temp.ant = cursorNew;

        cursorNew = cursorNew.prox;

        cursor1 = cursor1.ant;
    }
    while(cursor2 != c2 && cursor2 != null)
    {
        CelulaDupla temp = new CelulaDupla();
        temp.elemento = cursor2.elemento;
        cursorNew.prox = temp;
        temp.ant = cursorNew;

        cursorNew = cursorNew.prox;

        cursor2 = cursor2.ant;
    }

    return headNew;
}
