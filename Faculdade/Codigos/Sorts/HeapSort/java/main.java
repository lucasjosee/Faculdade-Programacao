public class main
{
    public static void main(String[] args)
    {

    }

    public static void heapify(int[] array, int n, int i)
    {
        int maior = i;
        int esquerda = i * 2 + 1;
        int direita = i * 2 + 2;

        if(esquerda < n && array[esquerda] > array[maior])
        {
            maior = esquerda;
        }

        if(direita < n && array[direita] > array[maior])
        {
            maior = direita;
        }

        if(maior != i)
        {
            int temp = array[maior];
            array[maior] = array[i];
            array[i] = temp;

            heapify(array, n, maior);
        }
    }

    public static void sort(int[] array)
    {
        int n = array.length;
        
        for(int i = n / 2 - 1; i >= 0; i--)
        {
            heapify(array, n, i);
        }

        for(int i = n - 1 ; i > 0; i--)
        {
            int temp = array[i];
            array[i] = array[0];
            array[0] = temp;

            heapify(array, i, 0);
        }
    }
}