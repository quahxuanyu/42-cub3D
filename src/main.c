/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:32:28 by xquah             #+#    #+#             */
/*   Updated: 2025/01/01 16:33:02 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void setup_hooks(t_game *game)
{
    mlx_hook(game->win, 2, 1L << 0, key_press, &game->player);
    mlx_hook(game->win, 3, 1L << 1, key_release, &game->player);
    mlx_loop_hook(game->mlx, draw_loop, game);
}

int main(int ac, char **av)
{
    t_game game;
    init_all(&game, av[1], av[2]);
    setup_hooks(&game);

// Start the rendering loop
    mlx_loop(game.mlx);

    return (0);
}
