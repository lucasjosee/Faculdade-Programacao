import java.io.*;
import java.util.*;

public class Game 
{
    // atributos
    private int id;
    private String name;
    private String releaseDate;
    private int estimatedOwners;
    private float price;
    private String[] supportedLanguages;
    private int metacriticScore;
    private float userScore;
    private int achievements;
    private String[] publishers;
    private String[] developers;
    private String[] categories;
    private String[] genres;
    private String[] tags;

    public static int inicio = 0;
    public static long comparacoes = 0;
    public static long movimentacoes = 0;

    // construtor padrão
    public Game() {}

    // construtor completo
    public Game(int id, String name, String releaseDate, int estimatedOwners, float price, String[] supportedLanguages,
                int metacriticScore, float userScore, int achievements, String[] publishers, String[] developers,
                String[] categories, String[] genres, String[] tags) 
    {
        this.id = id;
        this.name = name;
        this.releaseDate = releaseDate;
        this.estimatedOwners = estimatedOwners;
        this.price = price;
        this.supportedLanguages = supportedLanguages;
        this.metacriticScore = metacriticScore;
        this.userScore = userScore;
        this.achievements = achievements;
        this.publishers = publishers;
        this.developers = developers;
        this.categories = categories;
        this.genres = genres;
        this.tags = tags;
    }

    // getters
    public int getId() { return id; }
    public float getPrice() { return price; }

    // método para imprimir o jogo completo
    public void mostrar() 
    {
        System.out.print("=> " + id + " ## " + name + " ## " + releaseDate + " ## " + estimatedOwners + " ## " + price + " ## ");
        System.out.print(Arrays.toString(supportedLanguages) + " ## ");
        System.out.print(metacriticScore + " ## " + userScore + " ## " + achievements + " ## ");
        System.out.print(Arrays.toString(publishers) + " ## ");
        System.out.print(Arrays.toString(developers) + " ## ");
        System.out.print(Arrays.toString(categories) + " ## ");
        System.out.print(Arrays.toString(genres) + " ## ");
        System.out.print(Arrays.toString(tags) + " ##\n");
    }

    // ===================== MAIN =====================
    public static void main(String[] args) throws Exception 
    {


        Scanner sc = new Scanner(System.in);

        // corrige problema de acentuação no console
        try {
            System.setOut(new PrintStream(new FileOutputStream(FileDescriptor.out), true, "UTF-8"));
        } catch (Exception e) {}

        Game[] jogos = new Game[5000];
        int count = 0;

        // leitura dos IDs até FIM
        String entrada = sc.nextLine();
        while (!entrada.equals("FIM")) 
        {
            int id = stringParaInt(entrada);
            Game g = lerGamePorId(id);
            if (g != null) jogos[count++] = g;
            entrada = sc.nextLine();
        }

        long inicioTempo = System.currentTimeMillis();

        // ordena com MergeSort
        mergeSort(jogos, 0, count - 1);

        long fimTempo = System.currentTimeMillis();
        double tempo = (fimTempo - inicioTempo) / 1000.0;

        // imprime as 5 linhas completas mais caras
        System.out.println("| 5 pre\u00E7os mais caros |");
        for (int i = count - 1; i >= count - 5 && i >= 0; i--) 
        {
            jogos[i].mostrar();
        }

        // imprime as 5 linhas completas mais baratas
        System.out.println();
        System.out.println("| 5 pre\u00E7os mais baratos |");
        for (int i = 0; i < 5 && i < count; i++) 
        {
            jogos[i].mostrar();
        }

        // cria log
        FileWriter fw = new FileWriter("892665_mergesort.txt");
        fw.write("892665\t" + comparacoes + "\t" + movimentacoes + "\t" + tempo);
        fw.close();

        sc.close();
    }

    // ===================== MERGESORT =====================
    public static void mergeSort(Game[] array, int esq, int dir) 
    {
        if (esq < dir) 
        {
            int meio = (esq + dir) / 2;
            mergeSort(array, esq, meio);
            mergeSort(array, meio + 1, dir);
            intercalar(array, esq, meio, dir);
        }
    }

    // intercala duas metades ordenadas
    public static void intercalar(Game[] array, int esq, int meio, int dir) 
    {
        int n1 = meio - esq + 1;
        int n2 = dir - meio;

        Game[] esquerda = new Game[n1];
        Game[] direita = new Game[n2];

        for (int i = 0; i < n1; i++) esquerda[i] = array[esq + i];
        for (int j = 0; j < n2; j++) direita[j] = array[meio + 1 + j];

        int i = 0, j = 0, k = esq;

        while (i < n1 && j < n2) 
        {
            comparacoes++;
            if (compararGames(esquerda[i], direita[j]) <= 0) 
            {
                array[k] = esquerda[i];
                i++;
            } 
            else 
            {
                array[k] = direita[j];
                j++;
            }
            movimentacoes++;
            k++;
        }

        while (i < n1) 
        {
            array[k++] = esquerda[i++];
            movimentacoes++;
        }

        while (j < n2) 
        {
            array[k++] = direita[j++];
            movimentacoes++;
        }
    }

