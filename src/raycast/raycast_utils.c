/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:33:48 by xquah             #+#    #+#             */
/*   Updated: 2025/01/01 16:11:30 by hheng            ###   ########.fr       */
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

void draw_map(t_game *game)
{
    int x;
    int y;

    y = -1;
    if (!game->map)
    {
        printf("Error: game->map is NULL\n");
        return;
    }


    while (game->map[++y])
    {
        if (!game->map[y])
        {
            printf("Error: game->map[%d] is NULL\n", y);
            return;
        }

        x = -1;
        while (game->map[y][++x])
        {
            if (game->map[y][x] == '1')
            {
                draw_square(x * WALL_SIZE, y * WALL_SIZE, WALL_SIZE, 0x0000FF, game);
            }
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


//for raycast
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
    {
        raycast(game);
    }

    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);


    return (0);
}