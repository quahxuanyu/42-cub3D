/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:19:49 by xquah             #+#    #+#             */
/*   Updated: 2024/03/07 15:55:06 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*p_dest;
	char	*p_src;

	if (!dst && !src)
		return (dst);
	p_dest = (char *) dst;
	p_src = (char *) src;
	i = -1;
	while (++i < n)
		p_dest[i] = p_src[i];
	return (dst);
}
