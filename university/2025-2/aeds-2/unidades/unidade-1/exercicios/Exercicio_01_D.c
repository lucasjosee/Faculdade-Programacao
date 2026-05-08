#include <stdio.h>


int main()
{
	int a = 100, n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			for(int k = 0; k < 2 * n; k++)
			{
				a--;
			}
		}
	}
	
	for(int i = 0; i < 5; i++)
	{
		a--;
	}
	
	printf("%d", a);
}
