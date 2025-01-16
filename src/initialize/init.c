/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:55:12 by hheng             #+#    #+#             */
/*   Updated: 2025/01/17 00:20:34 by hheng            ###   ########.fr       */
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
    memset(game, 0, sizeof(t_game));  // Initialize all to 0 first

    init_player(&game->player);
    init_mlx(game);
    init_texture(game);
    
    // Initialize map_data
    game->map_data.map = NULL;
    game->map_data.width = 0;
    game->map_data.height = 0;
}
