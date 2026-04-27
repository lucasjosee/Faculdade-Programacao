import java.util.Scanner;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.BufferedWriter;
import java.io.FileWriter;

public class main
{
    public static void main(String[] args)
    {
        ColecaoRestaurantes c = ColecaoRestaurantes.lerCsv();
        Scanner sc = new Scanner(System.in);

        Restaurante[] selecionados = separarRestaurantes(c, sc);
        int[] comparacoes = {0};
        int[] movimentacoes = {0};

        long inicio = System.currentTimeMillis();
        mergeSort(selecionados, 0, selecionados.length - 1, comparacoes, movimentacoes);
        long tempo = System.currentTimeMillis() - inicio;

        for(int i = 0; i < selecionados.length; i++)
        {
            System.out.println(selecionados[i].formatar());
        }

        gerarLog("892665", "MergeSort", comparacoes[0], movimentacoes[0], tempo);

        sc.close();
    }

    //Le os ids que vão ser processados e devolve o array pronto para a main
    public static Restaurante[] separarRestaurantes(ColecaoRestaurantes c, Scanner sc)
    {
        int[] ids = new int[c.getTamanho()];
        int totalIds = 0;
        int n;

        while((n = sc.nextInt()) != -1)
        {
            ids[totalIds++] = n;
        }

        Restaurante[] selecionados = new Restaurante[totalIds];

        for(int i = 0; i < totalIds; i++)
        {
            for(int j = 0; j < c.getTamanho(); j++)
            {
                if(c.getRestaurantes()[j].getId() == ids[i])
                {
                    selecionados[i] = c.getRestaurantes()[j];
                    j = c.getTamanho();
                }
            }
        }
        return selecionados;
    }

    //Função que gera o arquivo de log
    public static void gerarLog(String matricula, String algoritmo, int comparacoes, int movimentacoes, long tempo)
    {
        try
        {
            BufferedWriter bw = new BufferedWriter(new FileWriter(matricula + "_" + algoritmo + ".txt"));
            bw.write(matricula + "\t" + comparacoes + "\t" + movimentacoes + "\t" + tempo);
            bw.close();
        }
        catch(IOException e)
        {
            System.out.println("Erro ao gerar log: " + e.getMessage());
        }
    }

    //---------------------MergeSort----------------------//

    public static void mergeSort(Restaurante[] restaurantes, int esq, int dir, int[] comparacoes, int[] movimentacoes)
    {
        if(esq < dir)
        {
            int meio = (esq + dir) / 2;
            mergeSort(restaurantes, esq, meio, comparacoes, movimentacoes);
            mergeSort(restaurantes, meio + 1, dir, comparacoes, movimentacoes);
            intercalar(restaurantes, esq, meio, dir, comparacoes, movimentacoes);
        }
    }

    public static void intercalar(Restaurante[] restaurantes, int esq, int meio, int dir, int[] comparacoes, int[] movimentacoes)
    {
        int n1, n2, i, j, k;

        n1 = meio - esq + 1;
        n2 = dir - meio;

        Restaurante[] a1 = new Restaurante[n1];
        Restaurante[] a2 = new Restaurante[n2];

        for(i = 0; i < n1; i++)
            a1[i] = restaurantes[esq + i];

        for(j = 0; j < n2; j++)
            a2[j] = restaurantes[meio + j + 1];

        i = 0; j = 0; k = esq;
        while(i < n1 && j < n2)
        {
            int cmp = a1[i].getCidade().compareTo(a2[j].getCidade());
            comparacoes[0]++;
            if(cmp < 0)
            {
                restaurantes[k++] = a1[i++];
                movimentacoes[0]++;
            }
            else if(cmp > 0)
            {
                restaurantes[k++] = a2[j++];
                movimentacoes[0]++;
            }
            else
            {
                cmp = a1[i].getNome().compareTo(a2[j].getNome());
                comparacoes[0]++;
                if(cmp < 0)
                {
                    restaurantes[k++] = a1[i++];
                    movimentacoes[0]++;
                }
                else
                {
                    restaurantes[k++] = a2[j++];
                    movimentacoes[0]++;
                }
            }
        }

        while(i < n1)
        {
            restaurantes[k++] = a1[i++];
            movimentacoes[0]++;
        }
        while(j < n2)
        {
            restaurantes[k++] = a2[j++];
            movimentacoes[0]++;
        }
    }
}

//Classes Principais
/*-------------------------------------------------------------------------------------------------------*/
class ColecaoRestaurantes
{
    //atributos
    private int tamanho;
    private Restaurante[] restaurantes;

    //getters
    public int getTamanho(){return tamanho;}
    public Restaurante[] getRestaurantes(){return restaurantes;}

    public void lerCsv(String path)
    {
        BufferedReader br = null;
        try
        {
            br = new BufferedReader(new FileReader(path));

            String linha;
            int cont = 0;

            br.readLine(); //Pula a primeira linha
            while((linha = br.readLine()) != null)
            {
                cont++;
            }

            tamanho = cont;

            restaurantes = new Restaurante[cont];

            br = new BufferedReader(new FileReader(path));

            int i = 0;

            br.readLine();
            while((linha = br.readLine()) != null)
            {
                restaurantes[i] = Restaurante.parseRestaurante(linha);
                i++;
            }
        }
        catch(IOException e)
        {
            System.out.println("Erro ao ler arquivo: " + e.getMessage());
        }
    }

