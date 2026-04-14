import java.util.Scanner;

public class combinador {
    public static void main(String[] args)
    {
        String palavra1, palavra2;
    
        Scanner sc = new Scanner(System.in);

        palavra1 = sc.nextLine();
        palavra2 = sc.nextLine();
        
        int tamanho = palavra1.length() + palavra2.length();
        char[] palavrafinal = new char[tamanho];
        
        int menorString;
        if(palavra1.length() > palavra2.length())
        {
            menorString = palavra2.length();
        }
        else
        {
            menorString = palavra1.length();
        }
        int indice = 0;

        for(int i = 0; i < menorString; i++)
        {
            palavrafinal[indice++] = palavra1.charAt(i);
            palavrafinal[indice++] = palavra2.charAt(i);
        }

        if(palavra1.length() > menorString)
        {
            for(int i = menorString; i < palavra1.length(); i++)
            {
                palavrafinal[indice] = palavra1.charAt(i);
            }
        }
        else
        {
            for(int i = menorString; i < palavra2.length(); i++)
            {
                palavrafinal[indice] = palavra2.charAt(i);
            }
        }
        String novaString = new String(palavrafinal);

        System.out.println(novaString);
       
        sc.close();
    }

}
