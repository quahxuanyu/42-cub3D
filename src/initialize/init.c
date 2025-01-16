/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:55:12 by hheng             #+#    #+#             */
/*   Updated: 2025/01/16 17:00:42 by hheng            ###   ########.fr       */
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
    printf("Debug: Initializing game\n");
    memset(game, 0, sizeof(t_game));  // Initialize all to 0 first
    printf("Debug: Game structure initialized to zero\n");

    init_player(&game->player);
    printf("Debug: Player initialized\n");

    init_mlx(game);
    printf("Debug: MLX initialized\n");

    init_texture(game);
    printf("Debug: Textures initialized\n");
    
    // Initialize map_data
    game->map_data.map = NULL;
    game->map_data.width = 0;
    game->map_data.height = 0;
    printf("Debug: Map data initialized\n");
    
    // if (!game->map_data.map && map_file)  // Only try to load if we have a file
    // {
    //     printf("Error: Map not properly initialized\n");
    //     exit(EXIT_FAILURE);
    // }    
    printf("Debug: Initialization complete\n");
}
