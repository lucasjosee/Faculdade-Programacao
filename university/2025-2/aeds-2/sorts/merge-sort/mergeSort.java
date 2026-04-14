import java.util.Random;

public class mergeSort
{
    public static void main(String[] args)
    {
        Random rand = new Random();

        int[] numeros = new int[10];

        for(int i = 0; i < numeros.length; i++)
        {
            numeros[i] = rand.nextInt(1000);
        }

        System.out.println("Antes:");
        printArray(numeros);

        mergeSort(numeros);

        System.out.println("Depois:");
        printArray(numeros);
    }

    private static void printArray(int[] array)
    {
        for(int i = 0; i < array.length; i++)
        {
            System.out.println(array[i]);
        }
    }

    private static void mergeSort(int[] array)
    {
        int tamanhoArray = array.length; //pegando o tamanho do array

        if(tamanhoArray < 2) //caso tenha apenas um elemento no array, ele ja vai está ordenado
        {
            return;
        }

        int metade = tamanhoArray / 2; //pegando a metade do array

        //criando os subArrays, isso ira acontecer ate sobra um unico elemento
        int[] esquerdaArray = new int[metade]; 
        int[] direitaArray = new int[tamanhoArray - metade];

        //Preenchendo o array com os seus determinados valores
        for(int i = 0; i < metade; i++)
        {
            esquerdaArray[i] = array[i];
        }
        for(int j = metade; j < tamanhoArray; j++)
        {
            direitaArray[j - metade] = array[j];
        }

        //Chamada recursiva
        mergeSort(esquerdaArray);
        mergeSort(direitaArray);

        merge(array, esquerdaArray, direitaArray);

    }

    private static void merge(int[] array, int[] esquerdaArray, int[] direitaArray)
    {
        int tamDireita = direitaArray.length, tamEsquerda = esquerdaArray.length;

        int i = 0, j = 0, k = 0;

        while(i < tamEsquerda && j < tamDireita)
        {
            if(esquerdaArray[i] <= direitaArray[j])
            {
                array[k] = esquerdaArray[i];
                i++;
            }
            else
            {
                array[k] = direitaArray[j];
                j++;
            }
            k++;
        }

        while(i < tamEsquerda)
        {
            array[k] = esquerdaArray[i];
            k++;
            i++;
        }

        while(j < tamDireita)
        {
            array[k] = direitaArray[j];
            k++;
            j++;
        }
    }
}