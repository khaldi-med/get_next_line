#include "get_next_line.h"

char	*ft_free_null(char *ptr)
{
	free(ptr);
	ptr = NULL;
	return (NULL);
}

char	*ft_read_file(int fd, char *stored)
{
	char	*buffer;
	int		bytes_read;
	char	*temp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free_null(stored));
	bytes_read = 1;
	while (bytes_read > 0 && (!ft_strchr(stored, '\n') || !stored))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), ft_free_null(stored));
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(stored, buffer);
		if (!temp)
			return (free(buffer), ft_free_null(stored));
		free(stored);
		stored = temp;
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

	int i, j;
	if (!stored)
		return (NULL);
	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	if (!stored[i] || !stored[i + 1])
		return (ft_free_null(stored));
	rest = malloc(sizeof(char) * (ft_strlen(&stored[i + 1]) + 1));
	if (!rest)
		return (ft_free_null(stored));
	j = 0;
	i++; // Skip the newline
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
