/* 
 * Aluno: Lucas José Souza Rodrigues
 * TP 01 - Q3
*/ 

import java.util.Scanner;

public class Is 
{
    public static void main(String[] args) 
    {
        Scanner sc = new Scanner(System.in);

        String entrada = sc.nextLine();

        while (!isFim(entrada)) 
        {
            boolean x1 = isVogal(entrada);
            boolean x2 = isConsoante(entrada);
            boolean x3 = isInteiro(entrada);
            boolean x4 = isReal(entrada);

            System.out.println(simNao(x1) + " " + simNao(x2) + " " + simNao(x3) + " " + simNao(x4));

            entrada = sc.nextLine();
        }

        sc.close();
    }

    public static boolean isFim(String s) 
    {
        boolean resultado = false;

        if (s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M') 
        {
            resultado = true;
        }

        return resultado;
    }

    public static String simNao(boolean b) //Se for true retorna SIM, se for false retorna NAO. O retorno será impresso na main
    {
        String str = "NAO";

        if (b) 
        {
            str = "SIM";
        }

        return str;
    }

    public static boolean isVogal(String s) 
    {
        boolean resultado = true;

        for (int i = 0; i < s.length(); i++) 
        {
            char c = s.charAt(i);

            if (!(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                  c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')) 
            {
                resultado = false;
                i = s.length();
            }
        }

        return resultado;
    }

    public static boolean isConsoante(String s) 
    {
        boolean resultado = true;

        for (int i = 0; i < s.length(); i++) 
        {
            char c = s.charAt(i);
            boolean ehLetra = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); //Variavel que vai verificar se o caractere é uma letra
            boolean ehVogal = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                               c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'); //Variavel que vai verificar se é vogal

            if (!ehLetra || ehVogal) //Se for for vogal ou se não for letra, não é consoante
            {
                resultado = false;
                i = s.length();
            }
        }

        return resultado;
    }

    public static boolean isInteiro(String s) 
    {
        boolean resultado = true;

        for (int i = 0; i < s.length(); i++) 
        {
            char c = s.charAt(i);

            if (c < '0' || c > '9')
            {
                resultado = false;
                i = s.length();
            }
        }

        return resultado;
    }

    public static boolean isReal(String s) 
    {
        boolean resultado = true;
        int separadores = 0;

        for (int i = 0; i < s.length(); i++) 
        {
            char c = s.charAt(i);

            if (c >= '0' && c <= '9') 
            {
                // Caractere valido
            } 
            else if (c == ',' || c == '.')//Verifica se tem ',' ou '.', se tiver significa que é numero real 
            {
                separadores = separadores + 1;
            } 
            else 
            {
                resultado = false;
                i = s.length();
            }
        }

        if (separadores > 1) //Se tiver mais de um ponto ou virgula, não é numero real
        {
            resultado = false;
        }

        return resultado;
    }
}
