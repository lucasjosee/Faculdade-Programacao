import java.util.Scanner;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

class CelulaDupla {
    public Restaurante restaurante;
    public CelulaDupla ant;
    public CelulaDupla prox;

    public CelulaDupla() {
        this(null);
    }

    public CelulaDupla(Restaurante restaurante) {
        this.restaurante = restaurante;
        this.ant = this.prox = null;
    }
}

public class tp3_11 {
    public static CelulaDupla primeiro;
    public static CelulaDupla ultimo;
    public static int tamanho;
    public static int comparacoes = 0;
    public static int movimentacoes = 0;

    // Inicializa a estrutura de dados e seus ponteiros base
    public static void iniciar() {
        primeiro = new CelulaDupla();
        ultimo = primeiro;
        tamanho = 0;
    }

    // Aloca e anexa o elemento no fim da estrutura
    public static void inserirFim(Restaurante x) {
        ultimo.prox = new CelulaDupla(x);
        ultimo.prox.ant = ultimo;
        ultimo = ultimo.prox;
        tamanho++;
    }

    // Varre a estrutura imprimindo seus elementos na saida padrao
    public static void mostrar() {
        for (CelulaDupla i = primeiro.prox; i != null; i = i.prox) {
            System.out.println(i.restaurante.formatar());
        }
    }

    // Realiza a troca de posicao entre dois elementos do arranjo
    public static void swap(CelulaDupla i, CelulaDupla j) {
        Restaurante tmp = i.restaurante;
        i.restaurante = j.restaurante;
        j.restaurante = tmp;
        movimentacoes += 3;
    }

    public static CelulaDupla getCelula(int pos) {
        CelulaDupla resp = primeiro.prox;
        for (int i = 0; i < pos; i++) {
            resp = resp.prox;
        }
        return resp;
    }

    // Rotinas auxiliares para fracionar e ordenar os vetores usando Quicksort
    public static void quicksort(int esq, int dir) {
        int i = esq, j = dir;
        CelulaDupla cI = getCelula(i);
        CelulaDupla cJ = getCelula(j);
        Restaurante pivo = getCelula((dir + esq) / 2).restaurante;

        while (i <= j) {
            comparacoes++;
            while (cI.restaurante.getAvaliacao() < pivo.getAvaliacao() || 
                  (cI.restaurante.getAvaliacao() == pivo.getAvaliacao() && cI.restaurante.getNome().compareTo(pivo.getNome()) < 0)) {
                comparacoes += 2;
                i++;
                cI = cI.prox;
            }
            comparacoes++;
            while (cJ.restaurante.getAvaliacao() > pivo.getAvaliacao() || 
                  (cJ.restaurante.getAvaliacao() == pivo.getAvaliacao() && cJ.restaurante.getNome().compareTo(pivo.getNome()) > 0)) {
                comparacoes += 2;
                j--;
                cJ = cJ.ant;
            }

            if (i <= j) {
                swap(cI, cJ);
                i++;
                j--;
                cI = cI.prox;
                cJ = cJ.ant;
            }
        }
        if (esq < j) quicksort(esq, j);
        if (i < dir) quicksort(i, dir);
    }

    public static void main(String[] args) {
        long startTime = System.currentTimeMillis();
        ColecaoRestaurantes c = ColecaoRestaurantes.lerCsv();
        Scanner sc = new Scanner(System.in);

        iniciar();

        int id;
        while ((id = sc.nextInt()) != -1) {
            Restaurante r = c.getRestauranteById(id);
            if (r != null) {
                inserirFim(r);
            }
        }

        sc.close();

        quicksort(0, tamanho - 1);

        long tempoExecucao = System.currentTimeMillis() - startTime;

        mostrar();

        try {
            FileWriter fw = new FileWriter("892665_quicksort_flexivel.txt");
            fw.write("892665\t" + comparacoes + "\t" + movimentacoes + "\t" + tempoExecucao);
            fw.close();
        } catch (IOException e) {
            System.out.println("Erro ao escrever arquivo de log");
        }
    }
}

class ColecaoRestaurantes {
    private int tamanho;
    private Restaurante[] restaurantes;

    public int getTamanho() { return tamanho; }
    public Restaurante[] getRestaurantes() { return restaurantes; }

    // Le os dados do CSV e instancia os restaurantes
    public void lerCsv(String path) {
        BufferedReader br = null;
        try {
            br = new BufferedReader(new FileReader(path));
            String linha;
            int cont = 0;
            br.readLine(); 
            while ((linha = br.readLine()) != null) {
                cont++;
            }
            tamanho = cont;
            restaurantes = new Restaurante[cont];
            br.close();

            br = new BufferedReader(new FileReader(path));
            int i = 0;
            br.readLine();
            while ((linha = br.readLine()) != null) {
                restaurantes[i] = Restaurante.parseRestaurante(linha);
                i++;
            }
            br.close();
        } catch (IOException e) {
            System.out.println("Erro ao ler arquivo: " + e.getMessage());
        }
    }

    // Popula a colecao baseando-se no arquivo de dados padrao
    public static ColecaoRestaurantes lerCsv() {
        ColecaoRestaurantes c = new ColecaoRestaurantes();
        c.lerCsv("/tmp/restaurantes.csv");
        return c;
    }

