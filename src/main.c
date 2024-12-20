/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:32:28 by xquah             #+#    #+#             */
/*   Updated: 2024/12/20 17:40:53 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int main(int ac, char **av)
{
	t_game game;
	
	 if (check_input(ac, av))
    {
        return (1);
    }

    init_game(&game);

    init_texture(&game, "textures/wood.xpm"); // Ensure this path is correct

    mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
    mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
    mlx_loop_hook(game.mlx, draw_loop, &game);

    mlx_loop(game.mlx);
    return (0);
}