import java.util.Scanner;
import java.util.Random;

public class alteracao_aleatoria
{
    public static void  main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        Random gerador = new Random();
        gerador.setSeed(4);

        String entrada = sc.nextLine();

        while(!isFIM(entrada))
        {
            //gerando as duas letras aleatorias
            char a = (char) ('a' + (Math.abs(gerador.nextInt()) % 26));
            char b = (char) ('a' + (Math.abs(gerador.nextInt()) % 26));
            
            System.out.println(trocarAB(entrada, a, b));

            entrada = sc.nextLine();
        }
    }

    static String trocarAB(String e, char a, char b)
    {
        int tamanho = e.length(); 
        
        char[] result = new char[tamanho];

        for(int i = 0; i < tamanho; i++) //Preenchendo a nova string com as alterações
        {
            if(e.charAt(i) == a)
            {
                result[i] = b;
            }
            else
            {
                result[i] = e.charAt(i);
            }
        }
        return new String(result); //Transformando o vetor de char em string 
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

