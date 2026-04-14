import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.File;

public class Montador
{
    public static void main(String[] args) throws Exception
    {
        String arquivoEntrada = "testeula.ula";
        String arquivoSaida = "testeula.hex";

        BufferedReader br = new BufferedReader(new FileReader(arquivoEntrada));
        FileWriter fw = new FileWriter(arquivoSaida);

        String linha;
        int numLinha = 0;
        
        // Registradores
        int registradorX = 0;
        int registradorY = 0;

        System.out.println("Iniciando a montagem...");

        while ((linha = br.readLine()) != null)
        {
            numLinha++;
            linha = limparFinalLinha(linha);

            // Verifica se a linha esta vazia
            if (linha.length() == 0)
            {
                System.out.println("Erro na linha " + numLinha + ": vazia.");
                fw.close();
                new File(arquivoSaida).delete();
                return;
            }

            // Verifica o fim do arquivo
            if (comparaString(linha, "fim."))
            {
                System.out.println("Sucesso!");
                break;
            }

            // Ignora o inicio e processa o resto
            if (!comparaString(linha, "inicio:"))
            {
                int tam = linha.length();
                
                // Verifica o ponto e virgula
                if (linha.charAt(tam - 1) != ';')
                {
                    System.out.println("Erro na linha " + numLinha + ": falta ;");
                    fw.close();
                    new File(arquivoSaida).delete();
                    return;
                }

                // Ajusta o tamanho pra ignorar o ;
                tam = tam - 1;

                // Verifica X, Y ou W olhando os dois primeiros caracteres
                if (linha.charAt(0) == 'X' && linha.charAt(1) == '=')
                {
                    registradorX = extrairInteiro(linha, 2, tam);
                }
                else if (linha.charAt(0) == 'Y' && linha.charAt(1) == '=')
                {
                    registradorY = extrairInteiro(linha, 2, tam);
                }
                else if (linha.charAt(0) == 'W' && linha.charAt(1) == '=')
                {
                    char instHex = decodificarMnemonico(linha, 2, tam);

                    if (instHex == '-')
                    {
                        System.out.println("Erro na linha " + numLinha + ": inst invalida.");
                        fw.close();
                        new File(arquivoSaida).delete();
                        return;
                    }

                    // Grava os dados formatados
                    fw.write(String.format("%X%X%c\n", registradorX, registradorY, instHex));
                }
                else
                {
                    System.out.println("Erro na linha " + numLinha + ": comando invalido.");
                    fw.close();
                    new File(arquivoSaida).delete();
                    return;
                }
            }
        }

        br.close();
        fw.close();
    }

    // Funcao manual para converter string em inteiro
    public static int extrairInteiro(String str, int inicio, int fim)
    {
        int valor = 0;
        for (int i = inicio; i < fim; i++)
        {
            valor = (valor * 10) + (str.charAt(i) - '0');
        }
        return valor;
    }

    // Funcao manual para comparar strings exatamente
    public static boolean comparaString(String str1, String str2)
    {
        if (str1.length() != str2.length())
        {
            return false;
        }

        for (int i = 0; i < str1.length(); i++)
        {
            if (str1.charAt(i) != str2.charAt(i))
            {
                return false;
            }
        }
        return true;
    }

    // Decodifica a instrucao mapeando pro Hexa
    public static char decodificarMnemonico(String str, int inicio, int fim)
    {
        // Isola a palavra do mnemonico
        String mnemonico = "";
        for (int i = inicio; i < fim; i++)
        {
            mnemonico += str.charAt(i);
        }

        if (comparaString(mnemonico, "CopiaA")) return '0';
        if (comparaString(mnemonico, "CopiaB")) return '1';
        if (comparaString(mnemonico, "AxB")) return '2';
        if (comparaString(mnemonico, "nAxnB")) return '3';
        if (comparaString(mnemonico, "AeBn")) return '4';
        if (comparaString(mnemonico, "nB")) return '5';
        if (comparaString(mnemonico, "nAonB")) return '6';
        if (comparaString(mnemonico, "nA")) return '7';
        if (comparaString(mnemonico, "AonB")) return '8';
        if (comparaString(mnemonico, "UmL")) return '9';
        if (comparaString(mnemonico, "ZeroL")) return 'A';
        if (comparaString(mnemonico, "AeB")) return 'B';
        if (comparaString(mnemonico, "nAeB")) return 'C';
        if (comparaString(mnemonico, "AenB")) return 'D';
        if (comparaString(mnemonico, "AoB")) return 'E';
        if (comparaString(mnemonico, "nAenB")) return 'F';
        
        return '-'; 
    }

    // Tira os espacos e quebras de linha do final
    public static String limparFinalLinha(String linha)
    {
        int tam = linha.length();
        while (tam > 0 && (linha.charAt(tam - 1) == ' ' || linha.charAt(tam - 1) == '\n' || linha.charAt(tam - 1) == '\r' || linha.charAt(tam - 1) == '\t'))
        {
            tam--;
        }
        
        String limpa = "";
        for (int i = 0; i < tam; i++)
        {
            limpa += linha.charAt(i);
        }
        return limpa;
    }
}
