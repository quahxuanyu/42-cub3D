/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:48:45 by xquah             #+#    #+#             */
/*   Updated: 2025/01/03 15:48:46 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int key_press(int keycode, t_player *player)
{
	// printf("keycode: %d\n", keycode);
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	if (keycode == ESC)
		exit(0);
	return (0);
}

int key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

void	move_player(t_game *game, t_player *player)
{
	if (player->key_up)
		move_up(game);
	if (player->key_down)
		move_down(game);
	if (player->key_left)
		move_left(game);
	if (player->key_right)
		move_right(game);
	if (player->left_rotate)
		rotate_left(game);
	if (player->right_rotate)
		rotate_right(game);
}

bool init_player_position(t_game *game)
{
    const char player_chars[] = "NSEW";
    int found = 0;
    
    for (int y = 0; game->map[y]; y++)
    {
        for (int x = 0; game->map[y][x]; x++)
        {
            char cell = game->map[y][x];
            if (ft_strchr(player_chars, cell))
            {
                game->player.pos_x = x * WALL_SIZE + (WALL_SIZE / 2);
                game->player.pos_y = y * WALL_SIZE + (WALL_SIZE / 2);
                
                // Set initial angle based on direction
                if (cell == 'N') game->player.angle = -PI/2;
                else if (cell == 'S') game->player.angle = PI/2;
                else if (cell == 'E') game->player.angle = 0;
                else if (cell == 'W') game->player.angle = PI;
                
                found = 1;
                // Replace player position with empty space
                game->map[y][x] = '0';
                break;
            }
        }
        if (found) break;
    }
    
    return found;
}