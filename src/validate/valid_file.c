/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:38:20 by hheng             #+#    #+#             */
/*   Updated: 2025/01/16 16:56:27 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool valid_input(int ac, char *filepath)
{
    if (ac != 2)
    {
        printf("Error: Invalid number of arguments!\n");
        return false;
    }
    
    char *ext = strrchr(filepath, '.');
    if (!ext || ft_strcmp(ext, ".cub") != 0)
    {
        printf("Error: Invalid file extension! Expected .cub file.\n");
        return false;
    }
    printf("Debug: Input is valid\n");
    return true;
}


int valid_file(char *file_path, t_game *game)
{
    if (!file_path || !game)
        return (FAILURE);
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
    printf("Debug: Validating texture\n");
    if (!game || !game->mlx || !file_path)
    {
        printf("Error: Invalid parameters\n");
        return (FALSE);
    }
    if (!game->map_data.wall_tex)
    {
        printf("Error: Texture array not allocated\n");
        return (FALSE);
    }
    if (!parse_directions(game, file_path))
    {
        printf("Error: Failed to parse textures\n");
        return (FALSE);
    }
    if (!validate_loaded_textures(game))
        return (FALSE);
    if (!check_rgb_colors(&game->map_data))
        return (FALSE);
    return (TRUE);
}


// int valid_map(t_game *game)
// {
//     if (!game->map_data.map)
//         return (FALSE);

//     if (check_map_borders(game->map_data.map) == FAILURE)
//         return (FALSE);

//     if (validate_map_characters(game->map_data.map) == FAILURE)
//         return (FALSE);

//     return (TRUE);
// }


int go_to_check_file(char *file_path, t_game *game)
{
    if (!file_path || !game)
        return (print_err_msg("NULL pointer provided"), FAILURE);
        
    if (!valid_input(2, file_path))
        return (print_err_msg("Invalid input"), FAILURE);

    if (!valid_file(file_path, game))
        return (print_err_msg("Invalid file"), FAILURE);
    

    if (!valid_texture(game, file_path))
        return (print_err_msg("Invalid texture"), FAILURE);

    return (SUCCESS);
}
