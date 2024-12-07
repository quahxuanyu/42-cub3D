/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:03:07 by xquah             #+#    #+#             */
/*   Updated: 2024/02/26 15:34:20 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*temp;
	char	*final_str;
	int		len;
	int		i;

	len = ft_strlen((char *) s);
	temp = (char *) s;
	i = -1;
	final_str = (NULL);
	while (++i <= len)
		if (temp[i] == (char) c)
			final_str = &temp[i];
	return (final_str);
}
