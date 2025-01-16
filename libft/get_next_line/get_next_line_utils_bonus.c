/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:09:52 by xquah             #+#    #+#             */
/*   Updated: 2025/01/15 14:05:09 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = -1;
	while (s[++i])
		continue ;
	return (i);
}

char	*ft_strjoin_special(char const *s1, char const *s2, int bytes_read)
{
	char	*str;
	int		s1_len;
	int		i;

	if (!s1)
		s1_len = 0;
	else
		s1_len = ft_strlen(s1);
	i = -1;
	str = malloc((s1_len + bytes_read + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (s1_len != 0)
	{
		while (s1[++i])
			str[i] = s1[i];
		i--;
	}
	while (++i - s1_len < bytes_read)
		str[i] = s2[i - s1_len];
	str[s1_len + bytes_read] = '\0';
	return (str);
}

char *ft_strchr_gnl(const char *s, int c)
{
    char *temp;
    size_t i;

    // Check for null pointer
    if (!s)
        return (NULL);

    temp = (char *)s;
    i = 0;

    // Continue until we find the character or reach the end of string
    while (temp[i] != '\0')
    {
        if (temp[i] == (char)c)
            return (&temp[i]);
        i++;
    }

    // Check one more time for null terminator if that's what we're looking for
    if ((char)c == '\0')
        return (&temp[i]);

    return (NULL);
}

char	*ft_strdup_gnl(const char *s1)
{
	int		i;
	char	*str;

	str = (char *)malloc(ft_strlen((char *)s1) + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}

int	line_len(char *buffer)
{
	int	len;

	len = 0;
	while (*buffer != '\n' && *buffer)
	{
		len++;
		buffer++;
	}
	if (*buffer == '\n')
		len++;
	return (len);
}
