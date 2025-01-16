/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:01:05 by hheng             #+#    #+#             */
/*   Updated: 2025/01/16 17:24:53 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int validate_xpm_format(char *path)
{
    int fd;
printf("Debug: Validating XPM format\n");
    if (!path)
        return (FALSE);
    if (!ft_strnstr(path, ".xpm", ft_strlen(path)))
    {
        printf("Error: File must be .xpm format\n");
        return (FALSE);
    }
    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        printf("Error: Cannot open file\n");
        return (FALSE);
    }
    close(fd);
    return (TRUE);
}

// int load_texture(char *path, t_img *tex, void *mlx)
// {
//     if (!validate_xpm_format(path))
//         return (FALSE);
//     tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
//     if (!tex->img)
//     {
//         printf("Error: Failed to load texture\n");
//         return (FALSE);
//     }
//     tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
//                                  &tex->line_length, &tex->endian);
//     return (tex->addr != NULL);
// }

int process_direction(char *line, t_game *game, int direction)
{
    char *path;
    
    printf("Debug: Processing direction %d\n", direction);
    
    // Skip the direction identifier (NO, SO, WE, EA) and any whitespace
    line += 2;  // Skip NO, SO, WE, or EA
    while (*line && (*line == ' ' || *line == '\t'))
        line++;
        
    // Store the path
    path = ft_strdup(line);  // Make copy of path
    if (!path)
        return (FALSE);
        
    // Remove newline if present
    char *newline = ft_strchr(path, '\n');
    if (newline)
        *newline = '\0';
        
    printf("Debug: Loading texture from path: '%s'\n", path);
    
    // Load the texture
    if (!load_texture(game, &(game->map_data.wall_tex[direction]), path))
    {
        printf("Error: Failed to load texture from %s\n", path);
        free(path);
        return (FALSE);
    }
    
    free(path);
    return (TRUE);
}

int parse_directions(t_game *game, char *file_path)
{
    int fd;
    char *line;
    bool found[4] = {false, false, false, false};  // Initialize array to false
    int line_number = 0;

    if (!game || !file_path) {
        printf("Error: NULL pointer provided to parse_directions\n");
        return (FALSE);
    }

    printf("Debug: Parsing directions\n");
    
    fd = open(file_path, O_RDONLY);
    if (fd < 0) {
        printf("Error: Could not open file %s\n", file_path);
        return (FALSE);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Debug: Processing line %d: %s\n", line_number, line);
        
        // Skip whitespace at start of line
        char *tmp = line;
        while (*tmp == ' ' || *tmp == '\t')
            tmp++;
            
        // Check for directions
        if (ft_strncmp(tmp, "NO", 2) == 0 && !found[NORTH]) {
            printf("Debug: Found NORTH direction\n");
            found[NORTH] = process_direction(tmp, game, NORTH);
        } else if (ft_strncmp(tmp, "SO", 2) == 0 && !found[SOUTH]) {
            printf("Debug: Found SOUTH direction\n");
            found[SOUTH] = process_direction(tmp, game, SOUTH);
        } else if (ft_strncmp(tmp, "WE", 2) == 0 && !found[WEST]) {
            printf("Debug: Found WEST direction\n");
            found[WEST] = process_direction(tmp, game, WEST);
        } else if (ft_strncmp(tmp, "EA", 2) == 0 && !found[EAST]) {
            printf("Debug: Found EAST direction\n");
            found[EAST] = process_direction(tmp, game, EAST);
        }
        
        free(line);  // Don't forget to free the line
        line_number++;
    }
    
    close(fd);  // Close the file descriptor

    printf("Debug: Finished parsing directions\n");
    printf("Debug: Found directions - N:%d S:%d W:%d E:%d\n", 
           found[NORTH], found[SOUTH], found[WEST], found[EAST]);
           
    return (found[NORTH] && found[SOUTH] && found[WEST] && found[EAST]);
}

int validate_rgb(size_t color)
{
    int r;
    int g;
    int b;
printf("Debug: Validating RGB\n");
    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        printf("Error: Invalid RGB values\n");
        return (FALSE);
    }
    return (TRUE);
}

int check_rgb_colors(t_map_data *map_data)
{
	printf("Debug: Checking RGB colors\n");
    if (map_data->f_rgb == 0 || map_data->c_rgb == 0)
    {
        printf("Error: Missing floor or ceiling color\n");
        return (FALSE);
    }
    if (!validate_rgb(map_data->f_rgb) || !validate_rgb(map_data->c_rgb))
        return (FALSE);
    return (TRUE);
}
int validate_loaded_textures(t_game *game)
{
    int i;
    t_img *textures;

    printf("Debug: Validating loaded textures\n");
    if (!game->map_data.wall_tex)
    {
        printf("Error: wall_tex is NULL\n");
        return (FALSE);
    }

    textures = game->map_data.wall_tex;
    for (i = 0; i < 4; i++)
    {
        printf("Debug: Validating texture at direction %d\n", i);
        printf("Debug: img: %p, addr: %p, width: %d, height: %d\n",
               textures[i].img, textures[i].addr, 
               textures[i].width, textures[i].height);
               
        if (!textures[i].img || !textures[i].addr)
        {
            printf("Error: Invalid texture pointers at direction %d\n", i);
            return (FALSE);
        }
        if (textures[i].width <= 0 || textures[i].height <= 0)
        {
            printf("Error: Invalid texture dimensions at direction %d\n", i);
            return (FALSE);
        }
    }
    return (TRUE);
}