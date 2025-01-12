/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:33:48 by xquah             #+#    #+#             */
/*   Updated: 2025/01/12 13:42:24 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x >= screenWidth || y >= screenHeight || x < 0 || y < 0)
		return ;
	dst = game->data + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int*) dst = color;
}

void    clear_image(t_game *game)
{
	int x;
	int y;

	x = -1;
	while (++x < screenWidth)
	{
		y = -1;
		while (++y < screenHeight)
			my_mlx_pixel_put(game, x, y, 0);
	}
}

void    set_ceiling_floor(t_game *game)
{
    int x;
    int y;

    x = -1;
    while (++x < screenWidth)
    {
        y = -1;
        while (++y < screenHeight)
        {
            if (y < screenHeight / 2)
                my_mlx_pixel_put(game, x, y, game->map_data.c_rgb);
            else
                my_mlx_pixel_put(game, x, y, game->map_data.f_rgb);
        }
    }
}

/***
 * @brief The main raycasting function.
 * @brief Shoots a ray for every pixel of the screen width
 * @param game the game structure
 */
void	raycast(t_game *game)
{
    int x;
    
    x = -1;
    while (++x < screenWidth)
    {
        init_ray(&game->player, &game->ray, x);
        get_initial_dist(&game->player, &game->ray);
        dda_algo(game, &game->player, &game->ray);
        calc_wall_dist(&game->ray);
        draw_line_on_image(game, &game->ray, x);
    }
}
