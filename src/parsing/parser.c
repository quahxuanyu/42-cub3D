/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:17:01 by hheng             #+#    #+#             */
/*   Updated: 2024/12/18 19:21:33 by hheng            ###   ########.fr       */
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
    if (!line)
	{
        printf("Error\nNull pointer passed to is_line_empty\n");
        return 1; // Treat as empty line
    }

    while (*line)
	{
        if (!ft_isspace((unsigned char)*line)) // Cast to `unsigned char`
            return 0; // Line contains non-whitespace characters
        line++;
    }
    return 1; // Line is empty or contains only whitespace
}

int process_map_line(char **map, char *line, int line_count) {
    if (!line) {
        printf("Error\nNull line passed to process_map_line\n");
        return line_count; // Ignore and continue
    }

    printf("Debug: Processing line: %s\n", line); // Debug log

    if (is_line_empty(line)) {
        free(line);
        return line_count;
    }

    map[line_count] = line;
    return line_count + 1;
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
while ((line = get_next_line(fd)) != NULL) {
    if (!line) {
        printf("Error\nget_next_line returned NULL unexpectedly\n");
        continue; // Skip invalid lines
    }

    printf("Debug: Read line: %s\n", line); // Debug log
    line_count = process_map_line(map, line, line_count);
    if (line_count >= max_line) {
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
