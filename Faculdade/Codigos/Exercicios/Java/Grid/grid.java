import java.util.Scanner;

public class grid
{
    static Scanner sc = new Scanner(System.in);
    static long cont = 0;
    public static void main(String[] args)
    {
        while(sc.hasNext())
        {
            int n = sc.nextInt();

            int[] largada = new int[n];
            int[] chegada = new int[n];

            int[] carros = new int[n];
            

            preencherVetor(largada, n);
            preencherVetor(chegada, n);

            ordemCarros(largada, chegada, carros, n);

            mergeSort(carros);
            
            System.out.println(cont);

            cont = 0;

        }
        

    }

    public static void ordemCarros(int[] largada, int[] chegada, int[] carros, int n)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(largada[i] == chegada[j])
                {
                    carros[i] = j;
                }
            }
            
        }
    }

    public static void preencherVetor(int[] vetor, int n)
    {
        for(int i = 0; i < n; i++)
        {
            vetor[i] = sc.nextInt();
        }
    }
  
    public static void printVetor(int[] vetor, int n)
    {
        for(int i = 0; i < n; i++)
        {
            System.out.print(vetor[i]);
        }
        System.out.print("\n");
    }

    public static void mergeSort(int[] vetor)
    {
        int n = vetor.length;

        if(n < 2)
        {
            return;
        }

        int metade = n / 2;

        int[] arrayEsquerda = new int[metade];
        int[] arrayDireita = new int[n - metade];

        for(int i = 0; i < metade; i++)
        {
            arrayEsquerda[i] = vetor[i];
        }

        for(int i = metade; i < n; i++)
        {
            arrayDireita[i - metade] = vetor[i];
        }

        mergeSort(arrayEsquerda);
        mergeSort(arrayDireita);

        merge(arrayEsquerda, arrayDireita, vetor);
    }

    public static void merge(int[] arrayEsquerda, int[] arrayDireita, int[]vetor)
    {
        int tamEsquerda = arrayEsquerda.length, tamDireita = arrayDireita.length;

        int i = 0, j = 0, k = 0;

        while(i < tamEsquerda && j < tamDireita)
        {
            if(arrayEsquerda[i] <= arrayDireita[j])
            {
                vetor[k] = arrayEsquerda[i];
                i++;
            }
            else
            {
                vetor[k] = arrayDireita[j];
                j++;
                cont += (tamEsquerda - i);
            }
            k++;
        }

        while(i < tamEsquerda)
        {
            vetor[k] = arrayEsquerda[i];
            i++;
            k++;
        }

        while(j < tamDireita)
        {
            vetor[k] = arrayDireita[j];
            j++;
            k++;
        }
    }
}