    // Faz a varredura linear na colecao para resgatar o restaurante pelo ID
    public Restaurante getRestauranteById(int id) {
        for (int i = 0; i < tamanho; i++) {
            if (restaurantes[i].getId() == id) {
                return restaurantes[i];
            }
        }
        return null;
    }
}

class Hora {
    private int hora;
    private int minuto;

    public int getHora() { return hora; }
    public int getMinuto() { return minuto; }
    public void setHora(int hora) { this.hora = hora; }
    public void setMinuto(int minuto) { this.minuto = minuto; }

    // Extrai hora e minuto de uma string
    public static Hora parseHora(String s) {
        Hora h = new Hora();
        Scanner sc = new Scanner(s);
        sc.useDelimiter(":");
        h.setHora(sc.nextInt());
        h.setMinuto(sc.nextInt());
        sc.close();
        return h;
    }

    // Transforma o restaurante formatado em um display de string para exibicao
    public String formatar() {
        return String.format("%02d:%02d", hora, minuto);
    }
}

class Data {
    private int ano;
    private int mes;
    private int dia;

    public int getAno() { return ano; }
    public int getMes() { return mes; }
    public int getDia() { return dia; }
    public void setAno(int ano) { this.ano = ano; }
    public void setMes(int mes) { this.mes = mes; }
    public void setDia(int dia) { this.dia = dia; }

    // Extrai ano, mes e dia de uma string
    public static Data parseData(String s) {
        Scanner sc = new Scanner(s);
        sc.useDelimiter("-");
        Data d = new Data();
        d.setAno(sc.nextInt());
        d.setMes(sc.nextInt());
        d.setDia(sc.nextInt());
        sc.close();
        return d;
    }

    // Transforma o restaurante formatado em um display de string para exibicao
    public String formatar() {
        return String.format("%02d/%02d/%04d", dia, mes, ano);
    }
}

class Restaurante {
    private int id;
    private String nome;
    private String cidade;
    private int capacidade;
    private double avaliacao;
    private String[] tiposCozinhas;
    private int faixaPreco;
    private Hora horarioAbertura;
    private Hora horarioFechamento;
    private Data dataAbertura;
    private boolean aberto;

    public int getId() { return id; }
    public String getNome() { return nome; }
    public String getCidade() { return cidade; }
    public int getCapacidade() { return capacidade; }
    public double getAvaliacao() { return avaliacao; }
    public String[] getTiposCozinha() { return tiposCozinhas; }
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
    public void setTiposCozinha(String[] tiposCozinhas) { this.tiposCozinhas = tiposCozinhas; }
    public void setFaixaPreco(int faixaPreco) { this.faixaPreco = faixaPreco; }
    public void setHorarioAbertura(Hora horarioAbertura) { this.horarioAbertura = horarioAbertura; }
    public void setHorarioFechamento(Hora horarioFechamento) { this.horarioFechamento = horarioFechamento; }
    public void setDataAbertura(Data dataAbertura) { this.dataAbertura = dataAbertura; }
    public void setAberto(boolean aberto) { this.aberto = aberto; }

    // Recebe uma linha CSV, faz a quebra dos atributos e monta a struct do Restaurante
    public static Restaurante parseRestaurante(String linha) {
        Scanner sc = new Scanner(linha);
        sc.useDelimiter(",");
        sc.useLocale(java.util.Locale.US);

        Restaurante r = new Restaurante();
        r.setId(sc.nextInt());
        r.setNome(sc.next());
        r.setCidade(sc.next());
        r.setCapacidade(sc.nextInt());
        r.setAvaliacao(sc.nextDouble());

        String temp = sc.next();
        String[] tiposCozinha = stringToArray(temp);
        r.setTiposCozinha(tiposCozinha);

        r.setFaixaPreco(sc.next().length());

        temp = sc.next();
        Scanner scHorario = new Scanner(temp);
        scHorario.useDelimiter("-");
        String hAbertura = scHorario.next();
        String hFechamento = scHorario.next();
        scHorario.close();
        r.setHorarioAbertura(Hora.parseHora(hAbertura));
        r.setHorarioFechamento(Hora.parseHora(hFechamento));

        r.setDataAbertura(Data.parseData(sc.next()));
        r.setAberto(sc.nextBoolean());

        sc.close();
        return r;
    }

    // Converte a string de tipos de cozinha para um array de strings
    public static String[] stringToArray(String s) {
        Scanner sc = new Scanner(s);
        sc.useDelimiter(";");
        int count = 0;
        while (sc.hasNext()) {
            sc.next();
            count++;
        }
        String[] resp = new String[count];
        sc = new Scanner(s);
        sc.useDelimiter(";");
        for (int i = 0; i < count; i++) {
            resp[i] = sc.next();
        }
        sc.close();
        return resp;
    }

    // Transforma o restaurante formatado em um display de string para exibicao
    public String formatar() {
        String tipos = "[";
        for (int i = 0; i < tiposCozinhas.length; i++) {
            tipos += tiposCozinhas[i];
            if (i < tiposCozinhas.length - 1)
                tipos += ",";
        }
        tipos += "]";

        String faixa = "";
        for (int i = 0; i < faixaPreco; i++)
            faixa += "$";

        return String.format("[%d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %s-%s ## %s ## %b]", 
            id, nome, cidade, capacidade, avaliacao, tipos, faixa, 
            horarioAbertura.formatar(), horarioFechamento.formatar(), dataAbertura.formatar(), aberto);
    }
}
