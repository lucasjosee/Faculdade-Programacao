import java.io.*;
import java.util.*;

class Game {
    int id;
    String name;
    String releaseDate;
    int estimatedOwners;
    float price;
    String[] supportedLanguages;
    int metacriticScore;
    float userScore;
    int achievements;
    String[] publishers;
    String[] developers;
    String[] categories;
    String[] genres;
    String[] tags;

    static int inicio = 0;

    Game(int id, String name, String releaseDate, int estimatedOwners, float price,
         String[] supportedLanguages, int metacriticScore, float userScore, int achievements,
         String[] publishers, String[] developers, String[] categories, String[] genres, String[] tags) {
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
}

class Celula {
    Game elemento;
    Celula prox;
    Celula(Game g) {
        this.elemento = g;
        this.prox = null;
    }
}

class Fila {
    Celula primeiro;
    Celula ultimo;

    Fila() {
        primeiro = new Celula(null);
        ultimo = primeiro;
    }

    void enfileirar(Game g) {
        ultimo.prox = new Celula(g);
        ultimo = ultimo.prox;
    }

    Game desenfileirar() throws Exception {
        if (primeiro == ultimo) throw new Exception();
        Celula tmp = primeiro.prox;
        primeiro.prox = tmp.prox;
        if (tmp == ultimo) ultimo = primeiro;
        return tmp.elemento;
    }
}

public class TP06Q04 {

    public static void main(String[] args) throws Exception {

        Scanner sc = new Scanner(System.in);
        Fila fila = new Fila();

        String entrada = sc.nextLine();
        while (!entrada.equals("FIM")) {
            fila.enfileirar(lerGamePorId(stringParaInt(entrada)));
            entrada = sc.nextLine();
        }

        int n = stringParaInt(sc.nextLine());

        for (int i = 0; i < n; i++) {
            String cmd = sc.next();
            if (cmd.equals("I")) {
                String id = sc.next();
                fila.enfileirar(lerGamePorId(stringParaInt(id)));
            } else if (cmd.equals("R")) {
                Game g = fila.desenfileirar();
                System.out.println("(R) " + g.name);
            }
        }

        Celula tmp = fila.primeiro.prox;
        while (tmp != null) {
            System.out.println(tmp.elemento.name);
            tmp = tmp.prox;
        }

        sc.close();
    }

    public static Game lerGamePorId(int idProcurado) {
        BufferedReader br = null;
        try {
            br = new BufferedReader(new FileReader("/tmp/games.csv"));
            br.readLine();
            String linha = br.readLine();
            while (linha != null) {
                Game.inicio = 0;
                int id = stringParaInt(proximoCampo(linha));
                if (id == idProcurado) {

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

                    return new Game(id, nome, data, donos, preco, linguas, meta, user,
                            conquistas, pubs, devs, cats, gens, tags);
                }
                linha = br.readLine();
            }
        } catch (Exception e) {}
        try { if (br != null) br.close(); } catch (Exception e) {}
        return null;
    }

    public static String proximoCampo(String linha) {
        int i = Game.inicio;
        if (i >= linha.length()) return "";
        String campo = "";
        boolean aspas = false;

        if (linha.charAt(i) == '"') {
            aspas = true;
            i++;
        }

        while (i < linha.length()) {
            char c = linha.charAt(i);
            if (aspas && c == '"') { i++; break; }
            else if (!aspas && c == ',') break;
            campo += c;
            i++;
        }

        if (i < linha.length() && linha.charAt(i) == ',') i++;
        Game.inicio = i;
        return campo;
    }

    public static String[] stringParaArray(String s) {
        if (s == null) return new String[0];
        ArrayList<String> out = new ArrayList<>();
        String atual = "";
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == ',' || c == ';') {
                if (atual.length() > 0) out.add(atual.trim());
                atual = "";
            } else if (c != '[' && c != ']' && c != '\'' && c != '"') {
                atual += c;
            }
        }
        if (atual.length() > 0) out.add(atual.trim());
        return out.toArray(new String[out.size()]);
    }

    public static String formatarData(String s) {
        if (s.length() == 4) return "01/01/" + s;
        String mes = "", dia = "", ano = "";
        int parte = 0;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == ' ') parte++;
            else if (parte == 0) mes += c;
            else if (parte == 1 && c != ',') dia += c;
            else if (parte == 2) ano += c;
        }
        if (dia.equals("")) dia = "01";
        String[] meses = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
        int mesNum = 1;
        for (int i = 0; i < 12; i++)
            if (mes.equals(meses[i])) mesNum = i + 1;
        return (dia.length()==1?"0"+dia:dia) + "/" +
               (mesNum<10?"0"+mesNum:mesNum) + "/" + ano;
    }

    public static int stringParaInt(String s) {
        int num = 0;
        for (int i = 0; i < s.length(); i++)
            if (s.charAt(i) >= '0' && s.charAt(i) <= '9')
                num = num * 10 + (s.charAt(i) - '0');
        return num;
    }

    public static float stringParaFloat(String s) {
        float num = 0;
        int div = 1;
        boolean decimal = false;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == '.') decimal = true;
            else if (c >= '0' && c <= '9') {
                num = num * 10 + (c - '0');
                if (decimal) div *= 10;
            }
        }
        return num / div;
    }
}
