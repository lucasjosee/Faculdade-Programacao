/*
 * Aluno: Lucas José Souza Rodrigues
 * TP 04 - Q1 - Árvore AVL em Java
 */

import java.util.Scanner;
import java.util.Locale;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class tp4_01
{
    static NoAvl raiz = null;
    static int comparacoes = 0;

    public static void main(String[] args)
    {
        ColecaoRestaurantes c = ColecaoRestaurantes.lerCsv();
        Scanner sc = new Scanner(System.in);
        raiz = null;

        int id;
        while(sc.hasNextInt() && (id = sc.nextInt()) != -1)
        {
            Restaurante r = c.getRestauranteById(id);
            if(r != null)
            {
                raiz = inserir(r, raiz);
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

        caminharCentral(raiz);

        try
        {
            FileWriter fw = new FileWriter("892665_arvore_avl.txt");
            fw.write("892665\t" + comparacoes + "\t" + tempo);
            fw.close();
        }
        catch(IOException e)
        {
            System.err.println("Erro ao escrever log");
        }
    }

    /* ---- Funções da AVL ---- */

    static int altura(NoAvl no)
    {
        return no == null ? 0 : no.altura;
    }

    static int fb(NoAvl no)
    {
        return altura(no.esq) - altura(no.dir);
    }

    static void atualizarAltura(NoAvl no)
    {
        no.altura = 1 + Math.max(altura(no.esq), altura(no.dir));
    }

    static NoAvl rotDir(NoAvl y)
    {
        NoAvl x = y.esq;
        NoAvl t2 = x.dir;
        x.dir = y;
        y.esq = t2;
        atualizarAltura(y);
        atualizarAltura(x);
        return x;
    }

    static NoAvl rotEsq(NoAvl x)
    {
        NoAvl y = x.dir;
        NoAvl t2 = y.esq;
        y.esq = x;
        x.dir = t2;
        atualizarAltura(x);
        atualizarAltura(y);
        return y;
    }

    static NoAvl inserir(Restaurante r, NoAvl no)
    {
        if(no == null) return new NoAvl(r);
        int cmp = r.getNome().compareTo(no.restaurante.getNome());
        if(cmp < 0)
        {
            no.esq = inserir(r, no.esq);
        }
        else if(cmp > 0)
        {
            no.dir = inserir(r, no.dir);
        }
        else
        {
            return no;
        }

        atualizarAltura(no);
        int f = fb(no);

        if(f > 1 && r.getNome().compareTo(no.esq.restaurante.getNome()) < 0)
            return rotDir(no);
        if(f < -1 && r.getNome().compareTo(no.dir.restaurante.getNome()) > 0)
            return rotEsq(no);
        if(f > 1 && r.getNome().compareTo(no.esq.restaurante.getNome()) > 0)
        {
            no.esq = rotEsq(no.esq);
            return rotDir(no);
        }
        if(f < -1 && r.getNome().compareTo(no.dir.restaurante.getNome()) < 0)
        {
            no.dir = rotDir(no.dir);
            return rotEsq(no);
        }
        return no;
    }

    static boolean pesquisarRec(String nome, NoAvl no)
    {
        if(no == null) return false;
        comparacoes++;
        if(nome.equals(no.restaurante.getNome())) return true;
        comparacoes++;
        if(nome.compareTo(no.restaurante.getNome()) < 0)
        {
            System.out.print("esq ");
            return pesquisarRec(nome, no.esq);
        }
        else
        {
            System.out.print("dir ");
            return pesquisarRec(nome, no.dir);
        }
    }

    static void pesquisar(String nome)
    {
        System.out.print("raiz ");
        boolean resp = pesquisarRec(nome, raiz);
        System.out.println(resp ? "SIM" : "NAO");
    }

    static void caminharCentral(NoAvl no)
    {
        if(no != null)
        {
            caminharCentral(no.esq);
            System.out.println(no.restaurante.formatar());
            caminharCentral(no.dir);
        }
    }
}

class NoAvl
{
    public Restaurante restaurante;
    public NoAvl esq, dir;
    public int altura;

    public NoAvl(Restaurante r)
    {
        restaurante = r;
        esq = null;
        dir = null;
        altura = 1;
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
