// EX 02: Contagem de Trocas

import java.util.Random;

public class BubbleSortEx02
{
    public static void main(String[] args)
    {
        Random gerador = new Random();
        int[] array = new int[10];

        for(int i = 0; i < array.length; i++)
        {
            array[i] = gerador.nextInt(100);
        }

        printArray(array);

        int cont = bubbleSort(array);

        printArray(array);
        
        System.out.println();

        System.out.println("Numero de trocas: " + cont);
    
    }

    private static void printArray(int[] array)
    {
        for(int i = 0; i < array.length; i++)
        {
            System.out.print(array[i] + " ");
        }
        System.out.println();
    }

    public static int bubbleSort(int[] array)
    {
        int cont = 0;
        for(int i = array.length - 1; i > 0; i--)
        {
            int mudancas = 0;
            for(int j = 0; j < i; j++)
            {
                if(array[j] > array[j + 1])
                {
                    swap(array, j, j + 1);
                    cont++;
                    mudancas++;
                }
            }
            if(mudancas <= 1)
            {
                break;
            }
        }
        return cont;

    }



    public static void swap(int[] array, int i, int j)
    {
        int temp = array[j];
        array[j] = array[i];
        array[i] = temp;
    }

}