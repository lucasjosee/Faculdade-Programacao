public class heapSort
{
    public static void main(String[] args)
    {
        int[] array = {20, 2, 32, 43, 123, 43, 1, 65, 9, 12};
        
        sort(array, 10);

        for(int i = 0; i < 10; i++)
        {
            System.out.println(array[i]);
        }
    }

    public static void sort(int[] array, int n)
    {
        int[] temp = new int[n + 1];
        for(int i = 0; i < n; i++)
        {
            temp[i + 1] = array[i];
        }

        for(int tamHeap = 2; tamHeap <= n; tamHeap++)
        {
            construir(temp, tamHeap);
        }

        int tamHeap = n; 
        while(tamHeap > 1)
        {
            swap(temp, 1, tamHeap--);
            reconstruir(temp, tamHeap);
        }
        
        for(int i = 0; i < n; i++)
        {
            array[i] = temp[i + 1];
        }
    }

    public static void construir(int[] array, int tamHeap)
    {
        for(int i = tamHeap; i > 1 && array[i] > array[i / 2]; i = i / 2)
        {
            swap(array, i, i / 2);
        }
    }

    public static void reconstruir(int[] array, int tamHeap)
    {
        int i = 1;
        while(i <= (tamHeap/2))
        {
            int filho = getMaiorFilho(array, i, tamHeap);
            if(array[i] < array[filho])
            {
                swap(array, i, filho);
                i = filho;
            }
            else
            {
                i = tamHeap;
            }
        }
    }

    public static int getMaiorFilho(int[] array, int i, int tamHeap)
    {
        int filho;
        if(i * 2 == tamHeap || array[i * 2] > array[i * 2 + 1])
        {
            filho = i * 2;
        }
        else
        {
            filho = i * 2 + 1;
        }
        return filho;
    }

    public static void swap(int[] array, int i, int j)
    {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}
