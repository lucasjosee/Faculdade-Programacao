import java.util.Scanner;

public class main
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        int num = sc.nextInt();
        sc.nextLine();
        while(num > 0)
        {
            String entrada = sc.nextLine();
            
            String[] permutacoes = gerarPermutacoes(entrada);
            if(permutacoes != null)
            {
                int tam = permutacoes.length;

                ordenar(permutacoes, 0, tam - 1);
            
                print(permutacoes);

                num--;
            }
        }
        
        sc.close();
    }

    public static void print(String[] permutacoes)
    {
        int tam = permutacoes.length;
        for(int i = 0; i < tam; i++)
            System.out.println(permutacoes[i]);

        System.out.println();
    }

    public static void ordenar(String[] permutacoes, int esq, int dir)
    {   
        int i = esq, j = dir;
        String pivo = permutacoes[(dir + esq) / 2];
        while(i <= j)
        {
            while(permutacoes[i].compareToIgnoreCase(pivo) < 0) i++;
            while(permutacoes[j].compareToIgnoreCase(pivo) > 0) j--;
            if(i <= j)
            {
                String temp = permutacoes[i];
                permutacoes[i] = permutacoes[j];
                permutacoes[j] = temp;
                i++;
                j--;
            }
        }
        if(esq < j) ordenar(permutacoes, esq, j);
        if(i < dir) ordenar(permutacoes, i, dir);
    }   

    public static String[] gerarPermutacoes(String palavra)
    {
        int tam = palavra.length();
        
        if(tam > 10)
            return null;

        char[] entrada = new char[tam];
        
        for(int i = 0; i < tam; i++)
        {
            entrada[i] = palavra.charAt(i);
        }
        
        String[] permutacoes;

        if(tam != 1)
            permutacoes = new String[(tam * tam) - tam];        
        else
            permutacoes = new String[1];
        
        int contPerm = 0;
        
        if(tam == 1)
        {
            String result = new String(entrada);
            permutacoes[0] = result;
        }
        else
        {
            while(tam > 0)
            {
                for(int i  = 0; i < entrada.length - 1; i++)
                {
                    char temp = entrada[i];
                    entrada[i] = entrada[i + 1];
                    entrada[i + 1] = temp;

                    String result = new String(entrada);
                    
                    if(contPerm != 0 && permutacoes[contPerm - 1].compareToIgnoreCase(result) == 0)
                    {
                        String[] result2 = new String[1];
                        result2[0] = result;
                        return result2;
                    }
                    permutacoes[contPerm++] = result;
               }
               tam--;
            }
        }
        return permutacoes;
    }     
}
