/* 
 * Aluno: Lucas José Souza Rodrigues
 * TP 01 - Q12
*/

import java.util.Scanner;

public class somaDigitosRec
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

        String linha = sc.nextLine();

        while(!isFIM(linha))
        {
            System.out.println(somarRec(linha));

            linha = sc.nextLine();
        }
        sc.close();
    }

    static int somarRec(String s)
    {
        return somarRec(s, 0);
    }

    static int somarRec(String s, int n)
    {
        int soma = 0;
        if(n < s.length()) soma += (s.charAt(n) - 48) + somarRec(s, n + 1); // a cada chamada recursiva ele acrescenta o numero na soma, 
                                                                            // o -48 foi usado para fazer a tranformação de char para int de acordo com a tabela ascii

        return soma;
        
    }

    static boolean isFIM(String e)
    {
        if(e.charAt(0) == 'F' && e.charAt(1) == 'I' && e.charAt(2) == 'M')
        {
            return true;
        }
        return false;
    }
}
