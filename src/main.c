/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:32:28 by xquah             #+#    #+#             */
/*   Updated: 2024/12/18 12:46:37 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_map(t_game *game)
{
	int x;
	int y;
	
	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			if (game->map[y][x] == '1')
				draw_square(x * WALL_SIZE, y * WALL_SIZE, WALL_SIZE, 0x0000FF, game);
		}
	}
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

//IMPORTANT - Calculate the collision of the ray and walls
bool touch(t_game *game, float px, float py)
{
	int	x;
	int	y;
	
	//rounds to int to allow it to index the map, and check whether a wall exist
	x = px / WALL_SIZE;
	y = py / WALL_SIZE;
	if (game->map[y][x] == '1')
		return true;
	return false;
}

void	draw_ray(t_game *game, float angle_diff, int x)
{
	float ray_x;
	float ray_y;
	float cos_angle;
	float sin_angle;

	// DDA Line Algorithm
	ray_x = game->player.x; // Reset ray_x
	ray_y = game->player.y; // Reset ray_y
	cos_angle = cos(game->player.angle + angle_diff); // they are all below 1
	sin_angle = sin(game->player.angle + angle_diff);
	while (!touch(game, ray_x, ray_y))
	{
		if (VIEW_STATE == 2)
			my_mlx_pixel_put(game, ray_x, ray_y, 0xFFFF00);
		ray_x += cos_angle; //The 0 degree position poitns to the right
		ray_y += sin_angle;
	}
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
	while (++i < screenWidth)
	{
		draw_ray(game, angle_diff, i);
		angle_diff += fraction;
	}
}

int draw_loop(t_game *game)
{
	t_player *player = &game->player;
	move_player(game, player);
	clear_image(game);
	if (VIEW_STATE == 2)
	{
		draw_map(game);
		raycast(game);
		draw_square(player->x, player->y, 10, 0x00FFFF, game);
	}
	else
		raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int main(void)
{
	t_game game;

	init_game(&game);
	init_texture(&game, "/home/quahxuanyu/42KL/42-cub3D/textures/wood.xpm"); //for some reason need full path for it to find the file
	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
}