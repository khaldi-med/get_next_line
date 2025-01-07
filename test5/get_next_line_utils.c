#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_str;
	size_t	tot_len;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if(!s1)
		return ft_strdup(s2);
	if(!s2)
		return ft_strdup(s1);
	tot_len = ft_strlen(s1) + ft_strlen(s2);
	new_str = malloc(sizeof(char) * (tot_len + 1));
	if (!new_str)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i])
		new_str[i] = s1[i];
	j = -1;
	while (s2[++j])
		new_str[i + j] = s2[j];
	new_str[tot_len] = '\0';
	return (new_str);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*new_s;
	int		i;

	i = 0;
	len = ft_strlen(s) + 1;
	new_s = malloc(len);
	if (!new_s)
		return (NULL);
	while (s[i] && len != 0)
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
