/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 23:40:00 by hheng             #+#    #+#             */
/*   Updated: 2025/01/16 23:53:24 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Creates a copy of the given map (2D array of strings).
 * 
 * Allocates memory for a new map and copies each line from the original map.
 * If an error occurs during allocation or copying, the function frees any
 * allocated memory and returns NULL.
 * 
 * @param original_map The original map to copy.
 * @param height The number of rows in the map.
 * @return A pointer to the newly allocated map or NULL on failure.
 */
char **copy_map(char **original_map, int height)
{
    char **new_map;
    int i;
    
    new_map = (char **)malloc(sizeof(char *) * (height + 1));
    if (!new_map)
        return (NULL);
    
    i = 0;
    while (i < height)
    {
        new_map[i] = ft_strdup(original_map[i]);
        if (!new_map[i])
        {
            free_map(new_map);
            return (NULL);
        }
        i++;
    }
    new_map[height] = NULL;
    return (new_map);
}

/**
 * @brief Frees the memory allocated for a map (2D array of strings).
 * 
 * Iterates through each row in the map, freeing the memory for each string.
 * Frees the memory for the map itself at the end.
 * 
 * @param map The map to be freed. If NULL, the function does nothing.
 */
void free_map(char **map)
{
    int i;
    
    if (!map)
        return;
    
    i = 0;
    while (map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}

/**
 * @brief Prints an error message and terminates the program.
 * 
 * Displays the specified error message, adds an empty line for clarity,
 * and exits the program with a status of 1.
 * 
 * @param msg The error message to display.
 */
void print_err_msg(char *msg)
{
    printf("Error: %s\n", msg);
    printf("\n");
    exit(1);
}
int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}