#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening file\n");
		return (1);
	}
	line = get_next_line(fd);
	if (line)
	{
		printf("Line read: %s", line);
		free(line);
	}
	else
		printf("No line read or error occurred\n");
	close(fd);
	return (0);
}
