import java.util.Scanner;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

class Celula {
    public Restaurante restaurante;
    public Celula prox;

    public Celula() {
        this(null);
    }

    public Celula(Restaurante restaurante) {
        this.restaurante = restaurante;
        this.prox = null;
    }
}

public class tp3_06 {
    public static Celula topo;

    // Inicializa a estrutura de dados e seus ponteiros base
    public static void iniciar() {
        topo = null;
    }

    // Aloca e anexa o elemento na respectiva posicao da estrutura
    public static void inserir(Restaurante x) {
        Celula tmp = new Celula(x);
        tmp.prox = topo;
        topo = tmp;
    }

    // Desvincula e retorna o elemento da estrutura, atualizando os nos
    public static Restaurante remover() {
        if (topo == null) {
            return null;
        }
        Restaurante resp = topo.restaurante;
        Celula tmp = topo;
        topo = topo.prox;
        tmp.prox = null;
        return resp;
    }

    // Varre a estrutura imprimindo seus elementos na saida padrao
    public static void mostrar() {
        for (Celula i = topo; i != null; i = i.prox) {
            System.out.println(i.restaurante.formatar());
        }
    }

    public static void main(String[] args) {
        ColecaoRestaurantes c = ColecaoRestaurantes.lerCsv();
        Scanner sc = new Scanner(System.in);

        iniciar();

        int id;
        while ((id = sc.nextInt()) != -1) {
            Restaurante r = c.getRestauranteById(id);
            if (r != null) {
                inserir(r);
            }
        }

        if (sc.hasNextInt()) {
            int n = sc.nextInt();
            for (int i = 0; i < n; i++) {
                String comando = sc.next();
                if (comando.equals("I")) {
                    int r_id = sc.nextInt();
                    inserir(c.getRestauranteById(r_id));
                } else if (comando.equals("R")) {
                    Restaurante r = remover();
                    if (r != null) {
                        System.out.println("(R)" + r.getNome());
                    }
                }
            }
        }

        mostrar();

        sc.close();
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