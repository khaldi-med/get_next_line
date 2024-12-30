#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_read_file(int fd, char *stored)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(stored, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stored = ft_strjoin(stored, buffer);
	}
	free(buffer);
	return (stored);
}

char	*ft_get_line(char *stored)
{
	char	*line;
	int		i;

	if (!stored || !stored[0])
		return (NULL);
	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	if (stored[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = -1;
	while (stored[++i] && stored[i] != '\n')
		line[i] = stored[i];
	if (stored[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_save_rest(char *stored)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	if (!stored[i])
	{
		free(stored);
		return (NULL);
	}
	rest = malloc(sizeof(char) * (ft_strlen(&stored[i + 1]) + 1));
	if (!rest)
		return (NULL);
	i++;
	j = 0;
	while (stored[i])
		rest[j++] = stored[i++];
	rest[j] = '\0';
	free(stored);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*stored;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stored = ft_read_file(fd, stored);
	if (!stored)
		return (NULL);
	line = ft_get_line(stored);
	stored = ft_save_rest(stored);
	return (line);
}
