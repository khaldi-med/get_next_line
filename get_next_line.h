/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 02:18:27 by mohkhald          #+#    #+#             */
/*   Updated: 2024/12/28 22:14:46 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

#include <stdlib.h>
#include <unistd.h>
// char	*ft_check_newline(char *buffer);
// char	*ft_save_rest(char *buffer);
// char	*ft_get_line(char *str, int fd);
char	*get_next_line(int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlen(const char *str);
#endif
