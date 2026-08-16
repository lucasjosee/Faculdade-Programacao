/*
 * Aluno: Lucas José Souza Rodrigues
 * 892665
 * Algoritmos e Estruturas de Dados II
 * Laboratorio - Arvore Bicolor
*/

public class ArvoreBicolor
{
    public static No raiz;

    // Inicializa a estrutura de dados e seus ponteiros base
    public static void iniciar()
    {
        raiz = null;
    }

    // Realiza reequilibrio por recoloracao equivalente a fragmentacao na arvore 2-3-4
    private static void fragmentar(No i)
    {
        i.cor = true;
        if(i.esq != null) i.esq.cor = false;
        if(i.dir != null) i.dir.cor = false;
        if(i == raiz) i.cor = false;
    }

    // Aplica rotacao simples a esquerda e retorna o novo no raiz do conjunto
    private static No rotacaoEsquerda(No no)
    {
        No novoRaiz = no.dir;
        no.dir = novoRaiz.esq;
        novoRaiz.esq = no;
        return novoRaiz;
    }

    // Aplica rotacao simples a direita e retorna o novo no raiz do conjunto
    private static No rotacaoDireita(No no)
    {
        No novoRaiz = no.esq;
        no.esq = novoRaiz.dir;
        novoRaiz.dir = no;
        return novoRaiz;
    }

    // Aplica rotacao dupla direita-esquerda e retorna o novo no raiz do conjunto
    private static No rotacaoDuplaDireitaEsquerda(No no)
    {
        no.dir = rotacaoDireita(no.dir);
        return rotacaoEsquerda(no);
    }

    // Aplica rotacao dupla esquerda-direita e retorna o novo no raiz do conjunto
    private static No rotacaoDuplaEsquerdaDireita(No no)
    {
        no.esq = rotacaoEsquerda(no.esq);
        return rotacaoDireita(no);
    }

    // Realiza reequilibrio por rotacao e conecta a nova raiz do conjunto ao bisavo
    private static void balancear(No bisavo, No avo, No pai, No i)
    {
        No novoRaiz;

        if(pai.elemento > avo.elemento && i.elemento > pai.elemento)
            novoRaiz = rotacaoEsquerda(avo);
        else if(pai.elemento > avo.elemento && i.elemento < pai.elemento)
            novoRaiz = rotacaoDuplaDireitaEsquerda(avo);
        else if(pai.elemento < avo.elemento && i.elemento < pai.elemento)
            novoRaiz = rotacaoDireita(avo);
        else
            novoRaiz = rotacaoDuplaEsquerdaDireita(avo);

        novoRaiz.cor = false;
        novoRaiz.esq.cor = true;
        novoRaiz.dir.cor = true;

        if(bisavo == null)
            raiz = novoRaiz;
        else if(novoRaiz.elemento > bisavo.elemento)
            bisavo.dir = novoRaiz;
        else
            bisavo.esq = novoRaiz;
    }

    // Aloca e insere o elemento na respectiva posicao da estrutura
    public static void inserir(int x)
    {
        if(raiz == null)
            raiz = new No(x);
        else
            inserir(x, null, null, null, raiz);
    }

    // Localiza a posicao de insercao e orquestra os reequilibrios necessarios
    private static void inserir(int x, No bisavo, No avo, No pai, No i)
    {
        if(i == null)
        {
            No novo = new No(x);
            novo.cor = true;
            if(x < pai.elemento)
                pai.esq = novo;
            else
                pai.dir = novo;
            if(pai.cor)
                balancear(bisavo, avo, pai, novo);
        }
        else
        {
            if(i.isNoTipo4())
            {
                fragmentar(i);
                if(pai != null && pai.cor)
                    balancear(bisavo, avo, pai, i);
            }
            if(x < i.elemento)
                inserir(x, avo, pai, i, i.esq);
            else if(x > i.elemento)
                inserir(x, avo, pai, i, i.dir);
        }
    }

    // Varre a arvore em ordem central imprimindo o elemento e sua cor
    public static void caminharCentral(No i)
    {
        if(i != null)
        {
            caminharCentral(i.esq);
            System.out.print(i.elemento + "(cor=" + (i.cor ? 1 : 0) + ") ");
            caminharCentral(i.dir);
        }
    }

    public static void main(String[] args)
    {
        iniciar();

        int[] elementos = {4, 35, 10, 13, 3, 30, 15, 12, 7, 40, 20};
        for(int e : elementos)
            inserir(e);

        caminharCentral(raiz);
        System.out.println();
    }
}

class No
{
    public int elemento;
    public boolean cor;
    public No esq;
    public No dir;

    public No(int elemento)
    {
        this.elemento = elemento;
        this.cor = false;
        this.esq = null;
        this.dir = null;
    }

    // Retorna verdadeiro se o no e do tipo 4 (ambos os filhos existem e sao coloridos)
    public boolean isNoTipo4()
    {
        return esq != null && dir != null && esq.cor && dir.cor;
    }
}
