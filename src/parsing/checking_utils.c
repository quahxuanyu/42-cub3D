/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:56:31 by hheng             #+#    #+#             */
/*   Updated: 2024/12/22 14:31:21 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void print_err_msg(char *msg)
{
	ft_printf("Error\n");
	ft_printf(msg);
	ft_printf("\n");
	exit(EXIT_FAILURE);
}

void free_map(char **map, size_t lines)
{
    for (size_t i = 0; i < lines; i++)
        free(map[i]);
    free(map);
}

size_t count_lines(char **map)
{
    size_t count = 0;
    while (map[count])
        count++;
    return count;
}
