#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

static char	*ft_get_line(char *str, int fd)
{
	char	*buffer;
	int		bytes_read;
	int		i;

	i = -1;
	bytes_read = 0;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[bytes_read] = '\0';
	while (++i < bytes_read)
		str[i] = buffer[i];
	str[i] = '\0';
	free(buffer);
	return (str);
}

static char	*ft_check_newline(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	j = -1;
	while (++j < i)
		line[j] = buffer[j];
	line[j] = '\0';
	return (line);
}

static char	*ft_save_rest(char *buffer)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	rest = malloc(sizeof(char) * (BUFFER_SIZE - i + 1));
	if (!rest)
		return (NULL);
	j = 0;
	while (buffer[i])
		rest[j++] = buffer[i++];
	rest[j] = '\0';
	return (rest);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*hold;
	char		*line;

	line = NULL;
	if (fd < 0 || !BUFFER_SIZE || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	hold = ft_get_line(buffer, fd);
	if (!hold)
	{
		free(buffer);
		return (NULL);
	}
	line = ft_check_newline(hold);
	if (!line)
		return (NULL);
	hold = ft_save_rest(hold);
	return (line);
}

int	main(void)
{
	char	*line;
	int		fd;

	fd = open("text.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Read content: '%s'\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
