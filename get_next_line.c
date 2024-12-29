#include "get_next_line.h"

// char	*ft_get_line(char *str, int fd)
// {
// 	char	*buffer;
// 	int		bytes_read;
// 	int		i;
//
// 	if (!str)
// 		return (NULL);
// 	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
// 	if (!buffer)
// 		return (NULL);
// 	bytes_read = read(fd, buffer, BUFFER_SIZE);
// 	if (bytes_read <= 0)
// 	{
// 		free(buffer);
// 		return (NULL);
// 	}
// 	buffer[bytes_read] = '\0';
// 	i = -1;
// 	while (++i < bytes_read)
// 		str[i] = buffer[i];
// 	str[i] = '\0';
// 	free(buffer);
// 	return (str);
// }
//
// char	*ft_check_newline(char *buffer)
// {
// 	char	*line;
// 	int		i;
// 	int		j;
//
// 	i = 0;
// 	while (buffer[i] && buffer[i] != '\n')
// 		i++;
// 	if (buffer[i] == '\n')
// 		i++;
// 	line = malloc(sizeof(char) * (i + 1));
// 	if (!line)
// 		return (NULL);
// 	j = -1;
// 	while (++j < i)
// 		line[j] = buffer[j];
// 	line[j] = '\0';
// 	return (line);
// }
//
// char	*ft_save_rest(char *buffer)
// {
// 	char	*rest;
// 	int		i;
// 	int		j;
//
// 	i = 0;
// 	while (buffer[i] && buffer[i] != '\n')
// 		i++;
// 	if (buffer[i] == '\n')
// 		i++;
// 	rest = malloc(sizeof(char) * (BUFFER_SIZE - i + 1));
// 	if (!rest)
// 		return (NULL);
// 	j = 0;
// 	while (buffer[i])
// 		rest[j++] = buffer[i++];
// 	rest[j] = '\0';
// 	return (rest);
// }
//
// char	*get_next_line(int fd)
// {
// 	char		*line;
// 	char		*buffer;
// 	static char	*stored;
//
// 	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
// 		return (NULL);
// 	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
// 	if (!buffer)
// 		return (NULL);
// 	stored = ft_get_line(buffer, fd);
// 	if (!stored)
// 	{
// 		free(buffer);
// 		return (NULL);
// 	}
// 	line = ft_check_newline(stored);
// 	if (!line)
// 		return (NULL);
// 	stored = ft_save_rest(stored);
// 	return (line);
// }
//
// Updated main.c

// char	*ft_get_line(char *buffer, int fd)
// {
// 	int	bytes_read;
//
// 	if (!buffer)
// 	{
// 		return (NULL);
// 	}
// 	bytes_read = read(fd, buffer, BUFFER_SIZE);
// 	if (bytes_read <= 0)
// 	{
// 		return (NULL);
// 	}
// 	buffer[bytes_read] = '\0';
// 	return (buffer);
// }
//
// char	*ft_check_newline(const char *buffer)
// {
// 	int		i;
// 	int		j;
// 	char	*line;
//
// 	i = 0;
// 	j = 0;
// 	while (buffer[i] && buffer[i] != '\n')
// 		i++;
// 	line = malloc(sizeof(char) * (i + 2));
// 	if (!line)
// 		return (NULL);
// 	while (j++ <= i++)
// 		line[j] = buffer[j];
// 	line[i + 1] = '\0';
// 	return (line);
// }
//
// char	*ft_save_rest(const char *buffer)
// {
// 	int		i;
// 	int		j;
// 	char	*rest;
//
// 	i = 0;
// 	j = 0;
// 	while (buffer[i] && buffer[i] != '\n')
// 		i++;
// 	if (!buffer[i])
// 		return (NULL);
// 	rest = malloc(sizeof(char) * (BUFFER_SIZE - i));
// 	if (!rest)
// 		return (NULL);
// 	i++;
// 	while (buffer[i])
// 		rest[j++] = buffer[i++];
// 	rest[j] = '\0';
// 	return (rest);
// }
//
// char	*get_next_line(int fd)
// {
// 	static char	*stored;
// 	char		*buffer;
// 	char		*line;
// 	char		*temp;
//
// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
// 	if (!buffer)
// 		return (NULL);
// 	if (!stored)
// 		stored = ft_get_line(buffer, fd);
// 	if (!stored)
// 	{
// 		free(buffer);
// 		return (NULL);
// 	}
// 	line = ft_check_newline(stored);
// 	temp = ft_save_rest(stored);
// 	stored = temp;
// 	free(buffer);
// 	return (line);
// }
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
		stored = temp ? ft_strncat(temp, buffer, bytes_read) : ft_ft_strdup(buffer);
		if (!stored)
		{
			free(temp);
			break ;
		}
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
	newline = ft_strchr(stored, '\n');
	if (!newline)
	{
		free(stored);
		return (NULL);
	}
	rest = ft_ft_strdup(newline + 1);
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
	return (line);
}
