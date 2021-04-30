#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv, char **env)
{

	int d;
	scanf("%d", &d);
	if (d < 0)
	{
		printf("User input - %d < 0\n", d);
		exit(1);
	}
	else
	{
		printf("User input - %d > 0\n", d);
		exit(0);
	}
}
