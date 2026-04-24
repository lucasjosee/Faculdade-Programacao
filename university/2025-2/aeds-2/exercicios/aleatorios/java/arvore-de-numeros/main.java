public class main
{
    public static void main(String[] args)
    {
        Arvore a1 = new Arvore();

        a1.inserirArvore(6599);
        a1.raiz.lista.inserirFinalLista("Lucas jose Souza Rodrigues");
    }
}

class Celula
{
    public Celula prox;
    public String nome;

    public Celula()
    {
        this.nome = "";
        this.prox = null;
    }

    public Celula(String n)
    {
        this.nome = n;
        this.prox = null;
    }
}

class No 
{
    public Lista lista;
    public int num;
    public No esquerda, direita;

    public No()
    {
        this.lista = null;
        this.direita = null;
        this.esquerda = null;
        this.num = 0;
    }

    public No(int num)
    {
        this.lista = new Lista();
        this.esquerda = null;
        this.direita = null;
        this.num = num;
    }
}

class Lista
{
    public Celula primeiro;
    public Celula ultimo;

    public Lista()
    {
        ultimo = primeiro = new Celula();
    }

    public void inserirFinalLista(String n)
    {
        ultimo.prox = new Celula(n);
        ultimo = ultimo.prox;
    }
}

class Arvore
{
    public No raiz;

    public Arvore()
    {
        this.raiz = null;
    }

    public void inserirArvore(int num)
    {
        raiz = inserirArvoreRec(num, raiz);
    }

    public No inserirArvoreRec(int num, No raiz)
    {
        if(raiz == null)
        {
            return raiz = new No(num);
        }
        if(num < raiz.num)
        {
            raiz.esquerda = inserirArvoreRec(num, raiz.esquerda);
        }
        if(num > raiz.num)
        {
            raiz.direita = inserirArvoreRec(num, raiz.direita);
        }
        return raiz;
    }

}
