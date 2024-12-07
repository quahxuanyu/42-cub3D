/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:11:09 by xquah             #+#    #+#             */
/*   Updated: 2024/03/07 15:55:12 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p_dest;
	unsigned char	*p_src;

	p_dest = (unsigned char *) dst;
	p_src = (unsigned char *) src;
	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		p_dest += len;
		p_src += len;
		while (len--)
			*--p_dest = *--p_src;
	}
	else
		while (len--)
			*p_dest++ = *p_src++;
	return (dst);
}
