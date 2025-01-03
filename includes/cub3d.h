/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:17:37 by xquah             #+#    #+#             */
/*   Updated: 2025/01/01 22:01:07 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../minilibx-linux/mlx.h"
#include <../libft/libft.h>
#include <math.h>
#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <limits.h>
#define mapWidth 18
#define mapHeight 10
// RATIO: 4:3
// NOTE: any size of screen and wall size works, as long as player does not spawn outside the walls (it wil seg fault)
#define screenWidth 1280 
#define screenHeight 960
#define WALL_SIZE 63
#define VIEW_STATE 3 //2 for 2D, 3 for 3D

#define TEXTURE_SIZE 64


# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307
# define PLAYER_SPEED 2

#define PI 3.14159265359
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

typedef struct s_rgb
{
    int r;
    int g;
    int b;
} t_rgb;

typedef	struct s_img
{
	void	*img;
	char	*addr;
	int		height;
	int		width;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_map_data
{
    t_img   n_img;
    t_img   s_img;
    t_img   w_img;
    t_img   e_img;
    t_rgb   c_rgb;
    t_rgb   f_rgb;
    char    **map;
    int     width;
    int     height;
} t_map_data;


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
	int			map_height;
	int			endian;
	t_img		tex;
	t_player	player;
	t_map_data  map_data;
	char		**map;
	int			side;
}	t_game;

void			init_player(t_player *player);
int				key_press(int keycode, t_player *player);
int				key_release(int keycode, t_player *player);
void			move_player(t_game *game, t_player *player);
bool			touch(t_game *game, float px, float py);

//player.c
bool 	init_player_position(t_game *game);

//init.c
void			init_game(t_game *game, char *map_file);
char 			**get_map(const char *file);
void 			init_mlx(t_game *game);

//utils.c
void			my_mlx_pixel_put(t_game *game, int x, int y, int color);
void			draw_square(int x, int y, int size, int color, t_game *game);
void 			setup_hooks(t_game *game);

//texture.c
unsigned int	get_pixel_color(t_img *tex, int x, int y);
void			init_texture(t_game *game, char *filename);

//render.c
void			three_d_projection(t_game *game, float ray_x, float ray_y, int x);

//raycast.c
void			raycast(t_game *game);
int 			draw_loop(t_game *game);

/* Parsing */
void check_first_and_last_line(t_game *game, char **temp_map);
void    check_first_and_last_char(t_game *game);
char *trim_from_back(int len, char *temp_map);
char **map_trim_spaces_newline_from_the_back(char **temp_map);
void map_checking(t_game *game, char **temp_map);
void    check_only_one_player(t_game *game);
char    **get_map_trim_newline(t_game *game, char **temp_map);
void	check_empty_lines(char **temp_map);
void    pad_map_with_spaces(t_game *game, char **temp_map);
void	check_middle_map_line(t_game *game);
int	check_correct_order(char *str, int check);
int	get_first_line(char **temp_map, int first_line);
int	get_last_line(char **temp_map, int last_line);
void    check_invalid_character(t_game *game);
void    set_player_angle(t_game *game, char direction);
void    malloc_map(t_game *game);


int check_input(int ac, char **av);
void	check_for_ones(char *str, int i);
void	check_extra_character(char **split);

char **duplicate_file(const char *file);
int validate_textures(t_game *game);
int go_to_check_file(t_game *game, int ac, char **av);
void print_err_msg(char *msg);
int	ft_count_lines(int fd);
void	ft_freesplit(char **split);

//main.c
void 			init_all(t_game *game, char *map_file, char *texture_file);

#endif 