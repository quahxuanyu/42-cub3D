/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:31:14 by xquah             #+#    #+#             */
/*   Updated: 2025/01/12 14:43:09 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char    **get_map(const char *file)
{
    char    **map;
    int     fd;
    char    *line;
    size_t  i;

    fd = open(file , O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening map file");
        return NULL;
    }
    map = malloc(sizeof(char *) * 11); // Allocate space for 11 rows + 1 for NULL termination
    if (!map)
    {
        perror("Error allocating memory for map");
        close(fd);
        return NULL;
    }
    i = 0;
    while (i < 10 && (line = get_next_line(fd)) != NULL)
    {
         if (!line)
        {
            printf("Error: get_next_line returned NULL\n");
            break;
        }
        map[i] = line;
        i++;
    }
    map[i] = NULL; // Null terminate the map
    close(fd);
    return map;
}

/**
 * @brief Initialize the MLX window, image, and data address
 */
void    init_mlx(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        printf("Error: Failed to initialize mlx\n");
        exit(EXIT_FAILURE);
    }
    game->win = mlx_new_window(game->mlx, screenWidth, screenHeight, "Raycast Test");
    if (!game->win)
    {
        printf("Error: Failed to create window\n");
        exit(EXIT_FAILURE);
    }
    game->img = mlx_new_image(game->mlx, screenWidth, screenHeight);
    if (!game->img)
    {
        printf("Error: Failed to create image\n");
        exit(EXIT_FAILURE);
    }
    game->data = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->line_length, &game->endian);
    if (!game->data)
    {
        printf("Error: Failed to get data address\n");
        exit(EXIT_FAILURE);
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

/***
 * @brief Load the texture from the .xpm file to an image
 * @param game the game structure
 * @param img the image to store the loaded texture
 * @param filename the filename of the .xpm texture
 */
void	load_texture(t_game *game, t_img *img, char *filename)
{
    int		fd;
    int		bits_per_pixel;
    int		line_length;
    int		endian;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        printf("Error\nTexture file not found\n");
        exit(1);
    }
	img->width = 64; //currently hardcoding the texture size
    img->width = 64; //currently hardcoding the texture size
    img->img = mlx_xpm_file_to_image(game->mlx, filename, &img->width, &img->height);
    if (!img->img)
    {
        printf("Error\nFailed to load texture\n");
        exit(1);
    }
    img->addr = mlx_get_data_addr(img->img, &bits_per_pixel, &line_length, &endian);
    img->bits_per_pixel = bits_per_pixel;
    img->line_length = line_length;
    img->endian = endian;
}

/***
 * @brief Initialize texutures from the map file
 * @note Currently hardcoding the wall textures, ceiling and floor colors
 * @note Changed from individual variables to array of t_img for wall textures (wall_tex[])
 * @note Ceiling and Floor colors changed from RGB struct to size_t
 */
void init_texture(t_game *game)
{
    game->map_data.wall_tex = (t_img *)malloc(sizeof(t_img) * 4); //remember to FREE
    load_texture(game, &game->map_data.wall_tex[NORTH], "textures/wood.xpm");
    load_texture(game, &game->map_data.wall_tex[SOUTH], "textures/redbrick.xpm");
    load_texture(game, &game->map_data.wall_tex[EAST], "textures/purplestone.xpm");
    load_texture(game, &game->map_data.wall_tex[WEST], "textures/mossy.xpm");
    game->map_data.c_rgb = 0x0000FF; //Temp Color - changed from RBG struct to just size_t
    game->map_data.f_rgb = 0xFFFFFF; //Temp Color - changed from RBG struct to just size_t
}