    // compara por preço e desempata por id
    public static int compararGames(Game a, Game b) 
    {
        if (a.getPrice() < b.getPrice()) return -1;
        else if (a.getPrice() > b.getPrice()) return 1;
        else 
        {
            if (a.getId() < b.getId()) return -1;
            else if (a.getId() > b.getId()) return 1;
            else return 0;
        }
    }

    // ===================== LEITURA DO CSV =====================
    public static Game lerGamePorId(int idProcurado) 
    {
        BufferedReader br = null;
        try 
        {
            br = new BufferedReader(new FileReader("/tmp/games.csv"));
            br.readLine(); 
            String linha = br.readLine();

            while (linha != null) 
            {
                inicio = 0;
                String idStr = proximoCampo(linha);
                int id = stringParaInt(idStr);

                if (id == idProcurado) 
                {
                    String nome = proximoCampo(linha);
                    String data = formatarData(proximoCampo(linha));
                    int donos = stringParaInt(proximoCampo(linha));
                    float preco = stringParaFloat(proximoCampo(linha));
                    String[] linguas = stringParaArray(proximoCampo(linha));
                    int meta = stringParaInt(proximoCampo(linha));
                    float user = stringParaFloat(proximoCampo(linha));
                    int conquistas = stringParaInt(proximoCampo(linha));
                    String[] pubs = stringParaArray(proximoCampo(linha));
                    String[] devs = stringParaArray(proximoCampo(linha));
                    String[] cats = stringParaArray(proximoCampo(linha));
                    String[] gens = stringParaArray(proximoCampo(linha));
                    String[] tags = stringParaArray(proximoCampo(linha));

                    return new Game(id, nome, data, donos, preco, linguas, meta, user, conquistas, pubs, devs, cats, gens, tags);
                }
                linha = br.readLine();
            }

        } catch (IOException e) {
            System.out.println("Erro ao ler o arquivo.");
        } finally {
            try { if (br != null) br.close(); } catch (IOException e) {}
        }
        return null;
    }

    // ===================== AUXILIARES =====================
    public static String proximoCampo(String linha) 
    {
        if (inicio >= linha.length()) return "";
        String campo = "";
        int i = inicio;
        boolean aspas = false;

        if (linha.charAt(i) == '"') { aspas = true; i++; }

        while (i < linha.length()) 
        {
            char c = linha.charAt(i);
            if (aspas && c == '"') { i++; break; }
            else if (!aspas && c == ',') break;
            else { campo += c; i++; }
        }

        if (i < linha.length() && linha.charAt(i) == ',') i++;
        inicio = i;
        return campo;
    }

    public static String formatarData(String s) 
    {
        if (s.length() == 4) return "01/01/" + s;
        String mes = "", dia = "", ano = "";
        int parte = 0;

        for (int i = 0; i < s.length(); i++) 
        {
            char c = s.charAt(i);
            if (c == ' ') parte++;
            else if (parte == 0) mes += c;
            else if (parte == 1 && c != ',') dia += c;
            else if (parte == 2) ano += c;
        }

        if (dia.equals("")) dia = "01";
        int mesNum = 1;
        String[] meses = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
        for (int i = 0; i < 12; i++) if (mes.equals(meses[i])) mesNum = i + 1;

        String mesStr = (mesNum < 10 ? "0" + mesNum : "" + mesNum);
        return (dia.length() == 1 ? "0" + dia : dia) + "/" + mesStr + "/" + ano;
    }

    public static String[] stringParaArray(String s) 
    {
        String[] temp = new String[50];
        int cont = 0;
        String atual = "";
        for (int i = 0; i < s.length(); i++) 
        {
            char c = s.charAt(i);
            if (c == ',' || c == ';') 
            {
                if (atual.length() > 0) 
                {
                    temp[cont] = atual.trim();
                    cont++;
                    atual = "";
                }
            } 
            else if (c != '[' && c != ']' && c != '\'' && c != '\"') atual += c;
        }
        if (atual.length() > 0) temp[cont++] = atual.trim();

        String[] res = new String[cont];
        for (int i = 0; i < cont; i++) res[i] = temp[i];
        return res;
    }

    public static int stringParaInt(String s) 
    {
        int n = 0;
        for (int i = 0; i < s.length(); i++) 
        {
            char c = s.charAt(i);
            if (c >= '0' && c <= '9') n = n * 10 + (c - '0');
        }
        return n;
    }

    public static float stringParaFloat(String s) 
    {
        float num = 0;
        int divisor = 1;
        boolean decimal = false;
        for (int i = 0; i < s.length(); i++) 
        {
            char c = s.charAt(i);
            if (c == '.') decimal = true;
            else if (c >= '0' && c <= '9') 
            {
                num = num * 10 + (c - '0');
                if (decimal) divisor *= 10;
            }
        }
        return num / divisor;
    }
}
