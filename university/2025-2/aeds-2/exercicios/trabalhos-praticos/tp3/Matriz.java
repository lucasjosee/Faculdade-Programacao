import java.util.Scanner;

class Celula {
   public int elemento;
   public Celula inf, sup, esq, dir;

   public Celula(){
      this(0);
   }

   public Celula(int elemento){
      this(elemento, null, null, null, null);
   }

   public Celula(int elemento, Celula inf, Celula sup, Celula esq, Celula dir){
      this.elemento = elemento;
      this.inf = inf;
      this.sup = sup;
      this.esq = esq;
      this.dir = dir;
   }
}

public class Matriz {
    private Celula inicio;
    private int linha, coluna;

    public Matriz(int linha, int coluna) {
        this.linha = linha;
        this.coluna = coluna;

        inicio = new Celula();

        // Constroi a primeira linha
        Celula atual = inicio;
        for (int j = 1; j < coluna; j++) {
            atual.dir = new Celula();
            atual.dir.esq = atual;
            atual = atual.dir;
        }

        // Constroi as linhas restantes
        Celula inicioLinhaAnterior = inicio;
        for (int i = 1; i < linha; i++) {
            Celula inicioLinhaAtual = new Celula();
            inicioLinhaAtual.sup = inicioLinhaAnterior;
            inicioLinhaAnterior.inf = inicioLinhaAtual;

            Celula acima = inicioLinhaAnterior.dir;
            atual = inicioLinhaAtual;
            for (int j = 1; j < coluna; j++) {
                atual.dir = new Celula();
                atual.dir.esq = atual;
                atual = atual.dir;
                atual.sup = acima;
                acima.inf = atual;
                acima = acima.dir;
            }

            inicioLinhaAnterior = inicioLinhaAtual;
        }
    }

    public void inserir(int elemento, int linha, int coluna) {
        Celula c = inicio;
        for (int i = 0; i < linha; i++) c = c.inf;
        for (int j = 0; j < coluna; j++) c = c.dir;
        c.elemento = elemento;
    }

    public int obter(int linha, int coluna) {
        Celula c = inicio;
        for (int i = 0; i < linha; i++) c = c.inf;
        for (int j = 0; j < coluna; j++) c = c.dir;
        return c.elemento;
    }

    // Realiza a soma de matrizes validando suas dimensoes previamente
    public Matriz somar(Matriz m) {
        if (this.linha != m.linha || this.coluna != m.coluna)
            return null;

        Matriz resp = new Matriz(this.linha, this.coluna);

        Celula iA = this.inicio;
        Celula iB = m.inicio;
        Celula iC = resp.inicio;

        for (; iA != null; iA = iA.inf, iB = iB.inf, iC = iC.inf) {
            Celula a = iA;
            Celula b = iB;
            Celula c = iC;
            for (; a != null; a = a.dir, b = b.dir, c = c.dir) {
                c.elemento = a.elemento + b.elemento;
            }
        }

        return resp;
    }

    // Multiplica duas matrizes alocando dinamicamente a matriz resultante
    public Matriz multiplicar(Matriz m) {
        if (this.coluna != m.linha)
            return null;

        Matriz resp = new Matriz(this.linha, m.coluna);

        for (int i = 0; i < this.linha; i++) {
            for (int j = 0; j < m.coluna; j++) {
                int soma = 0;
                for (int k = 0; k < this.coluna; k++) {
                    soma += this.obter(i, k) * m.obter(k, j);
                }
                resp.inserir(soma, i, j);
            }
        }

        return resp;
    }

    // Percorre e imprime os elementos da diagonal principal da matriz
    public void mostrarDiagonalPrincipal() {
        int tam = Math.min(this.linha, this.coluna);
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < tam; i++) {
            if (i > 0) sb.append(" ");
            sb.append(obter(i, i));
        }
        System.out.println(sb.toString());
    }

    // Percorre e imprime os elementos da diagonal secundaria da matriz
    public void mostrarDiagonalSecundaria() {
        int tam = Math.min(this.linha, this.coluna);
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < tam; i++) {
            if (i > 0) sb.append(" ");
            sb.append(obter(i, tam - 1 - i));
        }
        System.out.println(sb.toString());
    }

    public void imprimir() {
        for (Celula i = inicio; i != null; i = i.inf) {
            StringBuilder sb = new StringBuilder();
            boolean primeiro = true;
            for (Celula j = i; j != null; j = j.dir) {
                if (!primeiro) sb.append(" ");
                sb.append(j.elemento);
                primeiro = false;
            }
            System.out.println(sb.toString());
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int casos = sc.nextInt();

        for (int t = 0; t < casos; t++) {
            // Lê a primeira matriz
            int l1 = sc.nextInt(), c1 = sc.nextInt();
            Matriz a = new Matriz(l1, c1);
            for (int i = 0; i < l1; i++)
                for (int j = 0; j < c1; j++)
                    a.inserir(sc.nextInt(), i, j);

            // A segunda matriz tem a mesma dimensao da primeira
            Matriz b = new Matriz(l1, c1);
            for (int i = 0; i < l1; i++)
                for (int j = 0; j < c1; j++)
                    b.inserir(sc.nextInt(), i, j);

            // Diagonal principal de A
            a.mostrarDiagonalPrincipal();

            // Diagonal secundária de B
            b.mostrarDiagonalSecundaria();

            // Soma A + B
            Matriz soma = a.somar(b);
            if (soma != null) soma.imprimir();

            // Multiplicação A * B
            Matriz mult = a.multiplicar(b);
            if (mult != null) mult.imprimir();
        }

        sc.close();
    }
}