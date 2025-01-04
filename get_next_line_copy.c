#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (strdup(s2));
	if (!s2)
		return (strdup(s1));
	len1 = strlen(s1);
	len2 = strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	strcpy(result, s1);
	strcat(result, s2);
	return (result);
}

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
		if (strchr(buffer, '\n'))
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
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	strncpy(line, stored, i + (stored[i] == '\n'));
	line[i + (stored[i] == '\n')] = '\0';
	return (line);
}

char	*ft_save_rest(char *stored)
{
	char	*newline;
	char	*rest;

	if (!stored)
		return (NULL);
	newline = strchr(stored, '\n');
	if (!newline)
	{
		free(stored);
		return (NULL);
	}
	rest = strdup(newline + 1);
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

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return 1;
	}
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return 0;
}
