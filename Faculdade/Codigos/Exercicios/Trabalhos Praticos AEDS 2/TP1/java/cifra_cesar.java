import java.util.Scanner;

public class cifra_cesar
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

        String entrada = sc.nextLine(); 

        while(!isFIM(entrada)) //Caso a palavra de entrada seja FIM, programa para
        {
            int tamanho = entrada.length();

            char[] resultado = criptografia(entrada, tamanho);
            
            for(int i = 0; i < tamanho; i++)
            {
                System.out.print(resultado[i]);
            }
            System.out.println();

            entrada = sc.nextLine();
        }
    }

    static char[] criptografia(String palavra, int n)
    {
        char[] result = new char[n]; //String que ira receber a criptografia

        char c;
        for(int i = 0; i < n; i++)
        {
            c = (char) (palavra.charAt(i) + 3); //Somando 3 no codigo ASCII do caractere
            result[i] = c;
        }
        return result;

    }

    static boolean isFIM(String e)
    {
        if(e.charAt(0) == 'F' && e.charAt(1) == 'I' && e.charAt(2) == 'M')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

