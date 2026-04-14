
## Algoritmo de Seleção 
Esse algoritmo varre o vetor procurando a posição do menor elemento, em seguida ele troca o menor elemento encontrado com a primeira posição do array. O segundo passo do algoritmo é repetir esse processo sempre desconsiderando o elemento que já foi trocado.
Exemplo:

for (int i = 0; i < (n - 1); i++) {
    int menor = i; 
    for (int j = (i + 1); j < n; j++){
        if (array[menor] > array[j]){
            menor = j;
        }
    }
    swap(menor, i);
}

## Algoritmo de Inserção
Esse algoritmo funciona como organizar cartas de um baralho na mão. Deve-se pegar cada carta (elemento do array), comparar com a que já tem na mão, e inseri-la na posição correta.
Exemplo:

for (int i = 1; i < n; i++) {
    int tmp = array[i];    pega a nova carta que vai ser inserida
    
    int j = i - 1;   pega a posição da ultima carta que foi colocada na mão
    
    while ( (j >= 0) && (array[j] > tmp) ){ compara e empurra os maiores p/ direita
        array[j + 1] = array[j];
        j--;
    }
    array[j + 1] = tmp; insere a carta que foi puxada na mao
}

## Quick Sort
Seu funcionamento básico consiste em escolher um elemento qualquer como pivô para um processo de partição dos elementos do _array_ em dois _subarrays_. Esse processo compara cada elemento do _array_ com o pivô e reorganiza o _array_ de tal forma que todos os elementos menores que o pivô ficam no _subarray_ à esquerda e os maiores, no _subarray_ à direita. Os elementos iguais ao pivô podem ficar em qualquer um dos dois subconjuntos. O próximo passo do algoritmo repete o processo em cada um dos _subarrays_ de tal forma que para cada _subarray_ tem um novo pivô e cada _subarray_ é particionado em dois novos _subarrays_. O algoritmo repete o processo de partição até que todos os _subarrays_ tenham somente um elemento.
exemplo recursivo:

 include<stdio.h>

void quicksort(int array[], int start, int end)
{
	if(end <= start) return;
	
	int pivot = particion(array, start, end);
	
	quicksort(array, start, pivot - 1);
	quicksort(array, pivot + 1, end);
}

int particion(int array[], int start, int end)
{
	int pivot = array[end];
	int i = start - 1;
	
	for(int j = start; j <= end; j++)
	{
		if(array[j] < pivot)
		{
			i++;
			
			int temp = array[i];
			array [i] = array[j];
			array [j] = temp;
		}
	}
	i++;
	int temp = array[i];
	array [i] = array[end];
	array [end] = temp;
	
	return i;
}

int main()
{
	int array[10] = {4, 7, 2, 3, 5, 9, 10, 6, 1, 8};

    int n = sizeof(array) / sizeof(array[0]);
    quicksort(array, 0, n - 1);

	for(int i = 0; i < 10; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");	
}