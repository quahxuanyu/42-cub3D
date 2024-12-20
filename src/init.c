/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:31:14 by xquah             #+#    #+#             */
/*   Updated: 2024/12/20 16:50:47 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char **get_map(void)
{
    char **map;
    int fd;
    char *line;
    size_t i;

    printf("Debug: Opening map file\n");
    fd = open("map/test.cub", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening map file");
        return NULL;
    }
    printf("Debug: Successfully opened map file\n");
    map = malloc(sizeof(char *) * 11); // Allocate space for 11 rows + 1 for NULL termination
    if (!map)
    {
        perror("Error allocating memory for map");
        close(fd);
        return NULL;
    }
    printf("Debug: Successfully allocated memory for map\n");
    i = 0;
    while (i < 10 && (line = get_next_line(fd)) != NULL)
    {
         if (!line)
        {
            printf("Error: get_next_line returned NULL\n");
            break;
        }
        printf("Debug: Read line %zu: %s\n", i, line);
        map[i] = line;
        i++;
    }
    map[i] = NULL; // Null terminate the map

    close(fd);
    printf("Debug: Finished reading map\n");
    return map;
}

void init_game(t_game *game)
{
    printf("Debug: Initializing player\n");
    init_player(&game->player);

    printf("Debug: Initializing mlx\n");
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        printf("Error: Failed to initialize mlx\n");
        exit(EXIT_FAILURE);
    }

    printf("Debug: Creating window\n");
    game->win = mlx_new_window(game->mlx, screenWidth, screenHeight, "Raycast Test");
    if (!game->win)
    {
        printf("Error: Failed to create window\n");
        exit(EXIT_FAILURE);
    }

    printf("Debug: Creating image\n");
    game->img = mlx_new_image(game->mlx, screenWidth, screenHeight);
    if (!game->img)
    {
        printf("Error: Failed to create image\n");
        exit(EXIT_FAILURE);
    }

    printf("Debug: Getting data address\n");
    game->data = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->line_length, &game->endian);
    if (!game->data)
    {
        printf("Error: Failed to get data address\n");
        exit(EXIT_FAILURE);
    }

    printf("Debug: Getting map\n");
    game->map = get_map();
    if (!game->map)
    {
        printf("Error: Failed to get map\n");
        exit(EXIT_FAILURE);
    }

    printf("Debug: Putting image to window\n");
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}