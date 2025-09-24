//Codigo referente ao trabalho de pesquisa
//Lucas José Souza Rodrigues
//Para testar, descomente as linhas

import java.util.Random;

public class quickSort {

    static Random gerador = new Random();

    public static void main(String[] args) {
        
        //TAMANHOS DE ARRAY PARA O TESTE
        //int[] array = new int[1000];
        int[] array = new int[10000];
        //int[] array = new int[100000];
        //int[] array = new int[1000000];

        //Preenche o array criado com numeros aleatorios
        for (int i = 0; i < array.length; i++) {
            array[i] = gerador.nextInt(1000);
        }

        //Para testar com o array ordenado ou quase ordenado descomente
        //QuickSortMedianOfThree(array, 0, array.length);

        //Descomente somente para testar o array quase ordenado
        //arrayQuaseOrd(array, array.length / 2);

        //embaralha os numeros do array para torna-lo completamente desordenado descomente
        embaralharArray(array);

        //for para testar os sorts N vezes
        for(int i = 0; i < 5; i++)
        {
            int[] arrayClone = array.clone();

            long inicio = System.currentTimeMillis();
        
            //QuickSortFirstPivot(arrayClone, 0, arrayClone.length - 1);
            //QuickSortLastPivot(arrayClone, 0, arrayClone.length - 1);
            //QuickSortRandomPivot(arrayClone, 0, arrayClone.length - 1);
            QuickSortMedianOfThree(arrayClone, 0, arrayClone.length - 1);
        
            long fim = System.currentTimeMillis();

            System.out.println("Tempo de execucao: " + (fim - inicio) + " ms" + "\n");

        }

        
        //verificar se o array está ordenado
        /*
        for(int i = 0; i < array.length - 1; i++) 
        {
            if (array[i] > array[i+1]) 
            {
                System.out.println("Erro: Array nao esta ordenado!");
                break;
            }
         }
        */
    }

    private static void QuickSortFirstPivot(int[] array, int esq, int dir) {
        if (esq < dir) 
        {
            int i = esq, j = dir;
            int pivo = array[esq];
            while (i <= j) 
            {
                while (array[i] < pivo) i++;
                while (array[j] > pivo) j--;
                if (i <= j) 
                {
                    swap(array, i, j);
                    i++;
                    j--;
                }
            }
            if (esq < j) QuickSortFirstPivot(array, esq, j);
            if (i < dir) QuickSortFirstPivot(array, i, dir);
        }
    }

    private static void QuickSortLastPivot(int[] array, int esq, int dir) 
    {
        if (esq < dir) 
        {
            swap(array, esq, dir);
            int i = esq, j = dir;
            int pivo = array[esq]; 
            while (i <= j) 
            {
                while (array[i] < pivo) i++;
                while (array[j] > pivo) j--;
                if (i <= j) 
                {
                    swap(array, i, j);
                    i++;
                    j--;
                }
            }
            if (esq < j) QuickSortLastPivot(array, esq, j);
            if (i < dir) QuickSortLastPivot(array, i, dir);
        }
    }

    private static void QuickSortRandomPivot(int[] array, int esq, int dir) {
        if (esq < dir) 
        {
            int pivotIndex = gerador.nextInt(dir - esq + 1) + esq;
            swap(array, esq, pivotIndex);
            
            int i = esq, j = dir;
            int pivo = array[esq];
            while (i <= j) 
            {
                while (array[i] < pivo) i++;
                while (array[j] > pivo) j--;
                if (i <= j)
                {
                    swap(array, i, j);
                    i++;
                    j--;
                }
            }
            if (esq < j) QuickSortRandomPivot(array, esq, j);
            if (i < dir) QuickSortRandomPivot(array, i, dir);
        }
    }

    private static void QuickSortMedianOfThree(int[] array, int esq, int dir) 
    {
        if (esq < dir) 
        {
            int meio = (esq + dir) / 2;

            int pivotIndex = mediana(array, esq, meio, dir);

            swap(array, esq, pivotIndex);

            int i = esq, j = dir;
            int pivo = array[esq]; 
            while (i <= j) {
                while (array[i] < pivo) i++;
                while (array[j] > pivo) j--;
                if (i <= j) {
                    swap(array, i, j);
                    i++;
                    j--;
                }
            }
            if (esq < j) QuickSortMedianOfThree(array, esq, j);
            if (i < dir) QuickSortMedianOfThree(array, i, dir);
        }
    }

    public static void swap(int[] array, int i, int j) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }


    public static int mediana(int[] array, int esq, int meio, int dir) {
        int vEsq = array[esq];
        int vMeio = array[meio];
        int vDir = array[dir];

        if ((vEsq > vMeio) ^ (vEsq > vDir)) 
        {
            return esq;
        } else if ((vMeio < vEsq) ^ (vMeio < vDir)) 
        {
            return meio;
        } else {
            return dir;
        }
    }

    private static void embaralharArray(int[] array)
    {
        int tamanho = array.length;

        for(int i = tamanho - 1; i > 0; i--)
        {
            int j = gerador.nextInt(i + 1);

            swap(array, i, j);
        }
    }

    private static void arrayQuaseOrd(int[] array, int numTrocas)
    {

        for (int i = 0; i < numTrocas; i++) 
        {
        
            int indice1 = gerador.nextInt(array.length);
            int indice2 = gerador.nextInt(array.length);

        
            while (indice1 == indice2) 
            {
                indice2 = gerador.nextInt(array.length);
            }

        
        swap(array, indice1, indice2); 
        }
    }
}