/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:38:29 by xquah             #+#    #+#             */
/*   Updated: 2024/12/18 13:54:04 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Calculate the distance between two points
 */
float distance(float delta_x, float delta_y)
{
	return (sqrt(delta_x * delta_x + delta_y * delta_y));
}

/**
 * @brief Calculate the distance between two points and the angle of the ray (to fix the fish eye effect)
 */
float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float	delta_x	= x2 - x1;
	float	delta_y = y2 - y1;
	float	angle = atan2(delta_y, delta_x) - game->player.angle;
	float	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

/**
 * @brief Draw the 3D projection, by drawing vertical lines of varying heights depending on the lenght of the ray
 */
void	three_d_projection(t_game *game, float ray_x, float ray_y, int x)
{
	// float dist = sqrt((ray_x - game->player.x) * (ray_x - game->player.x) + (ray_y - game->player.y) * (ray_y - game->player.y));
	float dist = fixed_dist(game->player.x, game->player.y, ray_x, ray_y, game);
	float height = (WALL_SIZE / dist) * (	screenWidth / 2);
	int start_y = (screenHeight - height) / 2;
	int end_y = start_y + height;
	while (start_y < end_y)
	{
		my_mlx_pixel_put(game, x, start_y, get_pixel_color(&game->tex, 0, 0));
		start_y++;
	}
}