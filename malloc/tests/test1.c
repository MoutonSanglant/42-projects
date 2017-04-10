#include <stdio.h>

#include "../src/malloc.h"

int	main(void)
{
	int *table;

	printf("Calling malloc\n");
	table = malloc(sizeof(int) * 4);
	printf("malloc call succesfull (%p)\n", table);
	return (1);
}
