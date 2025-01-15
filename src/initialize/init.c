/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:55:12 by hheng             #+#    #+#             */
/*   Updated: 2025/01/15 13:35:52 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
