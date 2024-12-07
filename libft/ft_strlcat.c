/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:12:18 by xquah             #+#    #+#             */
/*   Updated: 2024/03/07 17:00:17 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	initial_dest_length;

	if ((!dst || !src) && !dstsize)
		return (0);
	initial_dest_length = ft_strlen(dst);
	if (dstsize <= initial_dest_length)
		return (dstsize + ft_strlen(src));
	j = -1;
	i = initial_dest_length;
	while (src[++j] != '\0' && j < (dstsize - initial_dest_length - 1))
	{
		dst[i++] = src[j];
	}
	dst[i] = '\0';
	return (initial_dest_length + ft_strlen(src));
}
