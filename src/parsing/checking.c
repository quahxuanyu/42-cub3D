/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:38:20 by hheng             #+#    #+#             */
/*   Updated: 2025/01/01 17:23:26 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Check number of arguments, can only be 2
// Check file format, can only be .cub
int check_input(int ac, char **av)
{
    printf("Debug: Checking input arguments\n");
    if (ac != 2)
    {
        print_err_msg("Invalid number of arguments");
        return (0);  // Return 0 for failure
    }
    if (ft_strncmp(&av[1][ft_strlen(av[1]) - 4], ".cub", 4) != 0)
    {
        print_err_msg("Invalid file format");
        return (0);  // Return 0 for failure
    }
    printf("Debug: Input arguments are valid\n");
    return (1);  // Return 1 for success
}

// Open file to check every line
// Then start parsing at [split_file_into_two_parts]
char **duplicate_file(const char *file)
{
    int fd;
    int temp_map_size_y;
    char **temp_map;

    printf("Debug: Opening file: %s\n", file);
    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        print_err_msg("Failed to open file");
        return (NULL);
    }

    temp_map_size_y = ft_count_lines(fd);
    printf("Debug: Map size Y: %d\n", temp_map_size_y);
    
    temp_map = malloc(sizeof(char *) * (temp_map_size_y + 1));
    if (!temp_map)
    {
        close(fd);
        print_err_msg("Memory allocation failed");
        return (NULL);
    }

    // Add file reading logic here
    close(fd);
    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        free(temp_map);
        print_err_msg("Failed to reopen file");
        return (NULL);
    }

    // Read the file
    char *line;
    int i = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        temp_map[i] = line;
        i++;
    }
    temp_map[i] = NULL;  // Null terminate the array
    
    close(fd);
    printf("Debug: File successfully read\n");
    return (temp_map);
}

// // Check whether all textures are valid
// // North, South, West, East, Ceiling and Floor
// int validate_textures(t_game *game)
// {
//     printf("Debug: Validating textures\n");
//     // Check if textures are properly loaded
//     if (game->map_data.n_img.img == NULL || 
//         game->map_data.s_img.img == NULL ||
//         game->map_data.w_img.img == NULL || 
//         game->map_data.e_img.img == NULL)
//     {
//         print_err_msg("North/South/East/West texture not loaded properly");
//         return (0);
//     }
    
//     // Validate ceiling RGB values
//     if (game->map_data.c_rgb.r < 0 || game->map_data.c_rgb.r > 255 ||
//         game->map_data.c_rgb.g < 0 || game->map_data.c_rgb.g > 255 ||
//         game->map_data.c_rgb.b < 0 || game->map_data.c_rgb.b > 255)
//     {
//         print_err_msg("Invalid ceiling RGB values (must be 0-255)");
//         return (0);
//     }

//     // Validate floor RGB values
//     if (game->map_data.f_rgb.r < 0 || game->map_data.f_rgb.r > 255 ||
//         game->map_data.f_rgb.g < 0 || game->map_data.f_rgb.g > 255 ||
//         game->map_data.f_rgb.b < 0 || game->map_data.f_rgb.b > 255)
//     {
//         print_err_msg("Invalid floor RGB values (must be 0-255)");
//         return (0);
//     }

//     printf("Debug: Textures validated successfully\n");
//     return (1);
// }

// Main function to check file
int go_to_check_file(t_game *game, int ac, char **av)
{
    char **temp_map;

    if (!check_input(ac, av))
    {
        printf("Debug: Input check failed\n");
        return (0);
    }
    
    printf("Debug: Duplicating file\n");
    temp_map = duplicate_file(av[1]);
    if (!temp_map)
    {
        printf("Debug: File duplication failed\n");
        return (0);
    }
    printf("Debug: File duplicated successfully\n");

    // if (!validate_textures(game))
    // {
    //     free_map(temp_map);
    //     printf("Debug: Texture validation failed\n");
    //     return (0);
    // }
    // printf("Debug: Textures validated successfully\n");

    // Validate map lines
    // for (int i = 0; game->map_data.map[i]; i++)
    // {
    //     if (ft_strncmp(game->map_data.map[i], "F ", 2) == 0 || 
    //         ft_strncmp(game->map_data.map[i], "C ", 2) == 0)
    //     {
    //         if (!is_valid_color_line(game->map_data.map[i]))
    //         {
    //             free_map(temp_map);
    //             print_err_msg("Invalid color definition");
    //             return (0);
    //         }
    //     }
    // }

    printf("Debug: All checks passed successfully\n");
    return (1);
}