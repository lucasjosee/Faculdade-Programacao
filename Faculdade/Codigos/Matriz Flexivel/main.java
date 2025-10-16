import java.util.Random;
public class main
{
    public static void main(String[] args)
    {
        Matriz m1 = new Matriz(6, 6);

        m1.construirMatriz();
        m1.preencherMatriz();
        m1.mostrarMatriz();

        System.out.println();
        
        m1.getDiagonalSec();

    }
}

class Celula 
{
    public Celula dir, esq, sup, inf;
    public int elemento;

    public Celula()
    {
        this.dir = this.esq = this.sup = this.inf = null;
        this.elemento = 0;
    }

    public Celula(int elemento)
    {
        this.dir = this.esq = this.sup = this.inf = null;
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

    public void construirMatriz()
    {
        inicio = new Celula();
        Celula linhaAtual = inicio;
        
        for(int j = 1; j < coluna; j++)
        {
            linhaAtual.dir = new Celula();
            linhaAtual.dir.esq = linhaAtual;
            linhaAtual = linhaAtual.dir;
        }

        Celula linhaCima = inicio;

        for(int i = 1; i < linha; i++)
        {
            Celula novaLinha = new Celula();
            novaLinha.sup = linhaCima;
            linhaCima.inf = novaLinha;

            Celula atualCima = linhaCima.dir;
            Celula atualBaixo = novaLinha;

            for(int j = 1; j < coluna; j++)
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

    public  void preencherMatriz()
    {
        Random aleatorio = new Random();

        Celula i;
        Celula j;
        
        for(i = inicio; i != null; i = i.inf)
        {
            for(j = i; j != null; j = j.dir)
            {
                j.elemento = aleatorio.nextInt(100);
            }
        }
        
    }

    public void mostrarMatriz()
    {
        Celula i;
        Celula j;

        for(i = inicio; i != null; i = i.inf)
        {
            for(j = i; j != null; j = j.dir)
            {
                System.out.print(j.elemento + " ");

            }
            System.out.println();
        }
    }

    public Matriz somarMatriz(Matriz m1, Matriz m2)
    {
        if(m1.linha != m2.linha || m1.coluna != m2.coluna)
        {
            throw new RuntimeException("Erro: Matrizes de tamanhos diferentes");
        }

        Celula im1;
        Celula jm1;

        Celula im2;
        Celula jm2;

        Celula im3;
        Celula jm3;

        Matriz m3 = new Matriz(m1.linha, m1.coluna);

        m3.construirMatriz();


        for(im1 = m1.inicio, im2 = m2.inicio, im3 = m3.inicio; im1 != null; im1 = im1.inf, im2 = im2.inf, im3 = im3.inf)
        {
            for(jm1 = im1, jm2 = im2, jm3 = im3; jm1 != null; jm1 = jm1.dir, jm2 = jm2.dir, jm3 = jm3.dir)
            {
                jm3.elemento = jm1.elemento + jm2.elemento;
            }
            
        }

        return m3;
    }

    public void getDiagonalPri()
    {
        if(linha != coluna)
        {
            throw new RuntimeException("Erro: Matriz não é quadratica.");
        }

        Celula i, j;
        int conti, contj;
        for(i = inicio, conti = 0 ; conti < linha; conti++, i = i.inf)
        {
            for(j = i, contj = 0; contj < conti; j = j.dir, contj++);

            System.out.println(j.elemento + " ");
        }
    }

    public void getDiagonalSec()
    {
        if(linha != coluna)
        {
            throw new RuntimeException("Erro: Matriz não é quadratica.");
        }
        
        Celula i, j;
        int conti, contj;
        for(i = inicio, conti = 0 ; conti < linha; conti++, i = i.inf)
        {
            for(j = i, contj = coluna - 1; contj > conti; j = j.dir, contj--);

            System.out.println(j.elemento + " ");
        }
    }

}

