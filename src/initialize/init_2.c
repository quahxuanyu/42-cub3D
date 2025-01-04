/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:55:12 by hheng             #+#    #+#             */
/*   Updated: 2025/01/02 21:21:08 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//Later when parsing is finished, we will initialize the player position from the map
void	init_player(t_player *player)
{
    player->dir = 'N'; //set facing north for now
    player->pos_x = 5 + 0.5; //set in middle for now
    player->pos_y = 5 + 0.5; //set in middle for now
    player->dir_x = 0;
    player->dir_y = -1;
    player->plane_x = 0.66;
    player->plane_y = 0;
}

// Parsing Helper function to initialize map data
void init_map_data(t_game *game)
{
    // Initialize texture pointers to NULL
    game->map_data.n_img.img = NULL;
    game->map_data.s_img.img = NULL;
    game->map_data.w_img.img = NULL;
    game->map_data.e_img.img = NULL;

    // Initialize RGB values to invalid values to ensure they get set
    game->map_data.c_rgb = (t_rgb){-1, -1, -1};
    game->map_data.f_rgb = (t_rgb){-1, -1, -1};

    game->map_data.map = NULL;
    game->map_data.width = 0;
    game->map_data.height = 0;
}

void init_all(t_game *game, char *map_file, char *texture_file)
{
    init_player(&game->player);
    init_mlx(game);

    // Step 3: Load and validate the map
    game->map_data.map = get_map(map_file);
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
           game->player.pos_x, game->player.pos_y, game->player.angle);
    printf("Map loaded successfully.\n");
}