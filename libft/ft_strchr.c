/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:54:12 by xquah             #+#    #+#             */
/*   Updated: 2024/02/26 15:32:44 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*temp;
	int		len;
	int		i;

	len = ft_strlen((char *) s);
	temp = (char *) s;
	i = -1;
	while (++i <= len)
		if (temp[i] == (char) c)
			return (&temp[i]);
	return (NULL);
}
