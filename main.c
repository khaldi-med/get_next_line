#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

char	*ft_get_line(char *buffer, int fd)
{
	int	bytes_read;

	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	return (buffer);
}

char	*ft_check_newline(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if(buffer[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	while (j <= i)
		line[j++] = buffer[i++];
	line[j + 1] = '\0';
	return (line);
}

char	*ft_save_rest(const char *buffer)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (NULL);
	rest = malloc(sizeof(char) * (BUFFER_SIZE - i));
	if (!rest)
		return (NULL);
	i++;
	while (buffer[i])
		rest[j++] = buffer[i++];
	rest[j + 1] = '\0';
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*stored;
	char		*buffer;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (!stored)
		stored = ft_get_line(buffer, fd);
	line = ft_check_newline(stored);
	temp = ft_save_rest(stored);
	stored = temp;
	free(buffer);
	return (line);
}

int	main(void)
{
	char	*line;
	int		fd;

	fd = open("text.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Line read: '%s'\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
