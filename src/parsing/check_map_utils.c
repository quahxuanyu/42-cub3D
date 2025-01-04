/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 19:36:32 by hheng             #+#    #+#             */
/*   Updated: 2025/01/03 21:34:36 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Check whether the middle zeros are surrounded by ones */
/* up, down, left, right need to be surrounded by ones */
/* Skip first and last line */
void	check_middle_map_line(t_game *game)
{
	 int        i;
    int        j;

    i = 1;
    while (i < (game->map_height - 1))
    {
        j = 1;
        while (j < (game->map_data.width - 1))
        {
            if (game->map[i][j] == '0' || game->map[i][j] == 'N'
                || game->map[i][j] == 'S' || game->map[i][j] == 'W'
                || game->map[i][j] == 'E' || game->map[i][j] == 'D')
            {
                if (game->map[i + 1][j] == ' '
                    || game->map[i - 1][j] == ' '
                    || game->map[i][j + 1] == ' '
                    || game->map[i][j - 1] == ' ')
                    print_err_msg("Map is not surrounded by wall");
            }
            j++;
        }
        i++;
    }
}

/* If there is more than one N, S, W or E, exit the program */
/* Store player direction in player struct */
void    check_only_one_player(t_game *game)
{
    int    i;
    int    j;
    int    count_player;

    i = 0;
    count_player = 0;
    while (game->map[i] != NULL)
    {
        j = 0;
        while (game->map[i][j] != '\0')
        {
            if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
                || game->map[i][j] == 'W' || game->map[i][j] == 'E')
            {
                count_player++;
                // Store player position and direction when found
                game->player.pos_x = (float)j;
                game->player.pos_y = (float)i;
                game->player.angle = (game->map[i][j] == 'N') ? 270 :
                                   (game->map[i][j] == 'S') ? 90 :
                                   (game->map[i][j] == 'W') ? 180 : 0;
            }
            if (count_player > 1)
                print_err_msg("More than one player in the map");
            j++;
        }
        i++;
    }
    if (count_player == 0)
        print_err_msg("Need at least one player");
}

/* Map can only contain 1, 0, N, S, W, E, D */
void    check_invalid_character(t_game *game)
{
    int        i;
    int        j;

    i = 0;
    while (game->map[i] != NULL)
    {
        j = 0;
        while (game->map[i][j] != '\0')
        {
            // Simplified check since door state is not in the new structure
            if (ft_strchr("10NSWED \n", game->map[i][j]) == NULL)
                print_err_msg("Map contains invalid character");
            j++;
        }
        i++;
    }
}


/* Checks the first character in each line whether is 1 */
void    check_first_and_last_char(t_game *game)
{
    int        i;
    char    *copy_map_line;
    char    *after_trim;
    int        len;

    i = 0;
    while (game->map[i] != NULL)
    {
        copy_map_line = ft_strdup(game->map[i]);
        after_trim = ft_strtrim(copy_map_line, " ");
        len = ft_strlen(after_trim);
        if (len > 1)
        {
            if (ft_strchr("1\n ", after_trim[0]) == NULL)
                print_err_msg("Map is not surrounded by walls- first character");
            if (ft_strchr("1\n ", after_trim[len - 1]) == NULL)
                print_err_msg("Map is not surrounded by walls- last character");
        }
        free(after_trim);
        free(copy_map_line);
        i++;
    }
}