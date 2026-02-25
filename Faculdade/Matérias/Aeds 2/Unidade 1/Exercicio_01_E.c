#include <stdio.h>


int main()
{
	int a = 0, n;
	scanf("%d", &n);
	
	for(int i = 0; i < (n * n * n); i++)
	{
		for(int j = 0; j < n * 9; j++)
		{
			a--;
		}
	}
	
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n * 5; j++)
		{
			a--;
		}
	}
	
	for(int i = 0; i < (n / 2); i++)
	{
		a--;
	}
	
	printf("%d", a);
}
