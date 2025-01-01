/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_store_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 21:19:37 by hheng             #+#    #+#             */
/*   Updated: 2025/01/01 21:56:56 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Store map width (size x) in game structure */
void    store_map_size_x(t_game *game, char **temp_map)
{
    int    i;
    int    len;
    int    max;

    i = 0;
    len = 0;
    max = -1;
    while (temp_map[i] != NULL)
    {
        len = ft_strlen(temp_map[i]);
        if (len > max)
            max = len;
        i++;
    }
    game->map_data.width = max;
}

/* Pad empty postion within the map with spaces */
void    pad_map_with_spaces(t_game *game, char **temp_map)
{
    int    i;
    int    j;
    int    len;

    // Assuming malloc_map is modified to use game struct
    malloc_map(game);
    i = 0;
    while (i < game->map_height)
    {
        len = ft_strlen(temp_map[i]);
        len--;
        j = 0;
        while (j < game->map_data.width)
        {
            if (j <= len && temp_map[i][j] != '\0')
                game->map[i][j] = temp_map[i][j];
            else
                game->map[i][j] = ' ';
            j++;
        }
        game->map[i][j] = '\n';
        game->map[i][j + 1] = '\0';
        i++;
    }
    ft_freesplit(temp_map);
}

/* Malloc game map - preparing for padding spaces */
/* Allocate the maximum number of map width for map */
void    malloc_map(t_game *game)
{
    int    i;

    i = 0;
    game->map = malloc(sizeof(char *) * (game->map_height + 1));
    if (!game->map)
        print_err_msg("Memory allocation failed for map");
    
    while (i < game->map_height)
    {
        game->map[i] = malloc(sizeof(char) * (game->map_data.width + 2));
        if (!game->map[i])
        {
            // Free previously allocated memory before exiting
            while (--i >= 0)
                free(game->map[i]);
            free(game->map);
            print_err_msg("Memory allocation failed for map row");
        }
        i++;
    }
    game->map[i] = NULL;
}