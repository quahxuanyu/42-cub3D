/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:31:14 by xquah             #+#    #+#             */
/*   Updated: 2024/12/17 22:44:56 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char **get_map(void)
{
	char **map;
	map = malloc(sizeof(char *) * 11); // Allocate space for 11 rows + 1 for NULL termination
	map[0] = "111111111111111111";
	map[1] = "100000000000100001";
	map[2] = "100010000000000001";
	map[3] = "100000000000000001";
	map[4] = "100010000010000001";
	map[5] = "100000000000000001";
	map[6] = "100000000000000001";
	map[7] = "101000000000000001";
	map[8] = "100000000000000001";
	map[9] = "111111111111111111";
	map[10] = NULL; // Null terminate the map
	return map;
}

void init_game(t_game *game)
{
	init_player(&game->player);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, screenWidth, screenHeight, "Raycast Test");
	game->img = mlx_new_image(game->mlx, screenWidth, screenHeight);
	game->data = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->line_length,
									&game->endian);
	game->map = get_map();
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}