    public static ColecaoRestaurantes lerCsv()
    {
        ColecaoRestaurantes c = new ColecaoRestaurantes();
        c.lerCsv("/tmp/restaurantes.csv");
        return c;
    }

}

class Hora
{
    private int hora;
    private int minuto;

    //getters
    public int getHora(){return hora;}
    public int getMinuto(){return minuto;}

    //setters
    public void setHora(int hora){this.hora = hora;}
    public void setMinuto(int minuto){this.minuto = minuto;}

    //metodos
    public static Hora parseHora(String s)
    {
        Hora h = new Hora();
        Scanner sc = new Scanner(s);
        sc.useDelimiter(":");

        h.setHora(sc.nextInt());
        h.setMinuto(sc.nextInt());

        sc.close();
        return h;
    }

    public String formatar()
    {
        return String.format("%02d:%02d", hora, minuto);
    }
}

class Data
{
    //atributos
    private int ano;
    private int mes;
    private int dia;

    //getters
    public int getAno(){return ano;}
    public int getMes(){return mes;}
    public int getDia(){return dia;}

    //setters
    public void setAno(int ano){this.ano = ano;}
    public void setMes(int mes){this.mes = mes;}
    public void setDia(int dia){this.dia = dia;}

    //metodos
    public static Data parseData(String s)
    {
        Scanner sc = new Scanner(s);
        sc.useDelimiter("-");

        Data d = new Data();
        d.setAno(sc.nextInt());
        d.setMes(sc.nextInt());
        d.setDia(sc.nextInt());

        return d;
    }

    public String formatar()
    {
        return String.format("%02d/%02d/%04d", dia, mes, ano);
    }
}

class Restaurante
{
    //atributos
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

    //Getters
    public int getId(){return id;}
    public String getNome(){return nome;}
    public String getCidade(){return cidade;}
    public int getCapacidade(){return capacidade;}
    public double getAvaliacao(){return avaliacao;}
    public String[] getTiposCozinha(){return tiposCozinhas;}
    public int getFaixaPreco(){return faixaPreco;}
    public Hora getHorarioAbertura(){return horarioAbertura;}
    public Hora getHorarioFechamento(){return horarioFechamento;}
    public Data getDataAbertura(){return dataAbertura;}
    public boolean getAberto(){return aberto;}

    //Setters
    public void setId(int id) {this.id = id;}
    public void setNome(String nome) {this.nome = nome;}
    public void setCidade(String cidade) {this.cidade = cidade;}
    public void setCapacidade(int capacidade) {this.capacidade = capacidade;}
    public void setAvaliacao(double avaliacao) {this.avaliacao = avaliacao;}
    public void setTiposCozinha(String[] tiposCozinhas) {this.tiposCozinhas = tiposCozinhas;}
    public void setFaixaPreco(int faixaPreco) {this.faixaPreco = faixaPreco;}
    public void setHorarioAbertura(Hora horarioAbertura) {this.horarioAbertura = horarioAbertura;}
    public void setHorarioFechamento(Hora horarioFechamento) {this.horarioFechamento = horarioFechamento;}
    public void setDataAbertura(Data dataAbertura) {this.dataAbertura = dataAbertura;}
    public void setAberto(boolean aberto) {this.aberto = aberto;}

    //Metodos
    public static Restaurante parseRestaurante(String linha)
    {
        //Scanner que varre a string e vai parando nas virgulas
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

        r.setFaixaPreco(sc.next().length()); //Le $$$ e retorna o tamanho

        //Parse da hora
        temp = sc.next();
        Scanner scHorario = new Scanner(temp);
        scHorario.useDelimiter("-");
        String hAbertura = scHorario.next();
        String hFechamento = scHorario.next();
        scHorario.close();
        r.setHorarioAbertura(Hora.parseHora(hAbertura));
        r.setHorarioFechamento(Hora.parseHora(hFechamento));

        //Parse da data
        r.setDataAbertura(Data.parseData(sc.next()));

        r.setAberto(sc.nextBoolean());

        sc.close();

        return r;
    }

    public static String[] stringToArray(String s)
    {
        //Scanner varra string s e vai parando nos ;
        Scanner sc = new Scanner(s);
        sc.useDelimiter(";");

        int count = 0;
        while(sc.hasNext())
        {
            sc.next();
            count++;
        }

        String[] resp = new String[count];
        sc = new Scanner(s);
        sc.useDelimiter(";");
        for(int i = 0; i < count; i++)
        {
            resp[i] = sc.next();
        }

        sc.close();

        return resp;
    }

    public String formatar()
    {
        //Preenche a string tipos, para que o array de tiposCozinha possa ser imprimido
        String tipos = "[";
        for(int i = 0; i < tiposCozinhas.length; i++)
        {
            tipos += tiposCozinhas[i];
            if(i < tiposCozinhas.length - 1)
                tipos += ",";
        }
        tipos += "]";

        //Como a faixa de preço está salva como int, aqui transformamos o int em um string de $
        String faixa = "";
        for(int i = 0; i < faixaPreco; i++)
            faixa += "$";

        return String.format("[%d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %s-%s ## %s ## %b]", id, nome, cidade, capacidade, avaliacao, tipos, faixa, horarioAbertura.formatar(), horarioFechamento.formatar(), dataAbertura.formatar(), aberto);
    }

}
/*-------------------------------------------------------------------------------------------------------*/
