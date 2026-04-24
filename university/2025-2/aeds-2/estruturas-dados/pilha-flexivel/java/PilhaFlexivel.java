public class PilhaFlexivel
{
    public static void main(String[] args)
    {
        Pilha pilha = new Pilha();

        pilha.inserir(1);
        pilha.inserir(2);
        pilha.inserir(10);
        pilha.inserir(9);
        pilha.inserir(7);
        pilha.mostrar();

        System.out.println();
        
        System.out.println("maior = " + pilha.maiorElementoRecursivo());
    }
}

class Celula
{
    Celula prox;
    public int elemento;

    public Celula()
    {
        this.prox = null;
        this.elemento = 0;
    }

    public Celula(int elemento)
    {
        this.prox = null;
        this.elemento = elemento;
    }
}

class Pilha
{
    private Celula topo;

    public Pilha()
    {
        topo = new Celula();
    }

    public void mostrar()
    {
        for(Celula i = topo.prox; i != null; i = i.prox)
        {
            System.out.print(i.elemento + " ");
        }
    }

    public void inserir(int elemento)
    {
        Celula temp = new Celula(elemento);
        temp.prox = topo.prox;
        topo.prox = temp;

        temp = null;
    }

    public void remover()
    {
        Celula temp = topo.prox;

        topo.prox = temp.prox;
        temp.prox = null;
        
        temp = null;
    }

    //Exercicio

    //1. Faça um metodo que some todos os elemento
    public int somar()
    {
        int soma = 0;
        for(Celula i = topo.prox; i != null; i = i.prox)
        {
            soma += i.elemento;
        }
        return soma;
    }

    //2. Faça o exercicio anterior de forma recursiva
    public int somarRecursivo()
    {
        return somarRecursivo(topo.prox);
    }

    private int somarRecursivo(Celula i)
    {
        if(i == null)
        {
            return 0;
        }

        return i.elemento + somarRecursivo(i.prox);
    }

    //3. Faça um metodo que retorne o maior elemento contido na mesma
    public int maiorElemento()
    {
        int maior = topo.prox.elemento;
        for(Celula i = topo.prox; i != null; i = i.prox)
        {
            if(i.elemento > maior)
            {
                maior = i.elemento;
            }
        }
        return maior;
    }

    //4. Faça o exercicio anterior de forma recursiva
    public int maiorElementoRecursivo()
    {
        return maiorElementoRecursivo(topo.prox, topo.prox.elemento);
    }

    private int maiorElementoRecursivo(Celula i, int maior)
    {
        if(i == null)
        {
            return maior;
        }

        if(i.elemento > maior)
        {
            maior = i.elemento;
        }
        return maiorElementoRecursivo(i.prox, maior);
    }
    

}
