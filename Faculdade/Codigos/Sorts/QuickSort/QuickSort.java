import java.util.Random;

public class QuickSort
{
    public static void main(String[] args)
    {
        Random rand = new Random();

        int[] numeros = new int[10000];

        for(int i = 0; i < numeros.length; i++)
        {
            numeros[i] = rand.nextInt(100);
        }

        System.out.println("Antes:");
        //printArray(numeros);

        sort(numeros, 0, numeros.length - 1);

        System.out.println("Depois:");
        //printArray(numeros);
    }

    private static void printArray(int[] array)
    {
        for(int i = 0; i < array.length; i++)
        {
            System.out.println(array[i]);
        }
    }

    public static void sort(int[] array, int esquerda, int direita)
    {
        if(esquerda >= direita)
        {
            return;
        }

        int pivo = array[(esquerda + direita) / 2];
        int i = esquerda, j = direita;

        while(i <= j) 
        {
            while(array[i] < pivo) 
            {
                i++;
            }

            while(array[j] > pivo)
            {
                j--;
            }

            if(i <= j)
            {
                swap(array, i, j);
                i++;
                j--;
            }
        }

        if (esquerda < j)
        {
            sort(array, esquerda, j);
        }
        if (i < direita)
        {
            sort(array, i, direita);
        }
    }

    public static void swap(int[] array, int i, int j)
    {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}
