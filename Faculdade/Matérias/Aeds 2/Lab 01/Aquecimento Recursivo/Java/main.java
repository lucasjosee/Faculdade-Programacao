import java.util.Scanner;

public class main
{
    public static void main(String args[])
    {
        Scanner sc = new Scanner(System.in);
        String palavra = sc.nextLine();
        int n;
        while(!palavra.equals("FIM"))
        {
            n = contarMaiusculas(palavra, 0);
            System.out.println(n);
            palavra = sc.nextLine();
        }
        sc.close();
    }

    public static int contarMaiusculas(String p, int n)
    {
        int cont = 0;
        if(n < p.length())
        {
            if(p.charAt(n) >= 'A' && p.charAt(n) <= 'Z')
            {
                cont = 1 + contarMaiusculas(p, n + 1);
            }
            else
            {
                cont = 0 + contarMaiusculas(p, n + 1);
            }
        }
        
        return cont;
    }
}

