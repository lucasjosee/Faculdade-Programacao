public class main
{
    public static void main(String[] args)
    {
        Arvore a = new Arvore();

        a.inserir(1);
        a.inserir(15);
        a.inserir(10);
        a.inserir(3);
        a.inserir(2);
        a.inserir(4);
        a.inserir(7);
        a.inserir(5);

        a.caminhamento();
    }

   
}

class No
{
    public int elemento;
    public No dir;
    public No esq;

    public No()
    {
        this.elemento = 0;
        this.esq = null;
        this.dir = null;
    }

    public No(int n)
    {
        this.elemento = n;
        this.esq = null;
        this.dir = null;
    }
}

class Arvore
{
    public No root;

    public Arvore()
    {
        this.root = null;
    }

    public void inserir(int n)
    {
        root = inserirRec(this.root, n);
    }

    public No inserirRec(No root, int n)
    {
        if(root == null)
            root = new No(n);
        else if(n < root.elemento)
            root.esq = inserirRec(root.esq, n);
        else if(n > root.elemento)
            root.dir = inserirRec(root.dir, n);

        return root;
    }

    public void caminhamento()
    {
        caminhamentoRec(this.root);
    }

    public void caminhamentoRec(No root)
    {
        if(root != null)
        {
            System.out.println(root.elemento);
            caminhamentoRec(root.esq);
            caminhamentoRec(root.dir);
        }
    }
}
