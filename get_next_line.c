#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		total_len;
	int		i;
	int		j;

	if (!s2)
		return (s1);
	total_len = (s1 ? ft_strlen(s1) : 0) + ft_strlen(s2);
	result = malloc(sizeof(char) * (total_len + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j])
		result[i++] = s1[j++];
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	free(s1);
	return (result);
}

char	*ft_read_to_stash(int fd, char *stash)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && (!stash || !ft_strchr(stash, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*ft_extract_line(char *stash)
{
	char	*line;
	int		i;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_update_stash(char *stash)
{
	char	*new_stash;
	int		i;
	int		j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	i++;
	new_stash = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!new_stash)
	{
		free(stash);
		return (NULL);
	}
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	stash[fd] = ft_read_to_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = ft_extract_line(stash[fd]);
	stash[fd] = ft_update_stash(stash[fd]);
	return (line);
}

// char	*ft_read_file(int fd, char *stored)
// {
// 	char	*buffer;
// 	int		bytes_read;
// 	char	*temp;
// 
// 	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
// 	if (!buffer)
// 	{
// 		free(stored);
// 		return (NULL);
// 	}
// 	while (1)
// 	{
// 		bytes_read = read(fd, buffer, BUFFER_SIZE);
// 		if (bytes_read <= 0)
// 		{
// 			free(buffer);
// 			return (stored);
// 		}
// 		buffer[bytes_read] = '\0';
// 		temp = ft_strjoin(stored, buffer);
// 		free(stored);
// 		if (!temp)
// 		{
// 			free(buffer);
// 			return (NULL);
// 		}
// 		stored = temp;
// 		if (ft_strchr(stored, '\n'))
// 		{
// 			free(buffer);
// 			return (stored);
// 		}
// 	}
// }
// 
// char	*ft_get_line(char *stored)
// {
// 	char	*line;
// 	int		i;
// 
// 	i = 0;
// 	if (!stored || !stored[0])
// 		return (NULL);
// 	while (stored[i] && stored[i] != '\n')
// 		i++;
// 	line = malloc(sizeof(char) * (i + 2)); // +2 for '\n' and '\0'
// 	if (!line)
// 		return (NULL);
// 	i = 0;
// 	while (stored[i] && stored[i] != '\n')
// 	{
// 		line[i] = stored[i];
// 		i++;
// 	}
// 	if (stored[i] == '\n')
// 		line[i++] = '\n';
// 	line[i] = '\0';
// 	return (line);
// }
// 
// char	*ft_save_rest(char *stored)
// {
// 	char	*rest;
// 	char	*newline_ptr;
// 
// 	rest = NULL;
// 	if (!stored)
// 		return (NULL);
// 	newline_ptr = ft_strchr(stored, '\n');
// 	if (newline_ptr)
// 	{
// 		rest = ft_strdup(newline_ptr + 1);
// 	}
// 	free(stored);
// 	return (rest);
// }
// 
// char	*get_next_line(int fd)
// {
// 	static char	*stored;
// 	char		*line;
// 
// 	stored = NULL;
// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	stored = ft_read_file(fd, stored);
// 	if (!stored)
// 		return (NULL);
// 	line = ft_get_line(stored);
// 	stored = ft_save_rest(stored);
// 	return (line);
// }


