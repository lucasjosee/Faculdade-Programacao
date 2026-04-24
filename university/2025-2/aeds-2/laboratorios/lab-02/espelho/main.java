import java.util.Scanner;

public class main
{
    public static void main(String args[])
    {
        Scanner sc = new Scanner(System.in);

        int a, b;

        a = sc.nextInt();
        b = sc.nextInt();

        int[] vetor = new int[(b + 1) - a];

        for(int i = 0; i < vetor.length; i++)
        {
            vetor[i] = a + i;
        }

        printarNormal(vetor);
        printarContrario(vetor);

        sc.close();
    }

    public static void printarNormal(int[] vetor)
    {
        for(int i = 0; i < vetor.length; i++)
        {
            System.out.print(vetor[i]);
        }
    }

    public static void printarContrario(int[] vetor)
    {
        for(int i = vetor.length - 1; i >= 0; i--)
        {
            while(vetor[i] != 0)
            {
                System.out.print(vetor[i] % 10);
                vetor[i] = vetor[i] / 10;
            }
        }
    }
}