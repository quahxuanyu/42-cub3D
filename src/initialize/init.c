/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:31:14 by xquah             #+#    #+#             */
/*   Updated: 2025/01/02 15:48:06 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char **get_map(const char *file)
{
    char **map;
    int fd;
    char *line;
    size_t i;

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

void init_mlx(t_game *game)
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

//NOT WORKING
void	init_texture(t_game *game, char *filename)
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
	game->tex.width = 64;
	game->tex.width = 64;
	game->tex.img = mlx_xpm_file_to_image(game->mlx, filename, &game->tex.width, &game->tex.height);
    if (!game->tex.img)
    {
        printf("Error\nFailed to load texture\n");
        exit(1);
    }
    game->tex.addr = mlx_get_data_addr(game->tex.img, &bits_per_pixel, &line_length, &endian);
    game->tex.bits_per_pixel = bits_per_pixel;
    game->tex.line_length = line_length;
    game->tex.endian = endian;
}
