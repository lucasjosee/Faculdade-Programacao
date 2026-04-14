public class main
{
    public static void main(String[] args)
    {
        Matriz m1 = new Matriz(3, 3);
        m1.construirMatriz();

        m1.inserirFinalLista(0, 0, 10);
        m1.inserirFinalLista(0, 0, 5);
        m1.inserirFinalLista(0, 0, 2);

        m1.inserirFinalLista(0, 1, 7);
        m1.inserirFinalLista(0, 1, 0);
        m1.inserirFinalLista(0, 1, 9);

        m1.inserirFinalLista(0, 2, 10);
        m1.inserirFinalLista(0, 2, 20);
        m1.inserirFinalLista(0, 2, 30);

        m1.inserirFinalLista(1, 0, 23);
        m1.inserirFinalLista(1, 0, 22);
        m1.inserirFinalLista(1, 0, 37);

        m1.mostrarlista(0, 0);
        System.out.println();

        m1.mostrarlista(0, 1);
        System.out.println();

        m1.mostrarlista(0, 2);
        System.out.println();

        m1.mostrarlista(1, 0);
    }
}

//Celula da matriz, cada celula tem um ponteiro primeiro e ultimo que apontam para o nó cabeça da lista 
class Celula 
{
    public Celula dir, esq, sup, inf;
    public CelulaLista primeiro, ultimo;

    public Celula()
    {
        this.dir = this.esq = this.sup = this.inf = null;
        this.ultimo = this.primeiro = new CelulaLista(); //incializando Celula da Lista
    }
}

//Celula da lista 
class CelulaLista
{
    public CelulaLista prox;
    public int elemento;

    public CelulaLista()
    {
        this.prox = null;
        this.elemento = 0;
    }
    public CelulaLista(int elemento)
    {
        this.prox = null;
        this.elemento = elemento;
    }
}

class Matriz
{
    private Celula inicio;
    private int linha, coluna;

    public Matriz()
    {
        this.inicio = null;
        this.linha = 0;
        this.coluna = 0;
    }
    public Matriz(int l, int c)
    {
        this.inicio = null;
        this.linha = l;
        this.coluna = c;
    }

    //Constroi a matriz 
    public void construirMatriz()
    {
        inicio = new Celula(); //cria a primeira celula e faz inicio apontar para ela 
        Celula colunaAtual = inicio; //ponteiro que aponta para a coluna que está sendo manipulada
        
        //Cria a primeira fileira
        for(int j = 1; j < coluna; j++) //for começa com 1 pq a primeira celula, inicio, ja foi criada
        {
            colunaAtual.dir = new Celula();
            colunaAtual.dir.esq = colunaAtual;
            colunaAtual = colunaAtual.dir;
        }

        Celula linhaCima = inicio; //ponteiro que aponta para a primeira posiçã da ultima linha criada, e será usado para ligar as celulas de cima com as de baixo. Funciona como o ponteiro inicio

        for(int i = 1; i < linha; i++) //For externo que ira executar o numero de linhas que desejamos criar, começa com um porque a primeira fileira ja foi criada anteriormente
        {
            //Esse bloco de comando cria a primeira celula da nova linha e conecta ela com a celula de cima 
            Celula novaLinha = new Celula();
            novaLinha.sup = linhaCima;
            linhaCima.inf = novaLinha;
            Celula atualCima = linhaCima.dir;
            Celula atualBaixo = novaLinha;

            for(int j = 1; j < coluna; j++) //cria o resto das celulas da linha
            {
                atualBaixo.dir = new Celula();
                atualBaixo.dir.esq = atualBaixo;

                atualBaixo.dir.sup = atualCima;
                atualCima.inf = atualBaixo.dir;

                atualBaixo = atualBaixo.dir;
                atualCima = atualCima.dir;
            }
            linhaCima = linhaCima.inf;
        }
        
    }

    //Metodo pega a posição de uma celula na posição l, c
    public Celula getCelula(int l, int c)
    {
        Celula ptr = this.inicio;

        for(int i = 0; i < l; i++)
        {
            if(ptr.inf == null)
            {
                return null;
            }

            ptr = ptr.inf;
        }

        for(int j = 0; j < c; j++)
        {
            if(ptr.dir == null)
            {
                return null;
            }

            ptr = ptr.dir;
        }

        return ptr;
    }

    //Metodo que adiciona um elemento no inicio da lista da celula[l][c]
    public void inserirInicioLista(int l, int c, int numero)
    {
        Celula alvo = getCelula(l, c);

        CelulaLista temp = new CelulaLista(numero);

        if(alvo.primeiro.prox == null)
        {
            alvo.primeiro.prox = temp;
            alvo.ultimo = temp;
        }
        else
        {
            temp.prox = alvo.primeiro.prox;
            alvo.primeiro.prox = temp;
        }

        temp = null;
    }

    //Metodo que insere no final das listas
    public void inserirFinalLista(int l, int c, int numero)
    {
        Celula alvo = getCelula(l, c);

        alvo.ultimo.prox = new CelulaLista(numero);
        alvo.ultimo = alvo.ultimo.prox;
    }

    //Metodo que remove no inicio da lista e retorna o valor removido
    public int removerInicioLista(int l, int c)
    {
        Celula alvo = getCelula(l, c);
        int elemento;

        if(alvo.primeiro == alvo.ultimo)
        {
            throw new RuntimeException("Erro: Lista vazia.");
        }

        CelulaLista temp = alvo.primeiro.prox;
        elemento = temp.elemento;
        alvo.primeiro.prox = temp.prox;
        temp.prox = null;
        temp = null;

        return elemento;
    }

    //Metodo que remove no fim da lista e retorna o valor removido
    public int removerFimLista(int l, int c)
    {
        Celula alvo = getCelula(l, c);
        int elemento;

        CelulaLista i;
        for(i = alvo.primeiro.prox; i.prox != alvo.ultimo; i = i.prox);

        elemento = alvo.ultimo.elemento;
        alvo.ultimo = i;
        i.prox = null;

        i = null;

        return elemento;
    }

    public void mostrarlista(int l, int c)
    {
        Celula alvo = getCelula(l, c);

        for(CelulaLista i = alvo.primeiro.prox; i != null; i = i.prox)
        {
            System.out.print(i.elemento + " ");
        }
    }

    public int somarLista(int l, int c)
    {
        Celula alvo = getCelula(l, c);
        int soma = 0;

        for(CelulaLista i = alvo.primeiro.prox; i != null; i = i.prox)
        {
            soma += i.elemento;
        }

        return soma;
    }
}

