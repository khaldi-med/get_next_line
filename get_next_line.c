/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 02:18:51 by mohkhald          #+#    #+#             */
/*   Updated: 2025/01/13 08:25:49 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free_null(char *buff)
{
	free(buff);
	buff = NULL;
	return (NULL);
}

static char	*ft_fill_stash(int fd, char *stash)
{
	int		bites_read;
	char	*buffer;
	char	*temp;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (ft_free_null(stash));
	bites_read = 1;
	while (bites_read > 0 && (!stash || !ft_strchr(stash, '\n')))
	{
		bites_read = read(fd, buffer, BUFFER_SIZE);
		if (bites_read < 0)
			return (free(buffer), ft_free_null(stash));
		buffer[bites_read] = '\0';
		temp = ft_strjoin(stash, buffer);
		if (!temp)
			return (free(buffer), ft_free_null(stash));
		stash = temp;
	}
	free(buffer);
	return (stash);
}

static char	*ft_extract_stash(char *stash)
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
	i = -1;
	while (stash[++i] && stash[i] != '\n')
		line[i] = stash[i];
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*ft_uppdate_stash(char *stash)
{
	char	*rest;
	int		i;
	int		j;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i] || !stash[i + 1])
		return (ft_free_null(stash));
	rest = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!rest)
		return (ft_free_null(stash));
	i++;
	j = 0;
	while (stash[i])
		rest[j++] = stash[i++];
	rest[j] = '\0';
	free(stash);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, NULL, 0) == -1))
	{
		if (stash)
			stash = ft_free_null(stash);
		return (NULL);
	}
	stash = ft_fill_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_extract_stash(stash);
	stash = ft_uppdate_stash(stash);
	return (line);
}
