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
       for(int i = 1; i < tam; i++) //Considera que o primeiro ja está no lugar
       {
            int j = i;
            int menor = array[j];
            while(j != 0 && menor < array[j - 1]) //Enquanto o elemento da variavel menor for menor que o elemento anterior
            {
                array[j] = array[j - 1]; //vai puxando o elementos para a direita
                j--;
            }

            array[j] = menor; //insere o menor na posição correta
       }
    }
}
