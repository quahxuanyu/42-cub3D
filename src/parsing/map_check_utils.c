/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 21:38:14 by hheng             #+#    #+#             */
/*   Updated: 2025/01/16 21:46:15 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char **copy_map(char **original_map, int height)
{
    char **new_map;
    int i;
    
    new_map = (char **)malloc(sizeof(char *) * (height + 1));
    if (!new_map)
        return (NULL);
    
    i = 0;
    while (i < height)
    {
        new_map[i] = ft_strdup(original_map[i]);
        if (!new_map[i])
        {
            free_map(new_map);
            return (NULL);
        }
        i++;
    }
    new_map[height] = NULL;
    return (new_map);
}

void free_map(char **map)
{
    int i;
    
    if (!map)
        return;
    
    i = 0;
    while (map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}

void	print_err_msg(char *msg)
{
	printf("Error: %s\n", msg);
	printf("\n");
	exit(1);
}