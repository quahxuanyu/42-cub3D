/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:48:45 by xquah             #+#    #+#             */
/*   Updated: 2025/01/05 14:57:03 by xquah            ###   ########.fr       */
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

bool touch(t_game *game, float px, float py)
{
	int map_x;
	int map_y;

	map_x = (int)px;
	map_y = (int)py;
	//Debug
	// for (int i = 0; i < 10; i++)
	// {
	// 	printf("%s", game->map_data.map[i]);
	// }
	printf("\nmap_x: %d, map_y: %d\n", map_x, map_y);
	printf("to move x: %f, to move y: %f\n", px, py);
	printf("player->pos_x: %f, player->pos_y: %f\n", game->player.pos_x, game->player.pos_y);
	printf("player->dir_x: %f, player->dir_y: %f\n", game->player.dir_x, game->player.dir_y);
	// Consider spaces as walls
	return (game->map_data.map[map_y][map_x] == '1' || game->map_data.map[map_y][map_x] == ' ');
}

void	move_player(t_game *game, t_player *player)
{
	//Update, give player a set size to prevent camera flat on the wall
	if (player->key_up && !touch(game, game->player.pos_x + game->player.dir_x * MOVE_SPEED * 2, game->player.pos_y + game->player.dir_y * MOVE_SPEED * 2))
		move_up(game);
	if (player->key_down && !touch(game, game->player.pos_x - game->player.dir_x * MOVE_SPEED * 2, game->player.pos_y - game->player.dir_y * MOVE_SPEED * 2))
		move_down(game);
	if (player->key_left && !touch(game, game->player.pos_x + game->player.dir_y * MOVE_SPEED * 2, game->player.pos_y - game->player.dir_x * MOVE_SPEED * 2))
		move_left(game);
	if (player->key_right && !touch(game, game->player.pos_x - game->player.dir_y * MOVE_SPEED * 2, game->player.pos_y + game->player.dir_x * MOVE_SPEED * 2))
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