#include "get_next_line.h"

// Helper function to free memory and return NULL
static void	*cleanup(char *buffer, char *stash)
{
	if (buffer)
		free(buffer);
	buffer = NULL;
	if (stash)
		free(stash);
	stash = NULL;
	return (NULL);
}

// Reads from the file descriptor into the stash until a newline is found
char	*ft_read_to_stash(int fd, char *stash)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (cleanup(NULL, stash));
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(stash, '\n'))
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (cleanup(buffer, stash));
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			return (cleanup(buffer, NULL));
	}
	free(buffer);
	return (stash);
}

// Extracts a line from the stash (up to the newline character)
char	*ft_extract_line(char *stash)
{
	char	*line;
	int		i;

	if (!stash || !*stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	ft_strlcpy(line, stash, i + 1);
	return (line);
}

// Updates the stash by removing the extracted line
char	*ft_update_stash(char *stash)
{
	char	*new_stash;
	int		i;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (cleanup(NULL, stash));
	new_stash = ft_strdup(&stash[i + 1]);
	free(stash);
	return (new_stash);
}

// Main function to get the next line from the file descriptor
char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_extract_line(stash);
	if (!line)
		return (cleanup(NULL, stash));
	stash = ft_update_stash(stash);
	return (line);
}
