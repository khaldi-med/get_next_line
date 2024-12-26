//#include <get_next_line.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	char	str[256];
	int		read_char;
	int		fd;

	fd = open("text.txt", O_RDONLY);
	while ((read_char = read(fd, str, 5)))
	{
		str[read_char] = '\0';
		printf("red -> %s\n", str);
	}
	return (0);
}
