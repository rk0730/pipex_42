#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main()
{
	char	*str = (char *)malloc(sizeof(char) * 10);
	str = "Hello";
	write(1, str, 5);
	return (0);
}