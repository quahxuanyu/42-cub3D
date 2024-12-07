/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:23:49 by xquah             #+#    #+#             */
/*   Updated: 2024/03/07 13:21:06 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	temp_i;
	size_t	j;

	i = -1;
	j = 0;
	if ((!haystack || !needle) && len == 0)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *) haystack);
	while (haystack[++i] != '\0' && i < len)
	{
		temp_i = i;
		while (haystack[i] == needle[j] && i < len)
		{
			if (needle[j + 1] == '\0')
				return (&((char *) haystack)[i - j]);
			j++;
			i++;
		}
		j = 0;
		i = temp_i;
	}
	return (NULL);
}
