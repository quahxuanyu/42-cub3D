/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:17:01 by hheng             #+#    #+#             */
/*   Updated: 2024/12/18 18:42:56 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char **allocate_map_memory(int max_lines)
{
	char **map = malloc(sizeof(char *) * (max_lines+ 1));
	if (!map)
	{
		printf("Error\nFailed to allocate memory for map\n");
		return (NULL);
	}
	return (map);
}

int is_line_empty(const char *line)
{
    while (*line) {
        if (!ft_isspace((int)*line)) // Cast `char` to `int`
            return 0; // Line contains non-whitespace characters
        line++;
    }
    return 1; // Line is empty or contains only whitespace
}

int process_map_line(char **map, char *line, int line_count)
{
    if (is_line_empty(line)) {
        free(line); // Free blank or whitespace-only lines
        return line_count; // Do not increment line_count
    }
    map[line_count] = line; // Add valid line to the map
    return line_count + 1; // Increment line count
}

char **read_map_from_file(const char *filename)
{
	int fd;
	char *line;
	int line_count;
	int max_line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		{
			printf("Error\nFailed to open file\n");
			return (NULL);
		}
	
	max_line = 100;
	char **map = allocate_map_memory(max_line);
	if (!map)
	{
		close(fd);
		return (NULL);
	}
	
	line_count = 0;
	while((line = get_next_line(fd)) != NULL)
	{
        line_count = process_map_line(map, line, line_count);
        if (line_count >= max_line)
		{
			printf("Error\nMap is too large\n");
			break;
		}
    }
	map[line_count] = NULL; // Null-terminate the map
    close(fd);

    if (line_count == 0) {
        printf("Error\nMap file is empty or invalid\n");
        free(map);
        return NULL;
    }
    return map;
}
