/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:38:20 by hheng             #+#    #+#             */
/*   Updated: 2025/01/15 14:08:39 by hheng            ###   ########.fr       */
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
    
    if (temp_map_size_y <= 0)
    {
        close(fd);
        print_err_msg("Empty or invalid file");
        return (NULL);
    }
    
    temp_map = malloc(sizeof(char *) * (temp_map_size_y + 1));
    if (!temp_map)
    {
        close(fd);
        print_err_msg("Memory allocation failed");
        return (NULL);
    }

    // Initialize all pointers to NULL
    for (int i = 0; i <= temp_map_size_y; i++)
    {
        temp_map[i] = NULL;
    }

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
    while ((line = get_next_line(fd)) != NULL && i < temp_map_size_y)
    {
        if (line[0] != '\0')  // Skip empty lines
        {
            temp_map[i] = line;
            i++;
        }
        else
        {
            free(line);  // Free empty lines
        }
    }
    temp_map[i] = NULL;  // Null terminate the array
    
    close(fd);
    printf("Debug: File successfully read\n");
    return (temp_map);
}

bool has_direction(char **map, int map_height)
{
    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0; map[i][j]; j++)
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' ||
                map[i][j] == 'E' || map[i][j] == 'W')
            {
                return true;
            }
        }
    }
    return false;
}

void check_map_validity(char **file_lines, int line_count)
{
    bool has_no = false, has_so = false, has_we = false, has_ea = false;
    bool has_ceiling = false, has_floor = false;
    bool map_started = false;
    int map_start_index = 0;

    printf("\nDebug: Starting map validation. Line count: %d\n", line_count);

    if (!file_lines)
    {
        printf("Debug: ERROR - File lines are NULL\n");
        print_err_msg("File lines are NULL");
        return;
    }

    // Check for texture and color definitions
    for (int i = 0; i < line_count; i++)
    {
        printf("\nDebug: Checking line %d: ", i);
        
        // Add NULL check for each line
        if (!file_lines[i])
        {
            printf("NULL line\n");
            continue;
        }

        printf("'%s'", file_lines[i]);

        // Skip empty lines
        if (strlen(file_lines[i]) == 0)
        {
            printf(" (empty line)\n");
            continue;
        }

        if (ft_strncmp(file_lines[i], "NO ", 3) == 0)
        {
            has_no = true;
            printf(" -> Found NO texture\n");
        }
        else if (ft_strncmp(file_lines[i], "SO ", 3) == 0)
        {
            has_so = true;
            printf(" -> Found SO texture\n");
        }
        else if (ft_strncmp(file_lines[i], "WE ", 3) == 0)
        {
            has_we = true;
            printf(" -> Found WE texture\n");
        }
        else if (ft_strncmp(file_lines[i], "EA ", 3) == 0)
        {
            has_ea = true;
            printf(" -> Found EA texture\n");
        }
        else if (ft_strncmp(file_lines[i], "C ", 2) == 0)
        {
            has_ceiling = true;
            printf(" -> Found ceiling color\n");
        }
        else if (ft_strncmp(file_lines[i], "F ", 2) == 0)
        {
            has_floor = true;
            printf(" -> Found floor color\n");
        }
        else if (file_lines[i][0] && (isdigit(file_lines[i][0]) || file_lines[i][0] == ' '))
        {
            if (!map_started)
            {
                map_start_index = i;
                map_started = true;
                printf(" -> Map section starts here\n");
            }
            else
            {
                printf(" -> Map content\n");
            }
        }
        else
        {
            printf(" -> Unrecognized content\n");
        }
    }

    printf("\nDebug: Validation Summary:\n");
    printf("NO texture: %s\n", has_no ? "Found" : "Missing");
    printf("SO texture: %s\n", has_so ? "Found" : "Missing");
    printf("WE texture: %s\n", has_we ? "Found" : "Missing");
    printf("EA texture: %s\n", has_ea ? "Found" : "Missing");
    printf("Ceiling color: %s\n", has_ceiling ? "Found" : "Missing");
    printf("Floor color: %s\n", has_floor ? "Found" : "Missing");
    printf("Map section: %s\n", map_started ? "Found" : "Missing");

    if (!has_no || !has_so || !has_we || !has_ea)
    {
        printf("Debug: ERROR - Missing texture definitions\n");
        print_err_msg("Missing one or more texture definitions (NO, SO, WE, EA)");
    }
    if (!has_ceiling || !has_floor)
    {
        printf("Debug: ERROR - Missing color definitions\n");
        print_err_msg("Missing ceiling or floor color definitions (C, F)");
    }
    if (!map_started)
    {
        printf("Debug: ERROR - No map data found\n");
        print_err_msg("Map data is missing");
    }

    if (map_started)
    {
        printf("Debug: Checking map directions from line %d\n", map_start_index);
        if (!has_direction(&file_lines[map_start_index], line_count - map_start_index))
        {
            printf("Debug: ERROR - No valid direction found in map\n");
            print_err_msg("Map must contain at least one starting direction (N, S, E, W)");
        }
    }
}


// Updated main check file function to include texture validation
int go_to_check_file(t_game *game, int ac, char **av)
{
    char **temp_map;
    int fd;

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

    // Get line count properly
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
    {
        free_map(temp_map);
        printf("Debug: Failed to open file for line count\n");
        return (0);
    }
    int line_count = ft_count_lines(fd);
    close(fd);

    // Remove the extra curly braces that were causing immediate return
    check_map_validity(temp_map, line_count);

    printf("Debug: All checks passed successfully\n");
    free_map(temp_map);
    return (1);
}