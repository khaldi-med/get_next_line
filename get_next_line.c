#include "get_next_line.h"

char	*ft_read_file(int fd, char *stored)
{
	char	*buffer;
	int		bytes_read;
	char	*temp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		free(stored);
		return (NULL);
	}
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			return (stored);
		}
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(stored, buffer);
		free(stored);
		if (!temp)
		{
			free(buffer);
			return (NULL);
		}
		stored = temp;
		if (ft_strchr(stored, '\n'))
		{
			free(buffer);
			return (stored);
		}
	}
}

char	*ft_get_line(char *stored)
{
	char	*line;
	int		i;

	i = 0;
	if (!stored || !stored[0])
		return (NULL);
	while (stored[i] && stored[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2)); // +2 for '\n' and '\0'
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
	char	*newline_ptr;

	rest = NULL;
	if (!stored)
		return (NULL);
	newline_ptr = ft_strchr(stored, '\n');
	if (newline_ptr)
	{
		rest = ft_strdup(newline_ptr + 1);
	}
	free(stored);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*stored;
	char		*line;

	stored = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stored = ft_read_file(fd, stored);
	if (!stored)
		return (NULL);
	line = ft_get_line(stored);
	stored = ft_save_rest(stored);
	return (line);
}
