//Codigo referente ao trabalho de pesquisa
//Lucas José Souza Rodrigues

import java.util.Scanner;
import java.util.Random;
import java.util.Date;

public class quickSort
{
    static Random gerador = new Random();
    public static void main(String[] args)
    {
        
        int[] array = new int[10000];

        for(int i = 0; i < array.length; i++)
        {
            array[i] = gerador.nextInt(1000);
        }

        long inicio = System.currentTimeMillis();

        //chamadas de função
        //QuickSortFirstPivot(array, 0, array.length - 1);
        //QuickSortLastPivot(array, 0, array.length - 1);
        //QuickSortRandomPivot(array, 0, array.length - 1);
        //QuickSortMedianOfThree(array, 0, array.length - 1);

        long fim = System.currentTimeMillis();

        System.out.println("Tempo de execucao: " + (fim - inicio));

    }

    private static void QuickSortFirstPivot(int[] array, int esq, int dir) 
    {
        int i = esq, j = dir;
        int pivo = array[esq];
        while (i <= j) 
        {
            while (array[i] < pivo)
            {
                i++;
            } 
            while (array[j] > pivo)
            {
                j--;
            } 
            if (i <= j) 
            {
                swap(array, i, j);
                i++;
                j--;
            }
        }
        if (esq < j)  QuickSortFirstPivot(array, esq, j);
        if (i < dir)  QuickSortFirstPivot(array, i, dir);
    }

    private static void QuickSortLastPivot(int[] array, int esq, int dir) 
    {
        int i = esq, j = dir;
        int pivo = array[dir];
        while (i <= j) 
        {
            while (array[i] < pivo)
            {
                i++;
            } 
            while (array[j] > pivo)
            {
                j--;
            } 
            if (i <= j) 
            {
                swap(array, i, j);
                i++;
                j--;
            }
        }
        if (esq < j)  QuickSortLastPivot(array, esq, j);
        if (i < dir)  QuickSortLastPivot(array, i, dir);
    }

    private static void QuickSortRandomPivot(int[] array, int esq, int dir) 
    {
        int x = gerador.nextInt(dir - esq + 1) + esq;
        int i = esq, j = dir;
        int pivo = array[x];
        while (i <= j) 
        {
            while (array[i] < pivo)
            {
                i++;
            } 
            while (array[j] > pivo)
            {
                j--;
            } 
            if (i <= j) 
            {
                swap(array, i, j);
                i++;
                j--;
            }
        }
        if (esq < j)  QuickSortRandomPivot(array, esq, j);
        if (i < dir)  QuickSortRandomPivot(array, i, dir);
    }

    private static void QuickSortMedianOfThree(int[] array, int esq, int dir) 
    {
        int a = mediana(esq, (esq + dir) / 2, dir);
        int i = esq, j = dir;
        int pivo = array[a];
        while (i <= j) 
        {
            while (array[i] < pivo)
            {
                i++;
            } 
            while (array[j] > pivo)
            {
                j--;
            } 
            if (i <= j) 
            {
                swap(array, i, j);
                i++;
                j--;
            }
        }
        if (esq < j)  QuickSortMedianOfThree(array, esq, j);
        if (i < dir)  QuickSortMedianOfThree(array, i, dir);
    }

    public static void swap(int[] array, int i, int j) 
    {
		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}

    public static int mediana(int esq, int meio, int dir)
    {
        int result = (esq + meio + dir) / 3;
        return result;
    }

}