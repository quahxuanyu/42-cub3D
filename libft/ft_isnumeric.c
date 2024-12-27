/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 12:51:02 by hheng             #+#    #+#             */
/*   Updated: 2024/12/22 12:51:09 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool ft_isnumeric(char *str)
{
    if (!str || !*str)
        return false;

    int i = 0;
    if (str[i] == '-' || str[i] == '+') // Handle optional sign
        i++;

    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return false;
        i++;
    }

    return true;
}