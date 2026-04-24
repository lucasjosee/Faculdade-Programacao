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

        //---------------------Ex01---------------------//
        /* 
        int n;
        while((n = sc.nextInt()) != -1)
        {
            
            for(int i = 0; i < tamanho; i++)
            {
                if(restaurantes[i].getId() == id)
                {
                    System.out.println(restaurantes[i].formatar());
                    i = tamanho;
                }
            }
        }
        */
        
        //---------------------Ex04---------------------//i
        /*
        long inicio = System.currentTimeMillis();

        Restaurantes[] selecionados = separarRestaurantes(c, sc);

        insertionSort(selecionados, totalIds, inicio);
        
        //Imprimi os ids
        for(int i = 0; i < totalIds; i++)
        {
            System.out.println(selecionados[i].formatar());
        }
        */

        //---------------------Ex05---------------------//
        /*
        long inicio = System.currentTimeMillis();

        Restaurante[] selecionados = separarRestaurantes(c, sc);
        
        sc.nextLine();

        String linha;
        while((linha = sc.nextLine()).compareTo("FIM") != 0)
        {    
            System.out.println(pesquisaSequencial(selecionados, linha, inicio));
        }
        */

        //---------------------Ex07---------------------//
        long inicio = System.TimeMillis();
        
        Restaurante[] selecionados = separarRestaurantes(c, sc);

        

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

    //---------------------Pesquisa Sequencial----------------------//
    public static String pesquisaSequencial(Restaurante[] selecionados, String nome, long inicio)
    {
        int comparacoes = 0;
        int tamanho = selecionados.length;

        int flag = 0;
        for(int i = 0; i < tamanho; i++)
        {
            comparacoes++;
            if(nome.compareTo(selecionados[i].getNome()) == 0)
            {
                flag = 1;
                i = tamanho;
            }
        }
        long tempo = System.currentTimeMillis() - inicio;
        gerarLog("892665", "Pesquisa Sequencial", comparacoes, 0, tempo);
        
        if(flag == 1)
            return "SIM";
        else
            return "NAO";
    }


    //---------------------Sorts----------------------//
    public static void insertionSort(Restaurante[] restaurantes, int tamanho, long inicio)
    {
        int comparacoes = 0;
        int movimentacoes = 0;
        for(int i = 1; i < tamanho; i++)
        {
            int j = i;
            Restaurante menor = restaurantes[j];
            while(j > 0)
            {
                comparacoes++;
                int cmp = menor.getCidade().compareToIgnoreCase(restaurantes[j-1].getCidade());
                if(cmp < 0)
                {
                    restaurantes[j] = restaurantes[j - 1];
                    movimentacoes++;
                    j--;
                }
                else
                {
                    j = 0;
                }
            }

            restaurantes[j] = menor;
            movimentacoes++;
        }

        long tempo = System.currentTimeMillis() - inicio;
        gerarLog("892665", "insercao", comparacoes, movimentacoes, tempo);
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

        //Como a faixa de preço está salva como int, aqui transformamos o int em um string ed $
        String faixa = "";
        for(int i = 0; i < faixaPreco; i++)
            faixa += "$";

        return String.format("[%d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %s-%s ## %s ## %b]", id, nome, cidade, capacidade, avaliacao, tipos, faixa, horarioAbertura.formatar(), horarioFechamento.formatar(), dataAbertura.formatar(), aberto);
    }
    
}
/*-------------------------------------------------------------------------------------------------------*/






