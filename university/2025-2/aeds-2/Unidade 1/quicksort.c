#include <stdio.h>

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
