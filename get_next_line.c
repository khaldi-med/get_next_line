#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_read_file(int fd, char *stored)
{
	char	*buffer;
	int		bytes_read;
	char	*temp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && (!stored || !ft_strchr(stored, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free(stored), NULL);
		buffer[bytes_read] = '\0';
		if (!stored)
			stored = ft_strdup(buffer);
		else
		{
			temp = ft_strjoin(stored, buffer);
			free(stored);
			stored = temp;
		}
		if (!stored)
			return (free(buffer), NULL);
	}
	return (free(buffer), stored);
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
	i = 0;
	while (stored[i] && stored[i] != '\n')
	{
		line[i] = stored[i];
		i++;
	}
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

	if (!stored)
		return (NULL);
	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	if (!stored[i])
		return (free(stored), NULL);
	i++;
	rest = malloc(sizeof(char) * (ft_strlen(&stored[i]) + 1));
	if (!rest)
		return (free(stored), NULL);
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

	if (!stored || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stored = ft_read_file(fd, stored);
	if (!stored)
		return (NULL);
	line = ft_get_line(stored);
	stored = ft_save_rest(stored);
	return (line);
}
