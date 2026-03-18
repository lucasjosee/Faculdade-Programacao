import java.util.Scanner;

public class verificacao
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

        String entrada = sc.nextLine();

        boolean x1, x2, x3, x4;
        while(!isFIM(entrada))
        {
            int tamanho = entrada.length();

            x1 = isVogal(entrada, tamanho);
            x2 = isConsoante(entrada, tamanho);
            x3 = isInt(entrada, tamanho);
            x4 = !x1 && !x2 && !x3;
            
            System.out.println(simNao(x1) + " " + simNao(x2) + " " + simNao(x3) + " " + simNao(x4));
       
            entrada = sc.nextLine();
            
    }

    static String simNao(boolean a)
    {
        if(a)
        {
            return "SIM";
        }
        else
        {
            return "NAO";
        }
    }

    static boolean isInt(String s, int n)
    {
        boolean isLetra;
        for(int i = 0; i < n; i++)
        {
            char c = s.charAt(i);
            if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
            {
                isLetra = true;
                i = n;
            }
            else
            {
                isLetra = false;
            }
        }
        
        boolean isVirgula;
        for(int i = 0; i < n; i++)
        {
            char c = s.charAt(i);
            if(c == ',')
            {
                isVirgula = true;
                i = n;
            }
            else
            {
                isVirgula = false;
            }
        }

        return !isLetra && !isVirgula;

    }
    
    static boolean isVogal(String s, int n)
    {   
        for(int i = 0; i < n; i++)
        {
            char c = s.charAt(i);
            if(!(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'))
            {
                return false;
            }
        }
        return true;
    }

    static boolean isConsoante(String s, int n)
    {
        boolean isLetra = true;
        for(int i = 0; i < n; i++)
        {
            char c = s.charAt(i);
            if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
            {
                isLetra = true;
            }
            else
            {
                isLetra = false;
                i = n;
            }
        }

        boolean isVogal = false;
        for(int i = 0; i < n; i++)
        {
            char c = s.charAt(i);
            if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'):
            {
                isVogal = true;
                i = n;
            }
            else
            {
                isVogal = false;
            }
        }
        return isLetra && !isVogal;
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

