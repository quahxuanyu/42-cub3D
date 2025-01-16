/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 05:59:45 by hheng             #+#    #+#             */
/*   Updated: 2025/01/16 12:27:59 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int get_temp_file_size(char *file_path, t_game *game)
{
    printf("Debug: Getting temp file size\n");
    int fd;
    char *line;
    
    game->temp_rows = 0;
    fd = open(file_path, O_RDONLY);
    if (fd == -1)
        return (FAILURE);
    while ((line = get_next_line(fd)))
    {
        game->temp_rows++;
        free(line);
    }
    close(fd);
    return (SUCCESS);
}

int create_temp_map(char *file_path, t_game *game)
{
    int fd;
    char *line;
    int i;
 printf("Debug: Creating temp map\n");
    game->temp_map = malloc(sizeof(char *) * (game->temp_rows + 1));
    if (!game->temp_map)
        return (FAILURE);
    fd = open(file_path, O_RDONLY);
    if (fd == -1)
        return (free(game->temp_map), FAILURE);
    i = 0;
    while ((line = get_next_line(fd)) && i < game->temp_rows)
    {
        game->temp_map[i] = ft_strdup(line);
        if (!game->temp_map[i])
        {
            free_partial_temp(game, i);
            free(line);
            close(fd);
            return (FAILURE);
        }
        free(line);
        i++;
    }
    game->temp_map[i] = NULL;
    close(fd);
    printf("Debug: Temp map created\n");
    return (SUCCESS);
}

int parse_temp_map(t_game *game)
{
    printf("Debug: Parsing temp map\n");
    if (get_map_dimensions(game) == FAILURE)
        return (FAILURE);
    if (allocate_final_map(game) == FAILURE)
        return (FAILURE);
    if (copy_map_from_temp(game) == FAILURE)
    {
        free_map_data(game);
        return (FAILURE);
    }
    free_temp_map(game);
    printf("Debug: Temp map parsed\n");
    return (SUCCESS);
}

void free_temp_map(t_game *game)
{
    int i;
    printf("Debug: Freeing temp map\n");
    if (!game || !game->temp_map)
        return;
    i = 0;
    while (game->temp_map[i])
    {
        free(game->temp_map[i]);
        i++;
    }
    free(game->temp_map);
    game->temp_map = NULL;
}

void free_partial_temp(t_game *game, int current_row)
{
    int i;
    printf("Debug: Freeing partial temp map\n");
    i = 0;
    while (i < current_row)
    {
        free(game->temp_map[i]);
        i++;
    }
    free(game->temp_map);
}

void free_map_data(t_game *game)
{
    int i;
printf("Debug: Freeing map data\n");
    if (!game || !game->map_data.map)
        return;
    i = 0;
    while (i < game->map_data.height)
    {
        free(game->map_data.map[i]);
        i++;
    }
    free(game->map_data.map);
    game->map_data.map = NULL;
}


