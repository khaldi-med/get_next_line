#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int		fd;
// 	char	*line;

	fd = open("text.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening file\n");
		return (1);
	}
	printf("Line read: %s", get_next_line(fd));
	printf("Line read: %s", get_next_line(fd));
	close(fd);
	return (0);
}
