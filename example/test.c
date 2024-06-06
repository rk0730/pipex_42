#include <stdio.h>
#include <unistd.h>

int	main()
{
	if (access("/bin/ls -l", X_OK) == 0)
	{
		printf("File is executable.\n");
	}
	else
	{
		printf("File is not executable.\n");
	}
}