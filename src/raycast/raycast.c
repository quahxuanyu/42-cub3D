/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:33:48 by xquah             #+#    #+#             */
/*   Updated: 2025/01/04 16:40:34 by xquah            ###   ########.fr       */
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

void clear_image(t_game * game)
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

//for raycast
int draw_loop(t_game *game)
{
    move_player(game, &game->player);
    clear_image(game);
    raycast(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0);
}