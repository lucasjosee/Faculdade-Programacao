public class main
{
        public static void main(String[] args)
    {
        ListaDupla lista = new ListaDupla();

        lista.inserirFim(5);
        lista.inserirInicio(4);
        lista.inserirInicio(3);
        lista.inserir(10, 3);
        lista.mostrar();

        System.out.println();

        lista.removerFim();
        lista.mostrar();
    }

}

//Classe que cria a celula que ira armazenar o elemento, nele está presente o ponteiro para a proxima celula e para a anterior
class Celula
{
    public int elemento;
    public Celula prox;
    public Celula ant;

    public Celula()
    {
        this.elemento = 0;
        this.prox = null;
        this.ant = null;
    }

    public Celula(int x)
    {
        this.elemento = x;
        this.prox = null;
        this.ant = null;
    }
}

//Classe que cria a lista, nela está seus atributos e metodos
class ListaDupla
{
    private Celula primeiro, ultimo;

    public ListaDupla()
    {
        ultimo = primeiro = new Celula();
    }

    public void inserirFim(int x)
    {
        ultimo.prox = new Celula(x); //cria a proxima celula no fim
        ultimo.prox.ant = ultimo; //Faz o ponteiro ant da nova celula apontar para a celula anterior
        ultimo = ultimo.prox; //Como foi inserida uma nova celula no fim, ela deve se tornar a ultima
    }

    public void mostrar()
    {
        for(Celula i = primeiro.prox; i != null; i = i.prox)
        {
            System.out.print(i.elemento + " ");
        }
    }

    public void inserirInicio(int x)
    {
        Celula temp = new Celula(x); //celula temp é criada

        temp.ant = primeiro; //Ponteiro ant aponta para a sua celula anterior que é a primeira celula

        temp.prox = primeiro.prox; //ponteiro prox da nova celula temp aponta para a proxima celula 
        primeiro.prox = temp; //prox da celula primeiro aponta para a nova celula

        if(ultimo == primeiro)
        {
            ultimo = temp; //caso a nova celula for a primeira a ser inserida, ultimo deve apontar para ela
        }
        else
        {
            temp.prox.ant = temp; //Caso a celula não for a primeira, o ponterio ant da proxima celula deve apontar para a nova celula
        }

        temp = null;
    }

    public int removerFim()
    {
        if(ultimo == primeiro)
        {
            throw new RuntimeException("Erro: lista vazia");
        }

        int elemento = ultimo.elemento; //Armazenando elemento que será removido

        ultimo = ultimo.ant; //Ultimo passa a apontar para a celula anterior da que será removida
        
        //Desalocando os ponterios e removendo celula
        ultimo.prox.ant = null; 
        ultimo.prox = null;

        return elemento;
    }

    //Metodo "errado" porque remoce a celula cabeça
    public int removerinicioBosta()
    {
        if(ultimo == primeiro)
        {
            throw new RuntimeException("Erro: lista vazia");
        }

        Celula temp = primeiro;

        primeiro = primeiro.prox;

        int elemento = primeiro.elemento;

        temp.prox = primeiro.ant = null;

        temp.prox = null;
        temp = null;

        return elemento;
    }

    //Remove a celula fisicamente ao inves de so mudar o ponteiro primeiro
    public int removerInicio()
    {
        if(ultimo == primeiro)
        {
            throw new RuntimeException("Erro: lista vazia");
        }

        Celula temp = primeiro.prox; //temp aponta para a celula a ser removida

        int elemento = temp.elemento;

        primeiro.prox = temp.prox;
        temp.prox.ant = primeiro;

        temp.prox = null;
        temp.ant = null;
        temp = null;

        return elemento;
    }

    public int Tamanho() 
    {
        int tamanho = 0; 
        for(Celula i = primeiro.prox; i != null; i = i.prox, tamanho++); 
        return tamanho;
    }

    public void inserir(int x, int pos)
    {
        int tamanho = Tamanho();
        
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
            inserirFim(x);
        }
        else
        {
            Celula i = primeiro;
            for(int j = 0; j < pos; j++, i = i.prox); //Ponteiro i vai até o ant da posição que queremos inserir

            Celula temp = new Celula(x);
            temp.ant = i;
            temp.prox = i.prox;
            i.prox.ant = temp;
            i.prox = temp;
           
            temp = null;
        }
    }

    public void quickSort()
    {
        
    }
}