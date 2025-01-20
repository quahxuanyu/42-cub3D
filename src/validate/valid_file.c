/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:38:20 by hheng             #+#    #+#             */
/*   Updated: 2025/01/20 13:46:08 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool valid_input(int ac, char *filepath)
bool valid_input(int ac, char *filepath)
{
    if (ac != 2)
    {
        printf("Error: Invalid number of arguments!\n");
        return false;
    }

    if (ft_strcmp(filepath + strlen(filepath) - 4, ".cub") != 0)
    {
        printf("Error: Invalid file extension! Expected .cub file.\n");
        return false;
    }

    printf("Debug: Input is valid\n");
    return true;
}


int valid_file(char *file_path, t_game *game)
{
    if (get_temp_file_size(file_path, game) == FAILURE)
        return (FAILURE);
    if (create_temp_map(file_path, game) == FAILURE)
        return (FAILURE);
    if (parse_temp_map(game) == FAILURE)
    {
        free_temp_map(game);
        return (FAILURE);
    }
    printf("Debug: File is valid\n");
    return (SUCCESS);
    printf("Debug: Done valid file\n");
}

int valid_texture(t_game *game, char *file_path)
{
    if (!game || !game->mlx || !file_path)
        return (FALSE);
    if (!game->map_data.wall_tex)
        return (FALSE);
    if (!parse_directions(game, file_path))
        return (FALSE);
    if (!validate_loaded_textures(game))
        return (FALSE);
    if (!check_rgb_colors(&game->map_data))
        return (FALSE);
    return (TRUE);
}

int go_to_check_file(char *file_path, t_game *game)
{
    if (!file_path || !game)
        return (print_err_msg("Invalid argument"), FAILURE);
        
    if (!valid_input(2, file_path))
        return (print_err_msg("Invalid input"), FAILURE);

    if (!valid_file(file_path, game))
        return (print_err_msg("Invalid file"), FAILURE);
    

    if (!valid_texture(game, file_path))
        return (print_err_msg("Invalid texture"), FAILURE);

    return (SUCCESS);
}
