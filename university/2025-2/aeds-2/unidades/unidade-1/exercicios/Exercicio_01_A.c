#include <stdio.h>

int main()
{
	
	int a = 50, n;
	
	scanf("%d", &n);
	
	for(int i = 0; i < n; i++)
	{
		a--;
		a--;
		a--;
		
		for(int j = 0; j < (n * n) && i == 0; j++)
		{
			a--;
			a--;
		}
	}
	
	printf("%d", a);
	
	
}
