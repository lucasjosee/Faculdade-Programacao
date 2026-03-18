import java.util.Scanner;

public class organizador_vagoes
{
    public static void main(String[] args)
    {
       Scanner sc = new Scanner(System.in);

       int n = sc.nextInt();
       for(int i = 0; i < n; i++)
       {
            int tamanho = sc.nextInt();
            int array[] = new int[tamanho];

            for(int j = 0; j < tamanho; j++)
            {
                array[j] = sc.nextInt();
            }

            int swaps = boubbleSort(array, tamanho);

            System.out.println("Optimal train swapping takes " + swaps + " swaps.");
       }
       sc.close();
    }

    

    static int boubbleSort(int array[], int n)
    {
        int cont = 0;
        for(int i = 0; i < n - 1; i++)
        {
            for(int j = 0; j < n - 1 - i; j++)
            {
                if(array[j] > array[j + 1])
                {
                    int temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                    cont++;
                }
            }
        }
        return cont;
    }
        
}   
