/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:43:28 by xquah             #+#    #+#             */
/*   Updated: 2025/01/15 14:04:48 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;
    unsigned char *str1;
    unsigned char *str2;

    // Add NULL pointer checks
    if (!s1 || !s2)
        return (-1);  // or return a different value that makes sense for your use case

    str1 = (unsigned char *) s1;
    str2 = (unsigned char *) s2;
    i = 0;
    while (i < n && (str1[i] != '\0' || str2[i] != '\0'))
    {
        if (str1[i] != str2[i])
            return (str1[i] - str2[i]);
        i++;
    }
    return (0);
}
