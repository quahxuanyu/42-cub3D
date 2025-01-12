/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:55:12 by hheng             #+#    #+#             */
/*   Updated: 2025/01/12 14:08:51 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/***
 * @brief Initialize player's position and direction
 * @note Later when parsing is finish initialize the player position from file
 * @note CURRENT: (Hardcode) Set player position to (5, 5) and North facing
 */
void	init_player(t_player *player)
{
    player->dir = 'N'; //set facing north for now
    player->pos_x = 5 + 0.5; //set in middle for now
    player->pos_y = 5 + 0.5; //set in middle for now
    player->dir_x = 0;
    player->dir_y = -1;
    player->plane_x = 0.66;
    player->plane_y = 0;
    player->key_up = false;
    player->key_down = false;
    player->key_left = false;
    player->key_right = false;
    player->left_rotate = false;
    player->right_rotate = false;
}

/***
 * @brief Initialize the player, map, texture
 * @param game the game structure
 * @param map_file the map file
 * @param texture_file the texture file (NOT currently in use)
*/
void init_all(t_game *game, char *map_file, char *texture_file)
{
    init_player(&game->player); // Step 1: Initialize player position and direction
    init_mlx(game); // Step 2: Initialize MLX
    init_texture(game); // Step 3: Initialize texutures and colors of ceiling (Temporary hardcode texutures)
    game->map_data.map = get_map(map_file); // Step 4: Load and validate the map
    if (!game->map)
    {
        printf("Error: Failed to load map\n");
        exit(EXIT_FAILURE);
    }    

    //Debug
    printf("Player position: x=%f, y=%f, angle=%f\n", 
           game->player.pos_x, game->player.pos_y, game->player.angle);
    printf("Map loaded successfully.\n");
}
