/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:50:52 by hheng             #+#    #+#             */
/*   Updated: 2024/12/22 15:15:44 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int is_valid_color_line(const char *line)
{
    // Skip leading spaces
    while (*line && ft_isspace(*line))
        line++;

    // Example: "C 225,30,0" or "F 1,1,1"
    if (ft_strncmp(line, "C ", 2) != 0 && ft_strncmp(line, "F ", 2) != 0)
        return 0;

    line += 2; // Skip the "C " or "F " part

    int count = 0; // To ensure three values (R, G, B)
    while (*line)
    {
        if (!ft_isdigit(*line) && *line != ',' && !ft_isspace(*line))
        {
            printf("Error: Invalid character '%c' in color line\n", *line);
            return 0;
        }
        if (*line == ',')
            count++;
        line++;
    }

    if (count != 2) // Ensure exactly two commas
    {
        printf("Error: Invalid color format. Expected format: R,G,B\n");
        return 0;
    }

    return 1;
}

