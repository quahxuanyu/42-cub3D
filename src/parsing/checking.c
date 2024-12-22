/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:38:20 by hheng             #+#    #+#             */
/*   Updated: 2024/12/22 16:21:50 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#include "../includes/cub3d.h"

// Helper function to safely free map and return NULL
static char **free_map_and_exit(char **map, size_t count, int fd)
{
    if (map)
    {
        free_map(map, count);
    }
    if (fd != -1)
    {
        close(fd);
    }
    return NULL;
}

// Helper function to safely allocate initial map memory
static char **allocate_initial_map(size_t initial_capacity)
{
    char **map = calloc(initial_capacity + 1, sizeof(char *));
    if (!map)
    {
        perror("Error allocating memory for map");
        return NULL;
    }
    return map;
}

int check_input(int ac, char **av)
{
    printf("Debug: Checking input arguments\n");
    if (ac < 2)
    {
        printf("Error\nNo map file provided\n");
        return (1);
    }
    if (ac > 2)
    {
        printf("Error\nToo many arguments\n");
        return (1);
    }
    size_t len = ft_strlen(av[1]);
    if (len < 4 || ft_strncmp(av[1] + len - 4, ".cub", 4) != 0)
    {
        printf("Error\nInvalid file extension\n");
        return (1);
    }
    return (0);
}

char **duplicate_file(const char *file)
{
    printf("Debug: Duplicating file %s\n", file);
    int fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening map file");
        return NULL;
    }

    size_t capacity = 10;
    char **map = allocate_initial_map(capacity);
    if (!map)
        return free_map_and_exit(NULL, 0, fd);

    char *line;
    size_t i = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Debug: Reading line %zu: %s", i + 1, line);
        
        if (i >= capacity)
        {
            capacity *= 2;
            char **temp = reallocarray(map, capacity + 1, sizeof(char *));
            if (!temp)
            {
                free(line);
                return free_map_and_exit(map, i, fd);
            }
            map = temp;
        }

        // Remove trailing newline if present
        size_t len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

        map[i++] = line;
    }
    
    map[i] = NULL;
    close(fd);
    return map;
}

int is_valid_map_line(const char *line, size_t line_number)
{
    printf("Debug: Validating map line %zu: %s\n", line_number + 1, line);
    if (!line)
        return 0;

    size_t pos = 0;
    while (line[pos])
    {
        // Skip whitespace
        if (ft_isspace(line[pos]))
        {
            pos++;
            continue;
        }

        // Validate map characters
        if (!ft_strchr("01NSEW", line[pos]))
        {
            printf("Error: Invalid character '%c' in map file on line %zu at position %zu\n",
                   line[pos], line_number + 1, pos + 1);
            return 0;
        }
        pos++;
    }
    return 1;
}

int is_metadata_line(const char *line)
{
    if (!line)
        return 0;

    const char *valid_identifiers[] = {"NO ", "SO ", "WE ", "EA ", "F ", "C ", NULL};
    
    for (int i = 0; valid_identifiers[i]; i++)
    {
        if (ft_strncmp(line, valid_identifiers[i], ft_strlen(valid_identifiers[i])) == 0)
        {
            printf("Debug: Found metadata line: %s\n", line);
            return 1;
        }
    }
    return 0;
}

char **check_each_line(char **map)
{
    if (!map)
        return NULL;

    size_t i = 0;
    int found_map_start = 0;

    // Skip metadata and empty lines until first map line
    while (map[i])
    {
        if (map[i][0] == '\0' || is_metadata_line(map[i]))
        {
            i++;
            continue;
        }
        found_map_start = 1;
        break;
    }

    if (!found_map_start)
    {
        printf("Error: No valid map content found\n");
        return NULL;
    }

    // Validate map lines
    for (; map[i]; i++)
    {
        if (map[i][0] == '\0')
        {
            printf("Error: Empty line within map content at line %zu\n", i + 1);
            return NULL;
        }
        if (!is_valid_map_line(map[i], i))
            return NULL;
    }

    return map;
}

int validate_textures(t_game *game, char **file_lines)
{
    if (!game || !file_lines)
        return 0;

    const char *textures[] = {"NO", "SO", "EA", "WE"};
    int texture_found[4] = {0, 0, 0, 0};

    for (size_t i = 0; file_lines[i]; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (ft_strncmp(file_lines[i], textures[j], ft_strlen(textures[j])) == 0)
            {
                if (texture_found[j])
                {
                    printf("Error: Duplicate texture definition for %s\n", textures[j]);
                    return 0;
                }
                printf("Debug: Found texture %s on line %zu\n", textures[j], i + 1);
                texture_found[j] = 1;
            }
        }
    }

    // Check if all textures were found
    for (int j = 0; j < 4; j++)
    {
        if (!texture_found[j])
        {
            printf("Error: Missing texture definition for %s\n", textures[j]);
            return 0;
        }
    }

    return 1;
}

int go_to_check_file(t_game *game, int ac, char **av)
{
    if (!game || check_input(ac, av))
        return 1;

    printf("Debug: Checking and duplicating map file\n");
    game->map = duplicate_file(av[1]);
    if (!game->map)
        return 1;

    // Validate metadata (textures and colors)
    printf("Debug: Validating metadata lines\n");
    if (!validate_textures(game, game->map))
    {
        free_map(game->map, count_lines(game->map));
        return 1;
    }

    // Validate colors
    for (size_t i = 0; game->map[i]; i++)
    {
        if (ft_strncmp(game->map[i], "F ", 2) == 0 || 
            ft_strncmp(game->map[i], "C ", 2) == 0)
        {
            if (!is_valid_color_line(game->map[i]))
            {
                printf("Error: Invalid color definition on line %zu\n", i + 1);
                free_map(game->map, count_lines(game->map));
                return 1;
            }
        }
    }

    printf("Debug: Validating map lines\n");
    if (!check_each_line(game->map))
    {
        free_map(game->map, count_lines(game->map));
        return 1;
    }

    printf("Debug: All checks passed\n");
    return 0;
}