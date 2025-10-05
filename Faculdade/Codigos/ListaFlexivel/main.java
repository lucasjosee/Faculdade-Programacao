public class main
{
        public static void main(String[] args)
    {

    }

}

class Celula
{
    public int elemento;
    public Celula prox;

    public Celula()
    {
        this.elemento = 0;
        this.prox = null;
    }

    public Celula(int x)
    {
        this.elemento = x;
        this.prox = null;
    }
}

class listaFlexivel
{
    private Celula primeiro, ultimo;

    public listaFlexivel()
    {
        ultimo = primeiro = new Celula();
    }

    public void inserirFim(int x)
    {
        ultimo.prox = new Celula(x);
        ultimo = ultimo.prox;
    }

    public void inserirInicio(int x)
    {
        ultimo.prox = new Celula(x);

        Celula temp = new Celula(x);

        temp.prox = primeiro.prox;
        primeiro.prox = temp;

        if(ultimo == primeiro)
        {
            ultimo = temp;
        }

        temp = null;
    }

    public int removerFim()
    {
        if(ultimo == primeiro)
        {
            throw new RuntimeException("Erro: lista vazia");
        }

        Celula i;
        for(i = primeiro.prox; i.prox != ultimo; i = i.prox);


        int elemento = ultimo.elemento;
        ultimo = i;
        i = ultimo.prox = null;

        return elemento;
    }

    public int removerinicio()
    {
        if(ultimo == primeiro)
        {
            throw new RuntimeException("Erro: lista vazia");
        }

        Celula temp = primeiro;

        primeiro = primeiro.prox;

        int elemento = primeiro.elemento;

        temp.prox = null;
        temp = null;

        return elemento;
    }

    public int removerInicio2()
    {
        if(ultimo == primeiro)
        {
            throw new RuntimeException("Erro: lista vazia");
        }

        Celula temp = primeiro.prox;

        int elemento = temp.elemento;

        primeiro.prox = temp.prox;
        temp.prox = null;
        temp = null;

        return elemento;
    }

    public int Tamanho() 
    {
      int tamanho = 0;
      for(Celula i = primeiro; i != ultimo; i = i.prox, tamanho++);
      return tamanho;
    }

    public void inserir(int x, int pos)
    {
        if(pos < 0 || pos > tamanho)
        {
            throw new RuntimeException("Erro: posicao invalida");
        }
        else if(pos == 0)
        {
            inserirInicio(x);
        }
        else if(pos == tamanho)
        {
            inserirFinal(x);
        }
        else
        {
            Celula i = primeiro;
            for(int j = 0; j < pos; j++, i = i.prox);

            Celula temp = new Celula(x);
            temp.prox = i.prox;
            i.prox = temp;
           
            temp = null;
        }
    }

    public int removerSegundaPos()
    {
        if(ultimo == primeiro)
        {
            throw new RuntimeException("Erro: não existe segunda posição na lista");
        }

        Celula temp = primeiro.prox.prox;

        if (temp == ultimo) 
        { 
            ultimo = primeiro.prox;
        }

        int elemento = temp.elemento;
        primeiro.prox.prox = temp.prox;
        temp.prox = null;
        temp = null;

        return elemento;
    }

}

