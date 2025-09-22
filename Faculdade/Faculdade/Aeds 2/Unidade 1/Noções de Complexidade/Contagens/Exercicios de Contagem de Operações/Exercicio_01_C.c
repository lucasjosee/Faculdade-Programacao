#include <stdio.h>

int main()
{
	int a = 100;
	int n;
	scanf("%d", &n);
	int cont = 0;
	for(int i = n; i > 1; i /= 2)
	{
		a--;
		cont++;
	}

	
	int j = 0;
	while(j < n)
	{
		a--;
		cont++;
		j++;
	}
	
	printf("%d", cont);
}
