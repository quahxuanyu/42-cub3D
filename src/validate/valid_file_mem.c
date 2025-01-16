/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_file_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:15:49 by hheng             #+#    #+#             */
/*   Updated: 2025/01/16 17:32:27 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int get_map_dimensions(t_game *game)
{
    int i;
    int len;
printf("Debug: Getting map dimensions\n");
    game->map_data.height = 0;
    game->map_data.width = 0;
    i = 0;
    while (game->temp_map[i])
    {
        len = ft_strlen(game->temp_map[i]);
        if (len > game->map_data.width)
            game->map_data.width = len;
        game->map_data.height++;
        i++;
    }
    return (SUCCESS);
}

int allocate_final_map(t_game *game)
{
    int i;
	printf("Debug: Allocating final map\n");
    game->map_data.map = malloc(sizeof(char *) * (game->map_data.height + 1));
    if (!game->map_data.map)
        return (FAILURE);
    i = 0;
    while (i < game->map_data.height)
    {
        game->map_data.map[i] = malloc(game->map_data.width + 1);
        if (!game->map_data.map[i])
        {
            free_partial_map(game, i);
            return (FAILURE);
        }
        i++;
    }
    game->map_data.map[game->map_data.height] = NULL;
    return (SUCCESS);
}

int copy_map_from_temp(t_game *game)
{
    int row;
    int col;
    int len;
printf("Debug: Copying map from temp\n");
    row = 0;
    while (row < game->map_data.height)
    {
        len = ft_strlen(game->temp_map[row]);
        col = 0;
        while (col < game->map_data.width)
        {
            if (col < len)
                game->map_data.map[row][col] = game->temp_map[row][col];
            else
                game->map_data.map[row][col] = ' ';
            col++;
        }
        game->map_data.map[row][col] = '\0';
        row++;
    }
    return (SUCCESS);
}

void free_partial_map(t_game *game, int current_row)
{
    int i;

    i = 0;
    while (i < current_row)
    {
        if (game->map_data.map[i])
            free(game->map_data.map[i]);
        i++;
    }
    free(game->map_data.map);
    game->map_data.map = NULL;
}