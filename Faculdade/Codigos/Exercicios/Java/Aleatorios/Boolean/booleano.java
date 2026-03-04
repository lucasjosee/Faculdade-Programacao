//Aluno: Lucas José Souza Rodrigues
//Ex: Expresso Booleana - TP 2
 
import java.util.Scanner;

public class booleano 
{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int qtd = sc.nextInt();
        String expr;
        int[] bits = new int[3]; //guarda os valores binarios 

        while (qtd != 0)
        {
            for (int i = 0; i < qtd; i++) 
            {
                bits[i] = sc.nextInt();
            }

            expr = sc.nextLine(); //le a expressão
            expr = Substituidor.substituir(bits, expr); //chama o substituidor para trocar as variaveis
            expr = Resolutor.processar(expr); //resolve a expressão

            System.out.println(expr); //Imprime o resultado

            qtd = sc.nextInt();
        }
        sc.close();
    }
}

class Substituidor //Percorre a expessao e troca A B e C
{
    public static String substituir(int[] bits, String expr) 
    {
        String nova = "";

        for (int i = 0; i < expr.length(); i++) 
        {
            if (expr.charAt(i) != ' ') 
            {
                if (expr.charAt(i) == 'A')
                 {
                    nova += bits[0];
                } else if (expr.charAt(i) == 'B') 
                {
                    nova += bits[1];
                } else if (expr.charAt(i) == 'C') 
                {
                    nova += bits[2];
                } else 
                {
                    nova += expr.charAt(i);
                }
            }
        }
        return nova;
    }
}

class Resolutor // Em que ordem as operações serao resolvidas
{
    public static String processar(String expr) 
    {
        int qtd = 0;

        for (int i = 0; i < expr.length(); i++)
         {
            if (expr.charAt(i) == '(') 
            {
                qtd++;
            }
        }

        char[] ordem = new char[qtd]; //guarda as ordens de operção

        for (int i = 0; i < expr.length() - 2; i++)
         {
            if (expr.charAt(i + 2) == 't') 
            {
                ordem[--qtd] = 'n';
            } else if (expr.charAt(i + 2) == 'd') 
            {
                ordem[--qtd] = 'a';
            } else if (expr.charAt(i + 1) == 'r') 
            {
                ordem[--qtd] = 'o';
            }
        }

        for (int i = 0; i < ordem.length; i++) //aplica as operações na ordem certa
        {
            if (ordem[i] == 'n') 
            {
                expr = Operacoes.aplicarNot(expr);
            } else if (ordem[i] == 'a') 
            {
                expr = Operacoes.aplicarAnd(expr);
            } else 
            {
                expr = Operacoes.aplicarOr(expr);
            }
        }
        return expr;
    }
}

class Operacoes //métodos que reescrevem a string, substituindo uma operação completa pelo resultado
{
    public static String aplicarNot(String expr) 
    {
        String res = "";
        for (int i = 0; i < expr.length(); i++) 
        {
            if (expr.charAt(i) == 'n' && (expr.charAt(i + 4) == '1' || expr.charAt(i + 4) == '0')) 
            {
                res += expr.charAt(i + 4) == '1' ? 0 : 1;
                i += 5;
            } else 
            {
                res += expr.charAt(i);
            }
        }
        return res;
    }

    public static String aplicarAnd(String expr)
     {
        String res = "";
        for (int i = 0; i < expr.length(); i++)
         {
            if (expr.charAt(i) == 'a' && (expr.charAt(i + 4) == '1' || expr.charAt(i + 4) == '0') && (expr.charAt(i + 6) == '1' || expr.charAt(i + 6) == '0')) 
            {
                if (expr.charAt(i + 7) == ')') 
                {
                    res += (expr.charAt(i + 4) == '1' && expr.charAt(i + 6) == '1') ? 1 : 0;
                    i += 7;
                } else if (expr.charAt(i + 9) == ')') 
                {
                    res += (expr.charAt(i + 4) == '1' && expr.charAt(i + 6) == '1' && expr.charAt(i + 8) == '1') ? 1 : 0;
                    i += 9;
                } else if (expr.charAt(i + 11) == ')')
                 {
                    res += (expr.charAt(i + 4) == '1' && expr.charAt(i + 6) == '1' && expr.charAt(i + 8) == '1' && expr.charAt(i + 10) == '1') ? 1 : 0;
                    i += 11;
                } else {
                    res += expr.charAt(i);
                }
            } else 
            {
                res += expr.charAt(i);
            }
        }
        return res;
    }

    public static String aplicarOr(String expr) 
    {
        String res = "";
        for (int i = 0; i < expr.length(); i++) 
        {
            if (expr.charAt(i) == 'o' && expr.charAt(i + 1) == 'r' && (expr.charAt(i + 3) == '1' || expr.charAt(i + 3) == '0') && (expr.charAt(i + 5) == '1' || expr.charAt(i + 5) == '0')) 
            {
                if (expr.charAt(i + 6) == ')') 
                {
                    res += (expr.charAt(i + 3) == '1' || expr.charAt(i + 5) == '1') ? 1 : 0;
                    i += 6;
                } else if (expr.charAt(i + 8) == ')') 
                {
                    res += (expr.charAt(i + 3) == '1' || expr.charAt(i + 5) == '1' || expr.charAt(i + 7) == '1') ? 1 : 0;
                    i += 8;
                } else if (expr.charAt(i + 10) == ')') 
                {
                    res += (expr.charAt(i + 3) == '1' || expr.charAt(i + 5) == '1' || expr.charAt(i + 7) == '1' || expr.charAt(i + 9) == '1') ? 1 : 0;
                    i += 10;
                }
            } else {
                res += expr.charAt(i);
            }
        }
        return res;
    }
}


