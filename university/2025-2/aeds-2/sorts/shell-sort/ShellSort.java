public class ShellSort {

    public static void sort(int[] array) 
    {
        int n = array.length;
        for (int h = n / 2; h > 0; h /= 2) 
        {
            for (int i = h; i < n; i++) 
            {
                int temp = array[i];
                int j = i;
                while (j >= h && array[j - h] > temp) 
                {
                    array[j] = array[j - h];
                    j = j - h;
                }
                array[j] = temp;
            }
        }
    }

    public static void printArray(int[] arr) 
    {
        System.out.print("[");
        for (int i = 0; i < arr.length; i++) 
        {
            System.out.print(arr[i]);
            if (i < arr.length - 1) 
            {
                System.out.print(", ");
            }
        }
        System.out.println("]");
    }

    public static void main(String[] args) 
    {
        int[] data = { 9, 8, 3, 7, 5, 6, 4, 1 };

        System.out.print("Array antes da ordenação: ");
        printArray(data);

        ShellSort.sort(data);

        System.out.print("Array depois da ordenação: ");
        printArray(data);
    }
}