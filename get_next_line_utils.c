#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
	{
		len++;
	}
	return (len);
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

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	i;
	char	*new;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (start + len >= s_len)
		len = s_len - start;
	i = 0;
	new = (char *)malloc(len + 1);
	if (!new)
		return (NULL);
	while (i < len && s[start + i])
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

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

// char	*ft_strdup_until(const char *s, const char *end)
// {
// 	size_t	len;
// 	char	*dest;
// 	size_t	i;
// 
// 	if (!s || !end || end < s)
// 		return (NULL);
// 	len = end - s;
// 	dest = malloc(len + 1);
// 	if (!dest)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		dest[i] = s[i];
// 		i++;
// 	}
// 	dest[len] = '\0';
// 	return (dest);
// }
