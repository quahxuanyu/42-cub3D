/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:48:45 by xquah             #+#    #+#             */
/*   Updated: 2025/01/01 16:10:52 by hheng            ###   ########.fr       */
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
	float	angle_speed;
	float cos_angle;
	float sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	angle_speed = 0.01;
	
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	
	printf("angle: %f\n", player->angle);
	if (player->key_up && !touch(game, player->x + cos_angle * PLAYER_SPEED, player->y + sin_angle * PLAYER_SPEED))
	{
		player->x += cos_angle * PLAYER_SPEED;
		player->y += sin_angle * PLAYER_SPEED;
	}
	if (player->key_down && !touch(game, player->x - cos_angle * PLAYER_SPEED, player->y - sin_angle * PLAYER_SPEED))
	{
		player->x -= cos_angle * PLAYER_SPEED;
		player->y -= sin_angle * PLAYER_SPEED;
	}
	if (player->key_left && !touch(game, player->x + sin_angle * PLAYER_SPEED, player->y - cos_angle * PLAYER_SPEED))
	{
		player->x += sin_angle * PLAYER_SPEED;
		player->y -= cos_angle * PLAYER_SPEED;
	}
	if (player->key_right && !touch(game, player->x - sin_angle * PLAYER_SPEED, player->y + cos_angle * PLAYER_SPEED))
	{
		player->x -= sin_angle * PLAYER_SPEED;
		player->y += cos_angle * PLAYER_SPEED;
	}
}

/*	if (player->key_up)
	{
		player->x -= sin_angle * speed;
		player->y -= cos_angle * speed;
	}
	if (player->key_down)
	{
		player->x += sin_angle * speed;
		player->y += cos_angle * speed;
	}
	if (player->key_left)
	{
		player->x -= cos_angle * speed;
		player->y += sin_angle * speed;
	}
	if (player->key_right)
	{
		player->x += cos_angle * speed;
		player->y -= sin_angle * speed;
	}*/

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
                game->player.x = x * WALL_SIZE + (WALL_SIZE / 2);
                game->player.y = y * WALL_SIZE + (WALL_SIZE / 2);
                
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