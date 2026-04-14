import java.io.*;
import java.util.*;

public class Main {

    public static int inicio = 0;

    // ==========================================================
    // Classe Game (mesmo padrão do TP06Q03)
    // ==========================================================
    static class Game {
        int id;
        String name;
        String releaseDate;
        int estimatedOwners;
        float price;
        String supportedLanguages;
        int metacriticScore;
        float userScore;
        int achievements;
        String publishers;
        String developers;
        String categories;
        String genres;
        String tags;
    }

    // ==========================================================
    // Célula da Fila
    // ==========================================================
    static class Celula {
        Game g;
        Celula prox;
        Celula(Game g) { this.g = g; }
    }

    // ==========================================================
    // Fila Dinâmica (FIFO)
    // ==========================================================
    static class Fila {
        Celula primeiro;
        Celula ultimo;

        Fila() {
            primeiro = ultimo = null;
        }

        void enfileirar(Game g) {
            Celula tmp = new Celula(g);

            if (primeiro == null) {
               primeiro = ultimo = tmp;
            } else {
               ultimo.prox = tmp;
               ultimo = tmp;
            }
        }

        Game desenfileirar() {
            if (primeiro == null) return null;

            Game resp = primeiro.g;
            primeiro = primeiro.prox;

            if (primeiro == null)
                ultimo = null;

            return resp;
        }

        void imprimirFinal() {
            Celula tmp = primeiro;
            while (tmp != null) {
                imprimirGame(tmp.g);
                tmp = tmp.prox;
            }
        }
    }

    // ==========================================================
    // Impressão completa (mesma do TP06Q03)
    // ==========================================================
    static void imprimirGame(Game g) {
        System.out.println(
            "=> " + g.id + " ## " + g.name + " ## " + g.releaseDate +
            " ## " + g.estimatedOwners + " ## " + g.price + " ## [" +
            g.supportedLanguages + "] ## " + g.metacriticScore + " ## " +
            g.userScore + " ## " + g.achievements + " ## [" +
            g.publishers + "] ## [" + g.developers + "] ## [" +
            g.categories + "] ## [" + g.genres + "] ## [" + g.tags + "] ##"
        );
    }

    // ==========================================================
    // Leitura do CSV (idêntica ao TP06Q03)
    // ==========================================================
    static Game lerGamePorId(int idProcurado) {

        try {
            BufferedReader br = new BufferedReader(new FileReader("/tmp/games.csv"));

            String linha = br.readLine(); // pula cabeçalho
            linha = br.readLine();

            while (linha != null) {

                inicio = 0;

                int id = stringParaInt(proximoCampo(linha));

                if (id == idProcurado) {

                    Game g = new Game();
                    g.id = id;
                    g.name = proximoCampo(linha);

                    String dataBruta = proximoCampo(linha);
                    g.releaseDate = formatarData(dataBruta);

                    g.estimatedOwners = stringParaInt(proximoCampo(linha));
                    g.price = stringParaFloat(proximoCampo(linha));
                    g.supportedLanguages = proximoCampo(linha);
                    g.metacriticScore = stringParaInt(proximoCampo(linha));
                    g.userScore = stringParaFloat(proximoCampo(linha));
                    g.achievements = stringParaInt(proximoCampo(linha));
                    g.publishers = proximoCampo(linha);
                    g.developers = proximoCampo(linha);
                    g.categories = proximoCampo(linha);
                    g.genres = proximoCampo(linha);
                    g.tags = proximoCampo(linha);

                    br.close();
                    return g;
                }

                linha = br.readLine();
            }

            br.close();
        } catch (Exception e) {}

        return null;
    }

    // ==========================================================
    // Funções auxiliares — iguais ao TP06Q03
    // ==========================================================
    static String proximoCampo(String linha) {
        if (inicio >= linha.length()) return "";

        String resp = "";
        int i = inicio;
        boolean aspas = false;

        if (linha.charAt(i) == '"') {
            aspas = true;
            i++;
        }

        while (i < linha.length()) {
            char c = linha.charAt(i);

            if (aspas && c == '"') {
                i++;
                break;
            }

            if (!aspas && c == ',') break;

            resp += c;
            i++;
        }

        if (i < linha.length() && linha.charAt(i) == ',') i++;

        inicio = i;
        return resp;
    }

    static String formatarData(String s) {

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

        String[] meses = {
            "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"
        };

        int mesNum = 1;
        for (int i = 0; i < 12; i++)
            if (mes.equals(meses[i])) mesNum = i + 1;

        if (dia.length() == 1) dia = "0" + dia;

        return dia + "/" + (mesNum < 10 ? "0" + mesNum : mesNum) + "/" + ano;
    }

    static int stringParaInt(String s) {
        int num = 0;
        for (int i = 0; i < s.length(); i++)
            if (s.charAt(i) >= '0' && s.charAt(i) <= '9')
                num = num * 10 + (s.charAt(i) - '0');
        return num;
    }

    static float stringParaFloat(String s) {
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

    // ==========================================================
    // MAIN — TP06Q04 COMPLETO
    // ==========================================================
    public static void main(String[] args) throws Exception {

        Scanner sc = new Scanner(System.in);
        Fila fila = new Fila();

        String entrada = sc.nextLine();

        while (!entrada.equals("FIM")) {
            int id = stringParaInt(entrada);
            Game g = lerGamePorId(id);

            if (g != null) fila.enfileirar(g);

            entrada = sc.nextLine();
        }

        int n = stringParaInt(sc.nextLine());

        for (int i = 0; i < n; i++) {

            String comando = sc.next();

            if (comando.equals("I")) {
                int id = stringParaInt(sc.next());
                fila.enfileirar(lerGamePorId(id));
            }
            else if (comando.equals("R")) {
                Game removido = fila.desenfileirar();
                System.out.println("(R) " + removido.name);
            }
        }

        fila.imprimirFinal();

        sc.close();
    }
}
