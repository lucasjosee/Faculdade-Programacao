import java.util.Scanner;

public class ordenacaoMatriz
{
    public static void main(String[] args)
    {
        Matriz m = new Matriz(4, 4);
    }
}

class Celula
{
    int elemento;
    Celula dir, esq, sup, inf;

    public Celula(int n)
    {
        int elemento = n;
        this.dir = null;
        this.esq = null;
        this.inf = null;
        this.sup= null;
    }
}

class Matriz
{
    Celula inicio;

    int linha, coluna;

    public Matriz(int linha, int coluna)
    {
        this.linha = linha; this.coluna = coluna;

        inicio = new Celula();
        Celula nova = inicio;
        for(int j = 1; j < coluna; j++)
        {
            nova.dir = new Celula();
            nova.dir.esq = nova;
            nova = nova.dir;
        }
        
        Celula linhaAnt = inicio;

        for(int j = 1; j < linha; j++)
        {
            Celula linhaAntCursor = linhaAnt;

            Celula novaLinha = new Celula();
            novaLinha.sup = linhaAntCursor;
            linhaAntCursor.inf = novaLinha;
            linhaAntCursor = linhaAntCursor.dir;

            Celula cursor = novaLinha;
            for(int k = 1; k < coluna; k++)
            {
                Celula temp = new Celula();
                cursor.dir = temp;
                temp.esq = cursor;
                temp.sup = linhaAntCursor;
                linhaAntCursor.inf = temp;
                linhaAntCursor = linhaAnt.dir;
                cursor = temp;
            }
            linhaAnt = novaLinha;
    }   

    public inserir(int n)
    {
        
    }

    public Celula getProximo(Celula i, int linha)
    {
        Celula proximo = null;
        if(linha % 2 == 0)
        {
            if(i.dir == null)
                proximo = i.inf;
            else
                proximo = i.dir;
        }
        else
        {
            if(i.esq == null)
                proximo = i.inf;
            else
                proximo = i.esq;
        }
        return proximo;
    }

    public ordenar()
    {
        int contLinhaI = 0;
        for(Celula i = inicio; getProximo(i, contLinhaI) != null; i = getProximo(i, contLinhaI))
        {
            int contLinhaJ = contLinhaI;
            Celula menor = i;

            for(Celula j = getProximo(j, contLinhaJ); j != null; j = getProximo(j, contLinhaJ))
            {
                if(menor.elemento > j.elemento)
                {   
                    menor = j;
                }

                if(getproximo(j, contLinhaJ) = j.inf)
                    contLinhaJ++;
            }

            int temp = menor.elemento;
            menor.elemento = i.elemento;
            i.elemento;

            if(getProximo(i, contLinhaI) == i.inf)
                contLinhaI++;
           
        }
    }        

}


