/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 22:27:14 by xquah             #+#    #+#             */
/*   Updated: 2025/01/12 13:23:56 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/***
 * @brief Rotate the player to the right by multiplying the vectors (direction & camera)
 * @brief by the the rotation matrix with angle ROTATE_SPEED
 */
void	rotate_left(t_game *game)
{
	t_player *player = &game->player;
	double old_dir_x;
	double old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(-ROTATE_SPEED) - player->dir_y * sin(-ROTATE_SPEED);
	player->dir_y = old_dir_x * sin(-ROTATE_SPEED) + player->dir_y * cos(-ROTATE_SPEED);
	player->plane_x = player->plane_x * cos(-ROTATE_SPEED) - player->plane_y * sin(-ROTATE_SPEED);
	player->plane_y = old_plane_x * sin(-ROTATE_SPEED) + player->plane_y * cos(-ROTATE_SPEED);
}

/***
 * @brief Rotate the player to the right by multiplying the vectors (direction & camera)
 * @brief by the the rotation matrix with angle -ROTATE_SPEED
 */
void	rotate_right(t_game *game)
{
	t_player *player = &game->player;
	double old_dir_x;
	double old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(ROTATE_SPEED) - player->dir_y * sin(ROTATE_SPEED);
	player->dir_y = old_dir_x * sin(ROTATE_SPEED) + player->dir_y * cos(ROTATE_SPEED);
	player->plane_x = player->plane_x * cos(ROTATE_SPEED) - player->plane_y * sin(ROTATE_SPEED);
	player->plane_y = old_plane_x * sin(ROTATE_SPEED) + player->plane_y * cos(ROTATE_SPEED);
}