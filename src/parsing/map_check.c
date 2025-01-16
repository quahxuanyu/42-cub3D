/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 21:29:38 by hheng             #+#    #+#             */
/*   Updated: 2025/01/16 23:20:06 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
* Main function to perform all map validation checks
* Verifies map size, walls, player position, and valid characters
* Returns SUCCESS if all checks pass, FAILURE otherwise
*/
int map_checking(t_game *game)
{
    if (game->map_data.height < 3)
        return (print_err_msg("Map must have at least 3 rows"), FAILURE);
        
    if (!validate_map_walls(game))
        return (print_err_msg("Map must be enclosed by walls"), FAILURE);
    
    if (!validate_player_start(game))
        return (print_err_msg("Map must have exactly one player"), FAILURE);
    
    if (!validate_map_chars(game))
        return (print_err_msg("Map contains invalid characters"), FAILURE);
    
    convert_spaces_to_walls(game);
    return (SUCCESS);
}

/*
* Validates that the map is properly enclosed by walls
* Checks first row, last row, and edges of each row
* Returns SUCCESS if map is properly enclosed, FAILURE otherwise
*/
int validate_map_walls(t_game *game)
{
    char **map;
    int map_start;
    int i;

    map_start = find_map_start(game->map_data.map, game->map_data.height);
    if (map_start == -1)
        return (FAILURE);

    map = &(game->map_data.map[map_start]);
    int height = game->map_data.height - map_start;

    i = 0;
    while (map[0][i])
    {
        if (map[0][i] != '1' && map[0][i] != ' ' && map[0][i] != '\n')
            return (FAILURE);
        i++;
    }

    i = 0;
    while (map[height - 1][i])
    {
        if (map[height - 1][i] != '1' && map[height - 1][i] != ' ' && map[height - 1][i] != '\n')
            return (FAILURE);
        i++;
    }

    for (i = 0; i < height; i++)
    {
        int len = 0;
        int first = -1;
        int last = -1;

        while (map[i][len] && map[i][len] != '\n')
        {
            if (first == -1 && map[i][len] != ' ')
                first = len;
            if (map[i][len] != ' ')
                last = len;
            len++;
        }

        if (first != -1 && (map[i][first] != '1' || map[i][last] != '1'))
            return (FAILURE);
    }

    return (SUCCESS);
}

/*
* Finds the starting line of the actual map content
* Skips empty lines and configuration lines
* Returns the line number where map starts, or -1 if not found
*/
int find_map_start(char **map, int height)
{
    int i;
    
    i = 0;
    while (i < height)
    {
        if (map[i] && ft_strlen(map[i]) > 0 && is_map_line(map[i]))
            return (i);
        i++;
    }
    return (-1);
}

