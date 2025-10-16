import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.Scanner;

public class Game {

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

    public Game() {}

    public Game(int id, String name, String releaseDate, int estimatedOwners, float price, String[] supportedLanguages, int metacriticScore, float userScore, int achievements, String[] publishers, String[] developers, String[] categories, String[] genres, String[] tags) {
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

    public void mostrar() {
        System.out.print("=> " + this.id + " ## " + this.name + " ## " + this.releaseDate + " ## " + this.estimatedOwners + " ## " + this.price + " ## ");
        System.out.print(Arrays.toString(this.supportedLanguages) + " ## ");
        System.out.print(this.metacriticScore + " ## " + this.userScore + " ## " + this.achievements + " ## ");
        System.out.print(Arrays.toString(this.publishers) + " ## ");
        System.out.print(Arrays.toString(this.developers) + " ## ");
        System.out.print(Arrays.toString(this.categories) + " ## ");
        System.out.print(Arrays.toString(this.genres) + " ## ");
        System.out.print(Arrays.toString(this.tags) + " ##\n");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String idDeEntrada;

        while (!(idDeEntrada = scanner.nextLine()).equalsIgnoreCase("FIM")) {
            if (idDeEntrada.isEmpty()) continue;
            int idParaBuscar = stringParaInt(idDeEntrada);
            boolean encontrado = false;

            try (BufferedReader br = new BufferedReader(new FileReader("/tmp/games.csv"))) {
                br.readLine();
                String linha;

                while ((linha = br.readLine()) != null) {
                    inicio = 0;
                    String idStr = proximoCampo(linha);
                    int idAtual = stringParaInt(idStr);

                    if (idAtual == idParaBuscar) {
                        String nomeStr = proximoCampo(linha);
                        String dataStr = proximoCampo(linha);
                        String donosStr = proximoCampo(linha);
                        String precoStr = proximoCampo(linha);
                        String linguasStr = proximoCampo(linha);
                        String metaScoreStr = proximoCampo(linha);
                        String userScoreStr = proximoCampo(linha);
                        String conquistasStr = proximoCampo(linha);
                        String publishersStr = proximoCampo(linha);
                        String developersStr = proximoCampo(linha);
                        String categoriesStr = proximoCampo(linha);
                        String genresStr = proximoCampo(linha);
                        String tagsStr = proximoCampo(linha);
                        
                        String dataFormatada = formatarData(dataStr);
                        int donos = stringParaInt(donosStr.substring(donosStr.indexOf('-') + 1).trim());
                        float preco = precoStr.equalsIgnoreCase("Free to Play") ? 0.0f : stringParaFloat(precoStr);
                        String[] linguas = stringParaArray(linguasStr);
                        int metaScore = stringParaInt(metaScoreStr);
                        float userScore = userScoreStr.equalsIgnoreCase("tbd") ? -1.0f : stringParaFloat(userScoreStr);
                        int conquistas = stringParaInt(conquistasStr);
                        String[] publishers = stringParaArray(publishersStr);
                        String[] developers = stringParaArray(developersStr);
                        String[] categories = stringParaArray(categoriesStr);
                        String[] genres = stringParaArray(genresStr);
                        String[] tags = stringParaArray(tagsStr);

                        Game jogo = new Game(idAtual, nomeStr, dataFormatada, donos, preco, linguas, metaScore, userScore, conquistas, publishers, developers, categories, genres, tags);
                        jogo.mostrar();
                        encontrado = true;
                        break;
                    }
                }
            } catch (IOException e) {
                System.err.println("Erro ao ler o arquivo GAMES.CSV: " + e.getMessage());
            }

            if (!encontrado) {
                 System.out.println("ID " + idParaBuscar + " nao encontrado.");
            }
        }
        scanner.close();
    }

    public static String proximoCampo(String linha) {
        if (inicio >= linha.length()) return "";
        
        String campo = "";
        int i = inicio;
        boolean dentroDeAspas = false;

        if (linha.charAt(i) == '"') {
            dentroDeAspas = true;
            i++;
        }

        while (i < linha.length()) {
            if (dentroDeAspas && linha.charAt(i) == '"') {
                i++; 
                break;
            }
            if (!dentroDeAspas && linha.charAt(i) == ',') {
                break;
            }
            campo += linha.charAt(i);
            i++;
        }
        
        if (i < linha.length() && linha.charAt(i) == ',') {
            i++;
        }

        inicio = i;
        return campo;
    }

    public static String formatarData(String dataStr) {
        String dia = "", mesStr = "", ano = "";
        String mesNum = "01"; 
        int parte = 0;

        for (int i = 0; i < dataStr.length(); i++) {
            char c = dataStr.charAt(i);
            if (c == ' ') {
                parte++;
            } else if (parte == 0) {
                mesStr += c;
            } else if (parte == 1) {
                if (c != ',') dia += c;
            } else if (parte == 2) {
                ano += c;
            }
        }
        if (ano.isEmpty()) {
            ano = mesStr;
            mesStr = "Jan"; 
            dia = "01";
        }
        if(dia.isEmpty()) dia = "01";

        String[] meses = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        for(int i = 0; i < meses.length; i++){
            if(mesStr.equalsIgnoreCase(meses[i])){
                mesNum = (i < 9) ? "0" + (i+1) : "" + (i+1);
                break;
            }
        }
        return (dia.length() == 1 ? "0" + dia : dia) + "/" + mesNum + "/" + ano;
    }
    
    public static String[] stringParaArray(String s) {
        if (s == null || s.isEmpty()) return new String[0];

        s = s.replaceAll("^\\[|]$|'", "");

        String[] temp = new String[100];
        int contador = 0;
        String palavra = "";

        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == ',') {
                if (!palavra.isEmpty()) {
                    temp[contador++] = palavra.trim();
                    palavra = "";
                }
                while (i + 1 < s.length() && s.charAt(i + 1) == ' ') {
                    i++;
                }
            } else {
                palavra += s.charAt(i);
            }
        }
        if (!palavra.isEmpty()) {
            temp[contador++] = palavra.trim();
        }

        String[] resultado = new String[contador];
        for (int i = 0; i < contador; i++) {
            resultado[i] = temp[i];
        }
        return resultado;
    }

    public static int stringParaInt(String s) {
        if (s == null || s.isEmpty()) return 0;
        int numero = 0;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c >= '0' && c <= '9') {
                numero = (numero * 10) + (c - '0');
            }
        }
        return numero;
    }

    public static float stringParaFloat(String s) {
        if (s == null || s.isEmpty()) return 0.0f;
        float numero = 0;
        int divisor = 1;
        boolean posPonto = false;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == '.') {
                posPonto = true;
            } else if (c >= '0' && c <= '9'){
                if (posPonto) {
                    divisor *= 10;
                }
                numero = (numero * 10) + (c - '0');
            }
        }
        return (divisor == 1) ? numero : numero / divisor;
    }
}