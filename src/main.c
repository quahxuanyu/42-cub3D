/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:32:28 by xquah             #+#    #+#             */
/*   Updated: 2025/01/15 14:12:36 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int draw_loop(t_game *game)
{
    move_player(game, &game->player);
    clear_image(game);
    set_ceiling_floor(game);
    raycast(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0);
}

void setup_hooks(t_game *game)
{
    mlx_hook(game->win, 2, 1L << 0, key_press, game);
    mlx_hook(game->win, 3, 1L << 1, key_release, &game->player);
    mlx_loop_hook(game->mlx, draw_loop, game);
}

int main(int ac, char **av)
{
    t_game game;
    char **temp_map;
// Check the input and the file
    if (go_to_check_file(&game, ac, av) == false)
        return (1);
    printf("Debug: File checked successfully\n");
// map_checking(&game, temp_map);
    init_all(&game, av[1], av[2]);
    printf("Debug: Game initialized successfully\n");

    setup_hooks(&game);
// Start the rendering loop
    mlx_loop(game.mlx);
    return (0);
}
