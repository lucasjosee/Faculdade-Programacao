#include <stdio.h>


int main()
{
	int a = 0, n;
	scanf("%d", &n);
	
	for(int i = n; i > 1; i /= 2)
	{
		a--;
	}
	for(int i = 0; i < 5; i++)
	{
		for(int j = n; j > 1; j /= 2)
		{
			a--;
		}
	}
	printf("%d", a);
}
