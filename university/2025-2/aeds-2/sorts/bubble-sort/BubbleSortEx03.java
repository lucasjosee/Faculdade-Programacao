//Ex03: Ordenar strings pelo tamanho

import java.util.Scanner;
import java.util.String;

public class BubbleSortEx03
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

        String[] array = new String[4];

        for(int i = 0; i < array.length; i++)
        {
            System.out.println("Digite um palavra:");
            array[i] = sc.nextLine();
        }

        printArray(array);

        bubbleSort(array);

        printArray(array);

    
    }

    private static void printArray(String[] array)
    {
        for(int i = 0; i < array.length; i++)
        {
            System.out.print(array[i] + " ");
        }
        System.out.println();
    }

    public static void bubbleSort(String[] array)
    {
        for(int i = array.length - 1; i > 0; i--)
        {
            int mudancas = 0;
            for(int j = 0; j < i; j++)
            {
                if(array[j].length() > array[j + 1].length())
                {
                    swap(array, j, j + 1);
                    mudancas++;
                }

            }
            if(mudancas == 0)
            {
                break;
            }
        }
    }

    public static void swap(String[] array, int i, int j)
    {
        String temp = array[j];
        array[j] = array[i];
        array[i] = temp;
    }

}