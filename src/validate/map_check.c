/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 21:29:38 by hheng             #+#    #+#             */
/*   Updated: 2025/01/16 22:58:19 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int map_checking(t_game *game)
{
	printf("Debug: Checking map\n");
    if (game->map_data.height < 3)
        return (print_err_msg("Map must have at least 3 rows"), FAILURE);
    
    // if (!is_map_valid_size(game))
    //     return (print_error("Invalid map dimensions"), FAILURE);
        
    if (!validate_map_walls(game))
        return (print_err_msg("Map must be enclosed by walls"), FAILURE);
    
	printf("Debug: Map is surrounded by wall\n");
    if (!validate_player_start(game))
        return (print_err_msg("Map must have exactly one player"), FAILURE);
    
	printf("Debug: Player checked\n");   
    if (!validate_map_chars(game))
        return (print_err_msg("Map contains invalid characters"), FAILURE);
    printf("Debug: Map contains valid characters\n");    
    convert_spaces_to_walls(game);
    return (SUCCESS);
}

int validate_map_walls(t_game *game)
{
    printf("Debug: Validating map walls\n");
    char **map;
    int map_start;
    int i;

    // Find where the actual map starts
    map_start = find_map_start(game->map_data.map, game->map_data.height);
    if (map_start == -1)
        return (FAILURE);

    map = &(game->map_data.map[map_start]);
    int height = game->map_data.height - map_start;

    // Check first row
    i = 0;
    while (map[0][i])
    {
        if (map[0][i] != '1' && map[0][i] != ' ' && map[0][i] != '\n')
            return (FAILURE);
        i++;
    }

    // Check last row
    i = 0;
    while (map[height - 1][i])
    {
        if (map[height - 1][i] != '1' && map[height - 1][i] != ' ' && map[height - 1][i] != '\n')
            return (FAILURE);
        i++;
    }

    // Check first and last character of each row
    for (i = 0; i < height; i++)
    {
        int len = 0;
        int first = -1;
        int last = -1;

        // Find first non-space character
        while (map[i][len] && map[i][len] != '\n')
        {
            if (first == -1 && map[i][len] != ' ')
                first = len;
            if (map[i][len] != ' ')
                last = len;
            len++;
        }

        // Check if first and last characters are walls
        if (first != -1 && (map[i][first] != '1' || map[i][last] != '1'))
            return (FAILURE);
    }

    return (SUCCESS);
}

int find_map_start(char **map, int height)
{
    int i;
    int first_map_line = -1;
    
    printf("Debug: Finding map start\n");

    i = 0;
    while (i < height)
    {
        printf("Debug: Checking line %d: %s\n", i, map[i]);
        
        // Skip empty lines and configuration lines
        if (map[i] && ft_strlen(map[i]) > 0 && is_map_line(map[i]))
        {
            printf("Debug: Found map at line %d\n", i);
            return (i);
        }
        i++;
    }

    printf("Error: Map start not found\n");
    return (-1);
}

int is_map_line(char *line)
{
    int i = 0;
    int has_valid_char = 0;
    
    if (!line || !*line)
        return (0);

    // Skip leading spaces
    while (line[i] && line[i] == ' ')
        i++;

    // Check if this is a texture or color configuration line
    if ((line[i] == 'N' && line[i + 1] == 'O') ||
        (line[i] == 'S' && line[i + 1] == 'O') ||
        (line[i] == 'W' && line[i + 1] == 'E') ||
        (line[i] == 'E' && line[i + 1] == 'A') ||
        line[i] == 'F' || line[i] == 'C')
        return (0);

    // Check if line contains valid map characters
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && 
            !is_player_char(line[i]) && line[i] != '\n')
            return (0);
        if (line[i] == '1' || line[i] == '0' || is_player_char(line[i]))
            has_valid_char = 1;
        i++;
    }
    
    return has_valid_char;
}

int flood_fill_check(char **map, int height)
{
    printf("Debug: Entering flood fill check\n");
    int i = 0;
    int j;

    // Check top and bottom rows
    printf("Debug: Checking top row: %s\n", map[0]);
    printf("Debug: Checking bottom row: %s\n", map[height - 1]);

    // First, check if top and bottom rows are valid walls
    if (!is_row_valid(map[0])) {
        printf("Error: Top row is invalid\n");
        return (FAILURE);
    }
    if (!is_row_valid(map[height - 1])) {
        printf("Error: Bottom row is invalid\n");
        return (FAILURE);
    }

    // Then check all positions within the map
    while (i < height)
    {
        j = 0;
        while (map[i][j] && map[i][j] != '\n')  // Stop at newline
        {
            // Only check non-wall positions
            if (map[i][j] != '1' && map[i][j] != ' ')
            {
                printf("Debug: Checking position (%d, %d) with value '%c'\n", i, j, map[i][j]);
                if (!is_surrounded_by_walls(map, i, j, height)) {
                    printf("Error: Position (%d, %d) with value '%c' is not surrounded by walls\n", i, j, map[i][j]);
                    return (FAILURE);
                }
            }
            j++;
        }
        i++;
    }

    printf("Debug: Flood fill check passed\n");
    return (SUCCESS);
}
int is_row_valid(char *row)
{
    int i = 0;
    int found_wall = 0;

    // Skip leading spaces
    while (row[i] && row[i] == ' ')
        i++;

    // Check each character until newline
    while (row[i] && row[i] != '\n')
    {
        if (row[i] == '1')
            found_wall = 1;
        else if (row[i] != ' ')  // Allow only spaces besides walls
            return (0);
        i++;
    }

    return found_wall;  // Return 1 only if we found at least one wall
}

int is_surrounded_by_walls(char **map, int row, int col, int height)
{
    // Check if position is at map edges
    if (row == 0 || row == height - 1)
        return (0);
        
    // Get length of current line (excluding newline)
    int curr_len = 0;
    while (map[row][curr_len] && map[row][curr_len] != '\n')
        curr_len++;
        
    int prev_len = 0;
    while (map[row-1][prev_len] && map[row-1][prev_len] != '\n')
        prev_len++;
        
    int next_len = 0;
    while (map[row+1][next_len] && map[row+1][next_len] != '\n')
        next_len++;

    // Check if position is too close to row edges
    if (col == 0 || col >= curr_len - 1)
        return (0);

    // Check if adjacent positions exist and are valid
    if (col >= prev_len || col >= next_len)
        return (0);

    // Check surrounding positions (only wall '1' is acceptable)
    char up = map[row-1][col];
    char down = map[row+1][col];
    char left = map[row][col-1];
    char right = map[row][col+1];

    return (up == '1' && down == '1' && left == '1' && right == '1');
}


int is_position_valid(char **map, int row, int col, int height)
{
    if (row == 0 || row == height - 1)
        return (0);
    if (!map[row][col + 1] || !map[row][col - 1])
        return (0);
    if (map[row][col] == ' ' || map[row - 1][col] == ' ' || 
        map[row + 1][col] == ' ' || map[row][col - 1] == ' ' || 
        map[row][col + 1] == ' ')
        return (0);
    return (1);
}

int validate_player_start(t_game *game)
{
    int i;
    int j;
    int player_count = 0;
    int map_start;

    printf("Debug: Validating player start position\n");
    
    map_start = find_map_start(game->map_data.map, game->map_data.height);
    if (map_start == -1) {
        printf("Error: Failed to find map start\n");
        return (FAILURE);
    }
    printf("Debug: Map starts at line %d\n", map_start);

    i = map_start;
    while (i < game->map_data.height)
    {
        j = 0;
        while (game->map_data.map[i][j])
        {
            if (is_player_char(game->map_data.map[i][j]))
            {
                player_count++;
                printf("Debug: Found player at (%d, %d) facing %c\n", 
                       i, j, game->map_data.map[i][j]);
                
                if (player_count == 1)
                {
                    game->player.pos_x = (double)j + 0.5;
                    game->player.pos_y = (double)(i - map_start) + 0.5;  // Adjust for map start offset
                    game->player.dir = game->map_data.map[i][j];
                    printf("Debug: Player position set to (%f, %f) facing %c\n", 
                           game->player.pos_x, game->player.pos_y, game->player.dir);
                }
            }
            j++;
        }
        i++;
    }

    return (player_count == 1) ? SUCCESS : FAILURE;
}

int is_player_char(char c)
{
    return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void convert_spaces_to_walls(t_game *game)
{
    int i = 0;
    int j;
    
    while (i < game->map_data.height)
    {
        j = 0;
        while (game->map_data.map[i][j])
        {
            if (game->map_data.map[i][j] == ' ')
                game->map_data.map[i][j] = '1';
            j++;
        }
        i++;
    }
}

int validate_map_chars(t_game *game)
{
    int i;
    int j;
    int map_start;

    printf("Debug: Validating map characters\n");
    
    // Find where the actual map starts
    map_start = find_map_start(game->map_data.map, game->map_data.height);
    if (map_start == -1)
        return (FAILURE);

    i = map_start;  // Start from where the map begins
    while (i < game->map_data.height)
    {
        j = 0;
        while (game->map_data.map[i][j])
        {
            printf("Debug: Checking character at (%d, %d): '%c'\n", i, j, game->map_data.map[i][j]);
            if (!is_valid_map_char(game->map_data.map[i][j]) && 
                game->map_data.map[i][j] != '\n' &&
                game->map_data.map[i][j] != ' ')
            {
                printf("Error: Invalid character at (%d, %d): '%c'\n", i, j, game->map_data.map[i][j]);
                return (FAILURE);
            }
            j++;
        }
        i++;
    }

    printf("Debug: All map characters are valid\n");
    return (SUCCESS);
}

int is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || 
            c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

// int is_map_valid_size(t_game *game)
// {
//     int i = 0;
    
//     while (i < game->map_data.height)
//     {
//         if (strlen(game->map_data.map[i]) < 3)
//             return (FAILURE);
//         i++;
//     }
//     return (SUCCESS);
// }