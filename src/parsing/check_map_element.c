/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_element.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 21:18:36 by hheng             #+#    #+#             */
/*   Updated: 2025/01/01 21:54:30 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Save temp_map into new_temp_map */
/* temp_map 	-> only contains the map content with new lines before */
/* 					and after map content */
/* new_temp_map -> trims the newline before and after the map content  */
/* map struct 	->  is new_temp_map padded with spaces				   */
/* Save the total number of lines to vars->map.size.y */
char    **get_map_trim_newline(t_game *game, char **temp_map)
{
    int        i;
    char    **new_temp_map;
    int        first_line;
    int        last_line;

    first_line = 0;
    last_line = 0;
    first_line = get_first_line(temp_map, first_line);
    last_line = get_last_line(temp_map, last_line);
    game->map_height = last_line - first_line + 1;
    new_temp_map = malloc(sizeof(char *) * (game->map_height + 1));
    if (!new_temp_map)
        print_err_msg("Memory allocation failed");
    
    i = 0;
    while (first_line <= last_line)
    {
        new_temp_map[i] = ft_strdup(temp_map[first_line]);
        if (!new_temp_map[i])
        {
            ft_freesplit(new_temp_map); // Free previously allocated memory
            print_err_msg("Memory allocation failed");
        }
        i++;
        first_line++;
    }
    new_temp_map[i] = NULL;
    ft_freesplit(temp_map);
    
    // Update map width after trimming
    game->map_data.width = 0;
    for (i = 0; new_temp_map[i]; i++)
    {
        int line_len = ft_strlen(new_temp_map[i]);
        if (line_len > game->map_data.width)
            game->map_data.width = line_len;
    }
    
    return (new_temp_map);
}

/* Check if there is empty lines within the map */
/* If there is empty lines, exit the program */
void	check_empty_lines(char **temp_map)
{
	int		i;
	int		len;
	char	*after_trim;

	i = 0;
	while (temp_map[i] != NULL)
	{
		after_trim = ft_strtrim(temp_map[i], " \t\n");
		len = ft_strlen(after_trim);
		free(after_trim);
		if (len == 0)
			print_err_msg("Map contains empty line");
		i++;
	}
}