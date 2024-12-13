/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:32:28 by xquah             #+#    #+#             */
/*   Updated: 2024/12/13 18:00:36 by xquah            ###   ########.fr       */
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

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;

	i = -1;
	while (++i < size)
		my_mlx_pixel_put(game, x + i, y, color);
	i = -1;
	while (++i < size)
		my_mlx_pixel_put(game, x, y + i, color);
	i = -1;
	while (++i < size)
		my_mlx_pixel_put(game, x + i, y + size, color);
	i = -1;
	while (++i <= size)
		my_mlx_pixel_put(game, x + size, y + i, color);
}

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
	map[7] = "101000000010000001";
	map[8] = "100000000000000001";
	map[9] = "111111111111111111";
	map[10] = NULL; // Null terminate the map
	return map;
}

void init_game(t_game * game)
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

bool touch(t_game *game, float px, float py)
{
	int	x;
	int	y;
	
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
	
	float dist;

	ray_x = game->player.x; // Reset ray_x
	ray_y = game->player.y; // Reset ray_y
	cos_angle = cos(game->player.angle + angle_diff);
	sin_angle = sin(game->player.angle + angle_diff);
	while (!touch(game, ray_x, ray_y))
	{
		// my_mlx_pixel_put(game, ray_x, ray_y, 0xFFFF00);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	dist = sqrt((ray_x - game->player.x) * (ray_x - game->player.x) + (ray_y - game->player.y) * (ray_y - game->player.y));
	float height = (WALL_SIZE / dist) * (screenWidth / 2)	;
	int start_y = (screenHeight - height) / 2;
	int end = start_y + height;
	while (start_y < end)
	{
		my_mlx_pixel_put(game, x, start_y, 0xFF0000);
		start_y++;
	}
}

void	raycast(t_game *game)
{
	float ray_x;
	float ray_y;
	float cos_angle;
	float sin_angle;
	float fraction = PI / 3 / screenWidth;
	float FOV = PI / 3;
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
	// draw_map(game);
	raycast(game);
	// draw_square(player->x, player->y, 10, 0x00FFFF, game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int main(void)
{
	t_game game;

	init_game(&game);

	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
}