/*
* Determines if a line contains valid map content
* Checks for valid map characters and excludes texture/color configuration lines
* Returns 1 if line is valid map content, 0 otherwise
*/
int is_map_line(char *line)
{
    int i = 0;
    int has_valid_char = 0;
    
    if (!line || !*line)
        return (0);

    while (line[i] && line[i] == ' ')
        i++;

    if ((line[i] == 'N' && line[i + 1] == 'O') ||
        (line[i] == 'S' && line[i + 1] == 'O') ||
        (line[i] == 'W' && line[i + 1] == 'E') ||
        (line[i] == 'E' && line[i + 1] == 'A') ||
        line[i] == 'F' || line[i] == 'C')
        return (0);

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

/*
* Performs flood fill check to ensure map is properly enclosed
* Verifies that all non-wall positions are surrounded by valid walls
* Returns SUCCESS if map is properly enclosed, FAILURE otherwise
*/
int flood_fill_check(char **map, int height)
{
    int i = 0;
    int j;

    if (!is_row_valid(map[0]) || !is_row_valid(map[height - 1]))
        return (FAILURE);

    while (i < height)
    {
        j = 0;
        while (map[i][j] && map[i][j] != '\n')
        {
            if (map[i][j] != '1' && map[i][j] != ' ')
            {
                if (!is_surrounded_by_walls(map, i, j, height))
                    return (FAILURE);
            }
            j++;
        }
        i++;
    }
    return (SUCCESS);
}

/*
* Validates if a row contains proper wall structure
* Checks if the row has at least one wall and only valid characters
* Returns 1 if row is valid, 0 otherwise
*/
int is_row_valid(char *row)
{
    int i = 0;
    int found_wall = 0;

    while (row[i] && row[i] == ' ')
        i++;

    while (row[i] && row[i] != '\n')
    {
        if (row[i] == '1')
            found_wall = 1;
        else if (row[i] != ' ')
            return (0);
        i++;
    }

    return found_wall;
}

/*
* Checks if a position is surrounded by walls
* Verifies all adjacent positions are valid walls
* Returns 1 if position is properly surrounded, 0 otherwise
*/
int is_surrounded_by_walls(char **map, int row, int col, int height)
{
    if (row == 0 || row == height - 1)
        return (0);
        
    int curr_len = 0;
    while (map[row][curr_len] && map[row][curr_len] != '\n')
        curr_len++;
        
    int prev_len = 0;
    while (map[row-1][prev_len] && map[row-1][prev_len] != '\n')
        prev_len++;
        
    int next_len = 0;
    while (map[row+1][next_len] && map[row+1][next_len] != '\n')
        next_len++;

    if (col == 0 || col >= curr_len - 1)
        return (0);

    if (col >= prev_len || col >= next_len)
        return (0);

    char up = map[row-1][col];
    char down = map[row+1][col];
    char left = map[row][col-1];
    char right = map[row][col+1];

    return (up == '1' && down == '1' && left == '1' && right == '1');
}

/*
* Validates if a position in the map is valid
* Checks boundaries and adjacent spaces
* Returns 1 if position is valid, 0 otherwise
*/
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

/*
* Validates player starting position in the map
* Ensures exactly one player exists and sets their initial position
* Returns SUCCESS if exactly one player found, FAILURE otherwise
*/
int validate_player_start(t_game *game)
{
    int i;
    int j;
    int player_count = 0;
    int map_start;
    
    map_start = find_map_start(game->map_data.map, game->map_data.height);
    if (map_start == -1)
        return (FAILURE);

    i = map_start;
    while (i < game->map_data.height)
    {
        j = 0;
        while (game->map_data.map[i][j])
        {
            if (is_player_char(game->map_data.map[i][j]))
            {
                player_count++;
                if (player_count == 1)
                {
                    game->player.pos_x = (double)j + 0.5;
                    game->player.pos_y = (double)(i - map_start) + 0.5;
                    game->player.dir = game->map_data.map[i][j];
                }
            }
            j++;
        }
        i++;
    }

    return (player_count == 1) ? SUCCESS : FAILURE;
}

/*
* Checks if a character is a valid player direction character
* Returns 1 if character is N, S, E, or W, 0 otherwise
*/
int is_player_char(char c)
{
    return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/*
* Converts all space characters in the map to wall characters
* Modifies the map in place
*/
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

/*
* Validates that all characters in the map are valid map characters
* Checks for walls, spaces, and player characters
* Returns SUCCESS if all characters are valid, FAILURE otherwise
*/
int validate_map_chars(t_game *game)
{
    int i;
    int j;
    int map_start;
    
    map_start = find_map_start(game->map_data.map, game->map_data.height);
    if (map_start == -1)
        return (FAILURE);

    i = map_start;
    while (i < game->map_data.height)
    {
        j = 0;
        while (game->map_data.map[i][j])
        {
            if (!is_valid_map_char(game->map_data.map[i][j]) && 
                game->map_data.map[i][j] != '\n' &&
                game->map_data.map[i][j] != ' ')
            {
                return (FAILURE);
            }
            j++;
        }
        i++;
    }
    return (SUCCESS);
}

/*
* Checks if a character is a valid map character
* Returns 1 if character is a wall, space, or player direction, 0 otherwise
*/
int is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || 
            c == 'N' || c == 'S' || c == 'E' || c == 'W');
}