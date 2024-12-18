/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:14:47 by hheng             #+#    #+#             */
/*   Updated: 2024/12/18 21:15:13 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Function to count the number of lines in the file
static int count_lines(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
        return -1;

    int lines = 0;
    char c;
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
            lines++;
    }
    fclose(file);
    return lines;
}

// Function to read the map into a 2D array
char **read_map_from_file(const char *filename)
{
    int line_count = count_lines(filename);
    if (line_count <= 0)
    {
        printf("Error\nFailed to count map lines\n");
        return NULL;
    }

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error\nCould not open map file\n");
        return NULL;
    }

    char **map = malloc((line_count + 1) * sizeof(char *));
    if (!map)
    {
        printf("Error\nMemory allocation failed\n");
        fclose(file);
        return NULL;
    }

    size_t len = 0;
    ssize_t read;
    char *line = NULL;
    int i = 0;

    while ((read = getline(&line, &len, file)) != -1)
    {
        line[read - 1] = '\0'; // Remove newline character
        map[i] = strdup(line); // Copy the line into the map array
        i++;
    }
    map[i] = NULL; // Null-terminate the map array

    free(line);
    fclose(file);
    return map;
}