/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:15:31 by xquah             #+#    #+#             */
/*   Updated: 2024/03/07 15:30:06 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;

	if (count && size && count > INT_MAX / size)
		return (NULL);
	arr = malloc(count * size);
	if (!arr)
		return (arr);
	ft_bzero(arr, count * size);
	return (arr);
}
