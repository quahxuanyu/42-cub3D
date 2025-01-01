/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:55:12 by hheng             #+#    #+#             */
/*   Updated: 2025/01/01 16:47:19 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_all(t_game *game, char *map_file, char *texture_file)
{
    init_player(&game->player);
    init_mlx(game);

    // Step 3: Load and validate the map
    game->map = get_map(map_file);
    if (!game->map)
    {
        printf("Error: Failed to load map\n");
        exit(EXIT_FAILURE);
    }

	printf("successfuly loaded map\n");

    // // Step 4: Initialize player position from the map
    // if (!init_player_position(game))
    // {
    //     printf("Error: No valid player position found in map\n");
    //     exit(EXIT_FAILURE);
    // }

    // init_texture(game, texture_file);

    // Debug print for initialization
    printf("Initialization complete:\n");
    printf("Player position: x=%f, y=%f, angle=%f\n", 
           game->player.x, game->player.y, game->player.angle);
    printf("Map loaded successfully.\n");
}

