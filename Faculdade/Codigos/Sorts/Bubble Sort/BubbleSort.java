import java.util.Random;

public class BubbleSort
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

        bubbleSort(array);

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

    public static void bubbleSort(int[] array)
    {
        for(int i = array.length - 1; i > 0; i--)
        {
            int mudancas = 0;
            for(int j = 0; j < i; j++)
            {
                if(array[j] > array[j + 1])
                {
                    swap(array, j, j + 1);
                    mudancas++;
                }
            }
            if(mudancas <= 1)
            {
                break;
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