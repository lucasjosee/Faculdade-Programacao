public class mergeSort
{
    public static void main(String[] args)
    {
        int[] array = {23, 32, 1, 54, 2, 3, 74, 10, 23, 3};

        sort(array, 0, array.length - 1);

        for(int i = 0; i < 10; i++)
            System.out.println(array[i]);
    }
    
    public static void sort(int[] array, int esq, int dir)
    {
        if(esq < dir)
        {
            int meio = (esq + dir) / 2;
            sort(array, esq, meio);
            sort(array, meio + 1, dir);
            intercalar(array, esq, meio, dir);
        }
    }

    public static void intercalar(int[] array, int esq, int meio, int dir)
    {
        int n1, n2, i, j, k;

        n1 = meio - esq + 1;
        n2 = dir - meio;

        int[] a1 = new int[n1];
        int[] a2 = new int[n2];

        for(i = 0; i < n1; i++)
            a1[i] = array[esq + i];

        for(j = 0; j < n2; j++)
            a2[j] = array[meio + j + 1];

        i = 0; j = 0; k = esq;
        while(i < n1 && j < n2)
            array[k++] = (a1[i] <= a2[j]) ? a1[i++] : a2[j++];
          
        while(i < n1)
            array[k++] = a1[i++];
        while(j < n2) 
            array[k++] = a2[j++];

    }

}
