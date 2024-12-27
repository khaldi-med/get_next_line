#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 5

char	*ft_get_line(char *str, int fd)
{
	char	*buffer;
	int		bit_read;

	bit_read = 0;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!str)
		str = ft_strdup("");
	while ((bit_read = read(fd, buffer, BUFFER_SIZE)))
	{
		str[bit_read] = buffer[bit_read];
	}
	str[bit_read] = '\0';
	return (str);
}

// char	ft_clean_line(void)
// {
// }
//
// char	*ft_get_next_line(int fd)
// {
// 	char	*buffer;
// 	int		bit_read;
//
// 	bit_read = 0;
// 	if (!BUFFER_SIZE || read(fd, 0, 0) < 0)
// 		return (NULL);
// 	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
// 	if (!buffer)
// 		return (NULL);
// }

int	main(void)
{
	char	*str;
	char	*res;
	int		fd;

	str = NULL;
	fd = open("text.txt", O_RDONLY);
	res = ft_get_line(str, fd);
	printf("red-> %s\n", res);
	return (0);
}
