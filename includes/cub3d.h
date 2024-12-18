/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:17:37 by xquah             #+#    #+#             */
/*   Updated: 2024/12/18 21:17:31 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#define mapWidth 18
#define mapHeight 10
// RATIO: 4:3
// NOTE: any size of screen and wall size works, as long as player does not spawn outsied the walls (it wil seg fault)
#define screenWidth 1280 
#define screenHeight 960
#define WALL_SIZE 63
#define VIEW_STATE 3 //2 for 2D, 3 for 3D

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define PLAYER_SPEED 2

#define PI 3.14159265359

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	
	bool	key_up;
	bool	key_down;
	bool 	key_left;
	bool	key_right;
	
	bool	left_rotate;
	bool	right_rotate;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	
	char		*data;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_player	player;
	
	char		**map;
}	t_game;

void	init_player(t_player *player);
int		key_press(int keycode, t_player *player);
int		key_release(int keycode, t_player *player);
void	move_player(t_game *game, t_player *player);
bool	touch(t_game *game, float px, float py);

/* Parsing */
int	check_input (int ac, char **av);
static int count_lines(const char *filename);
char **read_map_from_file(const char *filename);
#endif