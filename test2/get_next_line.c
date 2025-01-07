#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_get_line(int fd, char *stored)
{
	char	*buffer;
	int		bytes_read;
	char	*temp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		temp = stored;
		stored = ft_strjoin(temp, buffer);
		free(temp);
		if (!stored)
			break ;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	if (bytes_read < 0)
	{
		free(stored);
		return (NULL);
	}
	return (stored);
}

char	*ft_extract_line(char *stored)
{
	int		i;
	char	*line;

	if (!stored || !*stored)
		return (NULL);
	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while(stored[i]){
		line[i] = stored[i];
		i++;
	}
	if(stored[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_save_rest(char *stored)
{
	char	*newline;
	char	*rest;

	if (!stored)
		return (NULL);
	newline = ft_strchr(stored, '\n');
	if (!newline)
	{
		free(stored);
		return (NULL);
	}
	rest = ft_strdup(newline + 1);
	free(stored);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*stored;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stored = ft_get_line(fd, stored);
	if (!stored)
		return (NULL);
	line = ft_extract_line(stored);
	stored = ft_save_rest(stored);
	return line;
}


