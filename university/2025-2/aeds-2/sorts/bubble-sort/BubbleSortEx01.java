// EX 01: Fazer o bubble Sort ordenar apenas parte do vetor

import java.util.Random;
import java.util.Scanner;

public class BubbleSortEx01
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

        System.out.println("Digite a posição desejada para comecar ordenação:");
        int m = sc.nextInt();

        System.out.println("Digite a posição desejada para encerrar a ordenação:");
        int n = sc.nextInt();

        Random gerador = new Random();
        int[] array = new int[10];

        for(int i = 0; i < array.length; i++)
        {
            array[i] = gerador.nextInt(100);
        }

        printArray(array);

        bubbleSort(array, m, n);

        printArray(array);

    
    }

    private static void printArray(int[] array)
    {
        for(int i = 0; i < array.length; i++)
        {
            System.out.print(array[i] + " ");
        }
        System.out.println();
    }

    public static void bubbleSort(int[] array, int m, int n)
    {
        for(int i = n; i > m; i--)
        {
            for(int j = m; j < i; j++)
            {
                if(array[j] > array[j + 1])
                {
                    swap(array, j, j + 1);
                }
            }
        }
    }

    public static void swap(int[] array, int i, int j)
    {
        int temp = array[j];
        array[j] = array[i];
        array[i] = temp;
    }

}