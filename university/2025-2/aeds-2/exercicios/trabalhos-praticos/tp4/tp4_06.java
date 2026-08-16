/*
 * Aluno: Lucas José Souza Rodrigues
 * TP 04 - Q6 - Árvore Binária de Árvore Binária em Java
 */

import java.util.Scanner;
import java.util.Locale;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class tp4_06
{
    static No1 raiz = null;
    static int comparacoes = 0;
    static String[] resultado = new String[1];

    public static void main(String[] args)
    {
        ColecaoRestaurantes c = ColecaoRestaurantes.lerCsv();
        Scanner sc = new Scanner(System.in);

        int id;
        while(sc.hasNextInt() && (id = sc.nextInt()) != -1)
        {
            Restaurante r = c.getRestauranteById(id);
            if(r != null)
            {
                inserir(r);
            }
        }

        long inicio = System.currentTimeMillis();
        while(sc.hasNextLine())
        {
            String str = sc.nextLine().trim();
            if(str.equals("FIM")) break;
            if(!str.isEmpty()) pesquisar(str);
        }
        long tempo = System.currentTimeMillis() - inicio;
        sc.close();

        try
        {
            FileWriter fw = new FileWriter("892665_hibrida_arvore_arvore.txt");
            fw.write("892665\t" + comparacoes + "\t" + tempo);
            fw.close();
        }
        catch(IOException e)
        {
            System.err.println("Erro ao escrever log");
        }
    }

    /* ---- AVL (2º nível) ---- */

    static int alt(No2 n)
    {
        return n == null ? 0 : n.altura;
    }

    static int fb(No2 n)
    {
        return alt(n.esq) - alt(n.dir);
    }

    static void updH(No2 n)
    {
        n.altura = 1 + Math.max(alt(n.esq), alt(n.dir));
    }

    static No2 rotD(No2 y)
    {
        No2 x = y.esq;
        y.esq = x.dir;
        x.dir = y;
        updH(y);
        updH(x);
        return x;
    }

    static No2 rotE(No2 x)
    {
        No2 y = x.dir;
        x.dir = y.esq;
        y.esq = x;
        updH(x);
        updH(y);
        return y;
    }

    static No2 insAvl(Restaurante r, No2 n)
    {
        if(n == null) return new No2(r);
        int cmp = r.getNome().compareTo(n.restaurante.getNome());
        if(cmp < 0)
        {
            n.esq = insAvl(r, n.esq);
        }
        else if(cmp > 0)
        {
            n.dir = insAvl(r, n.dir);
        }
        else
        {
            return n;
        }

        updH(n);
        int f = fb(n);

        if(f > 1 && r.getNome().compareTo(n.esq.restaurante.getNome()) < 0)
            return rotD(n);
        if(f < -1 && r.getNome().compareTo(n.dir.restaurante.getNome()) > 0)
            return rotE(n);
        if(f > 1 && r.getNome().compareTo(n.esq.restaurante.getNome()) > 0)
        {
            n.esq = rotE(n.esq);
            return rotD(n);
        }
        if(f < -1 && r.getNome().compareTo(n.dir.restaurante.getNome()) < 0)
        {
            n.dir = rotD(n.dir);
            return rotE(n);
        }
        return n;
    }

    /* ---- ABP (1º nível) ---- */

    static No1 ins1(Restaurante r, No1 n)
    {
        int ch = r.getCapacidade() % 15;
        if(n == null)
        {
            No1 novo = new No1(ch);
            novo.avl = insAvl(r, null);
            return novo;
        }
        if(ch < n.chave)
        {
            n.esq = ins1(r, n.esq);
        }
        else if(ch > n.chave)
        {
            n.dir = ins1(r, n.dir);
        }
        else
        {
            n.avl = insAvl(r, n.avl);
        }
        return n;
    }

    static void inserir(Restaurante r)
    {
        raiz = ins1(r, raiz);
    }

    /* ---- Pesquisa pré-ordem no 1º nível, AVL no 2º ---- */

    static boolean pesquisarAvl(String nome, No2 n, String dir)
    {
        System.out.print(dir + " ");
        if(n == null) return false;
        comparacoes++;
        if(nome.equals(n.restaurante.getNome()))
        {
            resultado[0] = n.restaurante.formatar();
            return true;
        }
        comparacoes++;
        if(nome.compareTo(n.restaurante.getNome()) < 0)
            return pesquisarAvl(nome, n.esq, "esq");
        else
            return pesquisarAvl(nome, n.dir, "dir");
    }

    static boolean preOrdem(String nome, No1 n, String caminho1)
    {
        System.out.print(caminho1 + " ");
        if(n == null) return false;
        boolean achou = pesquisarAvl(nome, n.avl, "raiz");
        if(achou)
        {
            System.out.println("SIM " + resultado[0]);
            return true;
        }
        if(preOrdem(nome, n.esq, "ESQ")) return true;
        return preOrdem(nome, n.dir, "DIR");
    }

    static void pesquisar(String nome)
    {
        resultado[0] = null;
        boolean achou = preOrdem(nome, raiz, "RAIZ");
        if(!achou) System.out.println("NAO");
    }
}

class No2
{
    public Restaurante restaurante;
    public No2 esq, dir;
    public int altura;

    public No2(Restaurante r)
    {
        restaurante = r;
        esq = null;
        dir = null;
        altura = 1;
    }
}

class No1
{
    public int chave;
    public No2 avl;
    public No1 esq, dir;

    public No1(int chave)
    {
        this.chave = chave;
        avl = null;
        esq = null;
        dir = null;
    }
}

class ColecaoRestaurantes
{
    private int tamanho;
    private Restaurante[] restaurantes;

