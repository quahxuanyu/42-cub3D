/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:38:20 by hheng             #+#    #+#             */
/*   Updated: 2024/12/20 18:22:10 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//check argument
int check_input(int ac, char **av)
{
    if (ac < 2)
    {
        printf("Error\nNo map file provided\n");
        return (1);
    }
    else if (ac > 2)
    {
        printf("Error\nToo many arguments\n");
        return (1);
    }
    else if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
    {
        printf("Error\nInvalid file extension\n");
        return (1);
    }
    return (0);
}
//open file and check each line
// make sure file contains valid data before parsing
char **check_each_line(t_game *game, char *file)
{
    int fd;
    char *line;
    char **map;
    size_t i;
    size_t j;

    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening map file");
        return NULL;
    }
    map = malloc(sizeof(char *) * 11); // Allocate space for 11 rows + 1 for NULL termination
    if (!map)
    {
        perror("Error allocating memory for map");
        close(fd);
        return NULL;
    }
    i = 0;
    while (i < 10 && (line = get_next_line(fd)) != NULL)
    {
        if (!line)
        {
            printf("Error: get_next_line returned NULL\n");
            break;
        }
        
    j = 0;
        while (line[j] != '\0')
        {
            if (line[j] != '0' && line[j] != '1' && line[j] != ' ')
            {
                printf("Error: Invalid character '%c' in map file\n", line[j]);
                free(line);
                close(fd);
                return NULL;
            }
            j++;
        }
         map[i] = line;
        i++;
    }
    map[i] = NULL; // Null terminate the map
    close(fd);
    printf("Debug: Map is checked and valid\n");
    return map;
    
}
