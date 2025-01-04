#include "get_next_line.h"

// static char	*update_storage(char **storage, char *newline_pos)
// {
// 	char	*temp;
// 	char	*line;
//
// 	temp = *storage;
// 	line = ft_substr(*storage, 0, newline_pos - *storage + 1);
// 	*storage = ft_strdup(newline_pos + 1);
// 	free(temp);
// 	return (line);
// }
//
// static char	*finalize_storage(char **storage)
// {
// 	char	*line;
//
// 	line = ft_strdup(*storage);
// 	free(*storage);
// 	*storage = NULL;
// 	return (line);
// }
//
// static char	*append_buffer(char **storage, char *buffer)
// {
// 	char	*temp;
// 	char	*new_storage;
//
// 	temp = *storage;
// 	new_storage = ft_strjoin(*storage, buffer);
// 	free(temp);
// 	return (new_storage);
// }
//
// char	*get_next_line(int fd)
// {
// 	static char	*storage;
// 	char		buffer[BUFFER_SIZE + 1];
// 	ssize_t		bytes_read;
// 	char		*newline_pos;
//
// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	while (!(newline_pos = ft_strchr(storage, '\n')))
// 	{
// 		bytes_read = read(fd, buffer, BUFFER_SIZE);
// 		if (bytes_read <= 0)
// 		{
// 			if (storage && *storage)
// 				return (finalize_storage(&storage));
// 			free(storage);
// 			return (NULL);
// 		}
// 		buffer[bytes_read] = '\0';
// 		storage = append_buffer(&storage, buffer);
// 		if (!storage)
// 			return (NULL);
// 	}
// 	return (update_storage(&storage, newline_pos));
// }

static char	*ft_free_and_nullify(char *ptr)
{
	free(ptr);
	ptr = NULL;
	return (NULL);
}

char	*ft_fill_stash(int fd, char *stash)
{
	char	*buffer;
	int		bytes_read;
	char	*temp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (ft_free_and_nullify(stash));
		}
		buffer[bytes_read] = '\0';
		temp = stash;
		stash = ft_strjoin(stash, buffer);
		free(temp);
		if (!stash)
			return (ft_free_and_nullify(buffer));
	}
	free(buffer);
	return (stash);
}

char	*ft_extract_line(char *stash)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!stash || !stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
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
	size_t	i;
	size_t	j;
	char	*new_stash;

	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (ft_free_and_nullify(stash));
	new_stash = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!new_stash)
		return (ft_free_and_nullify(stash));
	i++;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_fill_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_extract_line(stash);
	stash = ft_update_stash(stash);
	return (line);
}
