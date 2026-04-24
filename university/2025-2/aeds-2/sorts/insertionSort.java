import java.util.Scanner;

public class insertionSort
{
    public static void main(String[] args)
    {
        int array[] = new int[10];

        Scanner sc = new Scanner(System.in);

        for(int i = 0; i < 10; i++)
        {
            array[i] = sc.nextInt();
        }

        sort(array);

        for(int i = 0; i < 10; i++)
        {
            System.out.println(array[i]);
        }
    }

    public static void sort(int[] array)
    {
       int tam = array.length;
       for(int i = 1; i < tam; i++)
       {
            int j = i;
            int menor = array[j];
            while(j != 0 && menor < array[j - 1])
            {
                array[j] = array[j - 1];
                j--;
            }

            array[j] = menor;
       }
    }
}