    public int getTamanho() { return tamanho; }
    public Restaurante[] getRestaurantes() { return restaurantes; }

    public void lerCsv(String path)
    {
        try
        {
            BufferedReader br = new BufferedReader(new FileReader(path));
            int cont = 0;
            br.readLine();
            while(br.readLine() != null) cont++;
            br.close();
            tamanho = cont;
            restaurantes = new Restaurante[cont];
            br = new BufferedReader(new FileReader(path));
            br.readLine();
            int i = 0;
            String linha;
            while((linha = br.readLine()) != null)
            {
                restaurantes[i++] = Restaurante.parseRestaurante(linha);
            }
            br.close();
        }
        catch(IOException e)
        {
            System.err.println("Erro ao ler CSV: " + e.getMessage());
        }
    }

    public static ColecaoRestaurantes lerCsv()
    {
        ColecaoRestaurantes c = new ColecaoRestaurantes();
        c.lerCsv("/tmp/restaurantes.csv");
        return c;
    }

    public Restaurante getRestauranteById(int id)
    {
        for(int i = 0; i < tamanho; i++)
        {
            if(restaurantes[i].getId() == id)
            {
                return restaurantes[i];
            }
        }
        return null;
    }
}

class Hora
{
    private int hora, minuto;

    public int getHora() { return hora; }
    public int getMinuto() { return minuto; }
    public void setHora(int h) { hora = h; }
    public void setMinuto(int m) { minuto = m; }

    public static Hora parseHora(String s)
    {
        Hora h = new Hora();
        String[] p = s.split(":");
        h.setHora(Integer.parseInt(p[0]));
        h.setMinuto(Integer.parseInt(p[1]));
        return h;
    }

    public String formatar()
    {
        return String.format("%02d:%02d", hora, minuto);
    }
}

class Data
{
    private int ano, mes, dia;

    public int getAno() { return ano; }
    public int getMes() { return mes; }
    public int getDia() { return dia; }
    public void setAno(int a) { ano = a; }
    public void setMes(int m) { mes = m; }
    public void setDia(int d) { dia = d; }

    public static Data parseData(String s)
    {
        Data d = new Data();
        String[] p = s.split("-");
        d.setAno(Integer.parseInt(p[0]));
        d.setMes(Integer.parseInt(p[1]));
        d.setDia(Integer.parseInt(p[2]));
        return d;
    }

    public String formatar()
    {
        return String.format("%02d/%02d/%04d", dia, mes, ano);
    }
}

class Restaurante
{
    private int id;
    private String nome, cidade;
    private int capacidade;
    private double avaliacao;
    private String[] tiposCozinha;
    private int faixaPreco;
    private Hora horarioAbertura, horarioFechamento;
    private Data dataAbertura;
    private boolean aberto;

    public int getId() { return id; }
    public String getNome() { return nome; }
    public String getCidade() { return cidade; }
    public int getCapacidade() { return capacidade; }
    public double getAvaliacao() { return avaliacao; }
    public String[] getTiposCozinha() { return tiposCozinha; }
    public int getFaixaPreco() { return faixaPreco; }
    public Hora getHorarioAbertura() { return horarioAbertura; }
    public Hora getHorarioFechamento() { return horarioFechamento; }
    public Data getDataAbertura() { return dataAbertura; }
    public boolean getAberto() { return aberto; }

    public void setId(int id) { this.id = id; }
    public void setNome(String nome) { this.nome = nome; }
    public void setCidade(String cidade) { this.cidade = cidade; }
    public void setCapacidade(int capacidade) { this.capacidade = capacidade; }
    public void setAvaliacao(double avaliacao) { this.avaliacao = avaliacao; }
    public void setTiposCozinha(String[] t) { this.tiposCozinha = t; }
    public void setFaixaPreco(int f) { this.faixaPreco = f; }
    public void setHorarioAbertura(Hora h) { this.horarioAbertura = h; }
    public void setHorarioFechamento(Hora h) { this.horarioFechamento = h; }
    public void setDataAbertura(Data d) { this.dataAbertura = d; }
    public void setAberto(boolean a) { this.aberto = a; }

    public static Restaurante parseRestaurante(String linha)
    {
        String[] tokens = linha.split(",");
        Restaurante r = new Restaurante();
        r.setId(Integer.parseInt(tokens[0]));
        r.setNome(tokens[1]);
        r.setCidade(tokens[2]);
        r.setCapacidade(Integer.parseInt(tokens[3]));
        r.setAvaliacao(Double.parseDouble(tokens[4]));
        r.setTiposCozinha(tokens[5].split(";"));
        r.setFaixaPreco(tokens[6].length());
        String[] horario = tokens[7].split("-");
        r.setHorarioAbertura(Hora.parseHora(horario[0]));
        r.setHorarioFechamento(Hora.parseHora(horario[1]));
        r.setDataAbertura(Data.parseData(tokens[8]));
        r.setAberto(Boolean.parseBoolean(tokens[9]));
        return r;
    }

    public String formatar()
    {
        StringBuilder tipos = new StringBuilder("[");
        for(int i = 0; i < tiposCozinha.length; i++)
        {
            tipos.append(tiposCozinha[i]);
            if(i < tiposCozinha.length - 1) tipos.append(",");
        }
        tipos.append("]");
        StringBuilder faixa = new StringBuilder();
        for(int i = 0; i < faixaPreco; i++) faixa.append("$");
        return String.format(Locale.US,
            "[%d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %s-%s ## %s ## %b]",
            id, nome, cidade, capacidade, avaliacao, tipos, faixa,
            horarioAbertura.formatar(), horarioFechamento.formatar(),
            dataAbertura.formatar(), aberto);
    }
}
