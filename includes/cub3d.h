/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:17:37 by xquah             #+#    #+#             */
/*   Updated: 2025/01/15 13:43:26 by hheng            ###   ########.fr       */
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
#include <X11/X.h>
#define mapWidth 18
#define mapHeight 10
// RATIO: 4:3
// NOTE: any size of screen and wall size works, as long as player does not spawn outside the walls (it wil seg fault)
#define screenWidth 1280 
#define screenHeight 960
#define WALL_SIZE 63
#define TEXTURE_SIZE 64

#define MOVE_SPEED 0.1
#define ROTATE_SPEED 0.01

#define VERTICAL 0
#define HORIZONTAL 1

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307

#define PI 3.14159265359
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

enum e_direction
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3,
};

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
	t_img	*wall_tex; //array of 4 for the wall textures
	size_t	c_rgb;
	size_t	f_rgb;
    char    **map;
    int     width;
    int     height;
} t_map_data;

typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	// int		moved_x;
	// int		moved_y;
	// int		rotated;
	bool	key_up;
	bool	key_down;
	bool 	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
	float	angle;
}	t_player;

typedef struct s_ray
{
	double	camera_perc;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x; // total x distance
	double	side_dist_y; // total y distance
	double	delta_dist_x; //step x - from one vertical line to the next
	double	delta_dist_y; //step y - from one horizontal line to the next
	int		map_step_x; //step direction (used for map)
	int		map_step_y; //step direction
	int		side;
	double	wall_dist;
	double	wall_x;
}	t_ray;

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
	t_player	player;
	t_ray		ray;
	t_map_data  map_data;
	char		**map;
}	t_game;

void			init_player(t_player *player);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_player *player);
void			move_player(t_game *game, t_player *player);
bool			touch(t_game *game, float px, float py);

//player.c
bool 	init_player_position(t_game *game);

//init.c
void			init_game(t_game *game, char *map_file);
char 			**get_map(const char *file);
void 			init_mlx(t_game *game);

//init_2.c
void init_texture(t_game *game);

//utils.c
void			my_mlx_pixel_put(t_game *game, int x, int y, int color);
void			draw_square(int x, int y, int size, int color, t_game *game);
void 			setup_hooks(t_game *game);

//texture.c
unsigned int	get_pixel_color(t_img *tex, int x, int y);
void			put_wall_texture(t_game *game, int screen_x, int screen_y, int line_height);

//render.c
void			three_d_projection(t_game *game, float ray_x, float ray_y, int x);

//raycast.c
void			raycast(t_game *game);
void   			set_ceiling_floor(t_game *game);
void			clear_image(t_game *game);

//raycast_utils.c
void    init_ray(t_player *player, t_ray *ray, int x);
void    get_initial_dist(t_player *player, t_ray *ray);
void    dda_algo(t_game *game, t_player *player, t_ray *ray);
void    calc_wall_dist(t_ray *ray);
void	draw_line_on_image(t_game *game, t_ray *ray, int x);

//texture.c
void	get_vertical_texture(t_game *game);

//utils.c
void	free_all(t_game *game);

/* Parsing */
// void	check_first_and_last_line(t_game *game, char **temp_map);
// void    check_first_and_last_char(t_game *game);
// char	*trim_from_back(int len, char *temp_map);
// char	**map_trim_spaces_newline_from_the_back(char **temp_map);
// void	map_checking(t_game *game, char **temp_map);
// void    check_only_one_player(t_game *game);
// char    **get_map_trim_newline(t_game *game, char **temp_map);
// void	check_empty_lines(char **temp_map);
// void    pad_map_with_spaces(t_game *game, char **temp_map);
// void	check_middle_map_line(t_game *game);
// int		check_correct_order(char *str, int check);
// int		get_first_line(char **temp_map, int first_line);
// int		get_last_line(char **temp_map, int last_line);
// void    check_invalid_character(t_game *game);
// void    set_player_angle(t_game *game, char direction);
// void    malloc_map(t_game *game);


// int		check_input(int ac, char **av);
// void	check_for_ones(char *str, int i);
// void	check_extra_character(char **split);

// char	**duplicate_file(const char *file);
// int		validate_textures(t_game *game);
// int		go_to_check_file(t_game *game, int ac, char **av);
// void	print_err_msg(char *msg);
// int		ft_count_lines(int fd);
// void	ft_freesplit(char **split);

// int check_texture_format(t_game *game);

/*Validate*/
int check_input(int ac, char **av);
char **duplicate_file(const char *file);
bool has_direction(char **map, int map_height);
void check_map_validity(char **file_lines, int line_count);
int go_to_check_file(t_game *game, int ac, char **av);





//main.c
void 	init_all(t_game *game, char *map_file, char *texture_file);
int		draw_loop(t_game *game);

//movement.c
void	move_up(t_game *game);
void	move_down(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);

//rotate.c
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);

#endif