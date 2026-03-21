import java.util.Scanner;

public class tracando_movimentos
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

        while(sc.hasNextInt())
        {
            int n = sc.nextInt();
            sc.nextLine();
            char[] entrada = lerLinha(sc, n);
            
            char[] saidaEsperada = lerLinha(sc, n);

            popPush(entrada, saidaEsperada, n);
        }
    }

    public static void popPush(char[] entrada, char[] saidaEsperada, int n)
    {
        char[] pilha = new char[n];
        int topo = 0;
        int j = 0;
        
        for(int i = 0; i < n; i++)
        {
            pilha[topo] = entrada[i];
            topo++;
            System.out.print("I");

            while(topo > 0 && pilha[topo - 1] == saidaEsperada[j])
            {
                topo--;
                j++;
                System.out.print("R");
            }
        }
        if(topo != 0) System.out.println(" Impossible");
        else System.out.println();
    }

    public static char[] lerLinha(Scanner sc, int n)
    {   
        String s = sc.nextLine();
        char[] temp = new char[s.length()];

        int i = 0, j = 0;
        while(i < s.length())
        {
            if(s.charAt(i) != ' ')
            {
                temp[j] = s.charAt(i);
                i++;
                j++;
            }
            else
            {
                i++;
            }
        }
        char[] saida = new char[j];
        for(int k = 0; k < j; k++)
        {
            saida[k] = temp[k];
        }
        return saida;
    }
}
