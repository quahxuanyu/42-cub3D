/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:31:14 by xquah             #+#    #+#             */
/*   Updated: 2024/12/20 18:35:29 by hheng            ###   ########.fr       */
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

void init_game(t_game *game, char *map_file)
{
    init_player(&game->player);
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

    game->map = get_map(map_file);
    if (!game->map)
    {
        printf("Error: Failed to get map\n");
        exit(EXIT_FAILURE);
    }

    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}