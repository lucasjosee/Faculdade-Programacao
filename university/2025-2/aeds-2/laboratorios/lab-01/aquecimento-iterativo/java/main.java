import java.util.Scanner;

public class main
{
    public static void main(String []args)
    {
        Scanner sc = new Scanner(System.in);
        String palavra = sc.nextLine();
        while(!palavra.equals("FIM"))
        {
            int n = contarMaiusculos(palavra);
            System.out.println(n);
            palavra = sc.nextLine();
        }
        
    }

    public static int contarMaiusculos(String palavra)
    {
        int n = 0;
        for(int i = 0; i < palavra.length(); i++)
        {
            if(palavra.charAt(i) >= 'A' && palavra.charAt(i) <= 'Z')
            {
                n++;
            }
        }
        return n;
    }
}