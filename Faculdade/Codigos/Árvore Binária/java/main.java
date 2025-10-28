public class main
{
    public static void main(String[] args)
    {
        Arvore a = new Arvore();

        a.inserir(1);
        a.inserir(9);
        a.inserir(8);
        a.inserir(12);
        a.inserir(35);
        a.inserir(2);
        a.inserir(6);
        a.inserir(10);

        System.out.print(a.pesquisar(100));

    }
}

class No
{
    public int elemento;
    public No esquerda, direita;

    public No()
    {
        this.elemento = 0;
        this.esquerda = this.direita = null;
    }

    public No(int n)
    {
        this.elemento = n;
        this.esquerda = this.direita = null;
    }
}

class Arvore
{
    public No raiz;

    public Arvore()
    {
        this.raiz = null;
    }

    public void inserir(int n)
    {
        raiz = inserirRec(raiz, n);
    }
    public No inserirRec(No atual, int n)
    {
        if(atual == null)
        {
            return atual = new No(n); 
        }

        if(n < atual.elemento)
        {
            atual.esquerda = inserirRec(atual.esquerda, n);
        }
        if(n > atual.elemento)
        {
            atual.direita = inserirRec(atual.direita, n);
        }

        return atual;
    }

    public boolean pesquisar(int n)
    {
        return pesquisarRec(raiz, n);
    }
    public boolean pesquisarRec(No atual, int n)
    {
        if(atual == null)
        {
            return false;
        }

        if(atual.elemento == n)
        {
            return true;
        }

        if(atual.elemento < n)
        {
            return pesquisarRec(atual.esquerda, n);
        }

        return pesquisarRec(atual.direita, n);

    }
}
