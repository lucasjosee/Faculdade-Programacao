/* 
 * Aluno: Lucas José Souza Rodrigues
 * TP 01 - Q11
*/  

import java.util.Scanner;

public class invertStringRec
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

        String linha = sc.nextLine();

        while(!isFIM(linha))
        {
            imprimirInverso(linha);
            System.out.println();

            linha = sc.nextLine();
        }
        sc.close();
    }

    static void imprimirInverso(String s)
    {
        imprimirInverso(s, (s.length() - 1));
    }

    static void imprimirInverso(String s, int n)
    {
        if(n >= 0)
        {
            MyIO.print(s.charAt(n)); //Imprimir o caractere na posição n
            imprimirInverso(s, n - 1); //Chama a função recursivamente mandando n - 1
        }
    }

    static boolean isFIM(String s)
    {
        if(s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M') return true;

        return false;
    }
}

