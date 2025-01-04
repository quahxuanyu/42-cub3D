/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:38:29 by xquah             #+#    #+#             */
/*   Updated: 2025/01/03 21:34:07 by xquah            ###   ########.fr       */
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

// /**
//  * @brief Draw the 3D projection, by drawing vertical lines of varying heights depending on the lenght of the ray
//  * This function draws one single vertical line
//  */
// void	three_d_projection(t_game *game, float ray_x, float ray_y, int screen_x)
// {
// 	// float dist = sqrt((ray_x - game->player.x) * (ray_x - game->player.x) + (ray_y - game->player.y) * (ray_y - game->player.y));
// 	float dist = fixed_dist(game->player.x, game->player.y, ray_x, ray_y, game);
// 	float height = (WALL_SIZE / dist) * (	screenWidth / 2);
// 	int screen_y = (screenHeight - height) / 2;
// 	int end_y = screen_y + height;
// 	while (screen_y < end_y)
// 	{
// 		// put_texture_pixel(game, screen_x, screen_y);
// 		my_mlx_pixel_put(game, screen_x, screen_y, 0x00FF0000);
// 		screen_y++;
// 	}
// }