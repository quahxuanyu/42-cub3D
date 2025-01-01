/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 21:16:59 by hheng             #+#    #+#             */
/*   Updated: 2025/01/01 21:26:33 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Store player map position */
void    store_player_position(t_game *game)
{
    int    i;
    int    j;

    i = 0;
    while (game->map[i] != NULL)
    {
        j = 0;
        while (game->map[i][j] != '\0')
        {
            if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
                || game->map[i][j] == 'W' || game->map[i][j] == 'E')
            {
                game->player.x = (float)j;
                game->player.y = (float)i;
                set_player_angle(game, game->map[i][j]);
            }
            j++;
        }
        i++;
    }
}

/* Set player angle based on direction character */
void    set_player_angle(t_game *game, char direction)
{
    switch (direction)
    {
        case 'N':
            game->player.angle = 270; // -90 degrees in your original
            break;
        case 'S':
            game->player.angle = 90;
            break;
        case 'E':
            game->player.angle = 0;
            break;
        case 'W':
            game->player.angle = 180;
            break;
    }
}

/* Initialize player movement flags */
void    init_player_movement(t_game *game)
{
    game->player.key_up = false;
    game->player.key_down = false;
    game->player.key_left = false;
    game->player.key_right = false;
    game->player.left_rotate = false;
    game->player.right_rotate = false;
}

/* Update player's initial state */
void    update_player(t_game *game)
{
    store_player_position(game);
    init_player_movement(game);
}