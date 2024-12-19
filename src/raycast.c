/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:44:43 by xquah             #+#    #+#             */
/*   Updated: 2024/12/19 15:14:40 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// IMPORTANT - Calculate the collision of the ray and walls
bool touch(t_game *game, float px, float py)
{
	int map_x;
	int map_y;

	// Convert the ray's position to map grid coordinates
	map_x = px / WALL_SIZE;
	map_y = py / WALL_SIZE;
	// Check if the current grid cell contains a wall ('1')
	if (game->map[map_y][map_x] == '1')
		return true;
	return false;
}

bool	ray_touch(t_game *game, float ray_x, float ray_y)
{
	float	player_x;
	float	player_y;

	player_x = game->player.x;
	player_y = game->player.y;
	if (touch(game, ray_x, ray_y))
	{
		if (player_x - ray_x < player_y - ray_y)
		{
			if (player_x - ray_x > 0)
				game->side = 0;
			else
				game->side = 1;
		}
		else
		{
			if (player_y - ray_y > 0)
				game->side = 2;
			else
				game->side = 3;
		}
		return (true);
	}
	return (false);
}

void	draw_ray(t_game *game, float angle, int x)
{
	float ray_x;
	float ray_y;
	float cos_angle;
	float sin_angle;

	// DDA Line Algorithm
	ray_x = game->player.x; // Reset ray_x
	ray_y = game->player.y; // Reset ray_y
	cos_angle = cos(angle); // they are all below 1
	sin_angle = sin(angle);
	while (!ray_touch(game, ray_x, ray_y))
	{
		if (VIEW_STATE == 2)
			my_mlx_pixel_put(game, ray_x, ray_y, 0xFFFF00);
		ray_x += cos_angle; //The 0 degree position poitns to the right
		ray_y += sin_angle;
	}
	// printf("ray_x: %f, ray_y: %f\n", ray_x, ray_y);
	// printf("side: %i\n", game->side);
	if (VIEW_STATE == 3)
		three_d_projection(game, ray_x, ray_y, x);
}

void	raycast(t_game *game)
{
	float ray_x;
	float ray_y;
	float cos_angle;
	float sin_angle;
	float FOV = PI / 3;
	float fraction = FOV / screenWidth;
	float angle_diff = (FOV / 2) * -1;	
	int i = -1;
	// draw_ray(game, game->player.angle, i);
	while (++i < screenWidth)
	{
		draw_ray(game, angle_diff + game->player.angle, i);
		angle_diff += fraction;
	}
}