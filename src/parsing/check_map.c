/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:50:52 by hheng             #+#    #+#             */
/*   Updated: 2025/01/01 22:41:25 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Map validation functions for game map processing */

void check_first_and_last_line(t_game *game, char **temp_map)
{
    int i;
    int last_line;

    if (!game || !temp_map)
        print_err_msg("Invalid pointer in check_first_and_last_line");

    last_line = game->map_data.height - 1;
    
    // Check first line
    i = 0;
    while (temp_map[0][i] != '\0')
    {
        if (!ft_strchr("1 \n", temp_map[0][i]))
            print_err_msg("Map not surrounded by walls - first line");
        i++;
    }

    // Check last line
    i = 0;
    while (temp_map[last_line][i] != '\0')
    {
        if (!ft_strchr("1 \n", temp_map[last_line][i]))
            print_err_msg("Map not surrounded by walls - last line");
        i++;
    }
}

char *trim_from_back(int len, char *temp_map)
{
    char    *after_trim;
    int     i;

    if (!temp_map || len < 0)
        return (NULL);

    after_trim = malloc(sizeof(char) * (len + 2));
    if (!after_trim)
        return (NULL);

    i = 0;
    while (i <= len)
    {
        after_trim[i] = temp_map[i];
        i++;
    }
    after_trim[i] = '\0';
    free(temp_map);
    return (after_trim);
}

char **map_trim_spaces_newline_from_the_back(char **temp_map)
{
    int     i;
    int     len;
    char    *trimmed;

    if (!temp_map)
        return (NULL);

    i = 0;
    while (temp_map[i])
    {
        len = ft_strlen(temp_map[i]) - 1;
        while (len > 0)
        {
            if (!ft_strchr(" \n", temp_map[i][len]))
            {
                trimmed = trim_from_back(len, temp_map[i]);
                if (!trimmed)
                    print_err_msg("Memory allocation failed during trim");
                temp_map[i] = trimmed;
                break;
            }
            len--;
        }
        i++;
    }
    return (temp_map);
}

void map_checking(t_game *game, char **temp_map)
{
    if (!game || !temp_map)
        print_err_msg("Invalid pointer in map_checking");

    // Store initial map dimensions
    game->map_data.height = 0;
    while (temp_map[game->map_data.height])
        game->map_data.height++;
    printf("Debug entering map checking function ");
    check_invalid_character(game);
    temp_map = get_map_trim_newline(game, temp_map);
    check_only_one_player(game);
    check_empty_lines(temp_map);
    
    temp_map = map_trim_spaces_newline_from_the_back(temp_map);
    if (!temp_map)
        print_err_msg("Map processing failed");

    // Update map dimensions after processing
    game->map_data.width = ft_strlen(temp_map[0]);
    check_first_and_last_line(game, temp_map);
    check_first_and_last_char(game);
    pad_map_with_spaces(game, temp_map);
    check_middle_map_line(game);

    // Store processed map
    game->map = temp_map;
}

// /* Main function for map checking 	*/
// /* Rules:   						*/
// /*   doesnt allow for tabs in the map */
// /*	 doesnt allow duplicate textures	*/
// /*	 rgb must in the format of 23,23,23 (no spaces in between) */
// void	map_checking(t_vars *vars, char **temp_map)
// {
// 	check_invalid_character(temp_map, vars);
// 	temp_map = get_map_trim_newline(vars, temp_map);
// 	check_only_one_player(temp_map);
// 	check_empty_lines(temp_map);
// 	temp_map = map_trim_spaces_newline_from_the_back(temp_map);
// 	store_map_size_x(vars, temp_map);
// 	check_first_and_last_line(vars, temp_map);
// 	check_first_and_last_char(temp_map);
// 	pad_map_with_spaces(vars, temp_map);
// 	check_middle_map_line(vars);
// }

