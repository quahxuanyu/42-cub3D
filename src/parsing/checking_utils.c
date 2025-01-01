/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:56:31 by hheng             #+#    #+#             */
/*   Updated: 2025/01/01 21:52:35 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void print_err_msg(char *msg)
{
	ft_printf("Error\n");
	ft_printf(msg);
	ft_printf("\n");
	exit(EXIT_FAILURE);
}

void free_map(char **map, size_t lines)
{
    for (size_t i = 0; i < lines; i++)
        free(map[i]);
    free(map);
}

/* Count total number of lines in .cub file */
int	ft_count_lines(int fd)
{
	char	*str;
	int		count;

	count = 0;
	str = get_next_line(fd);
	while (str != NULL)
	{
		free(str);
		count++;
		str = get_next_line(fd);
	}
	return (count + 1);
}

void	ft_freesplit(char **split)
{
	int	i;

	i = -1;
	while (split[++i] != NULL)
		free(split[i]);
	free(split);
}

/* Check whether str (textures) contains extra characters  */
/* E.g. NO	./sprites/north.xpm x 				*/
/* char **split = NO	./sprites/north.xpm x   */
void	check_extra_character(char **split)
{
	int		i;
	char	*after_trim;
	int		count;

	i = 0;
	count = 0;
	while (split[i] != NULL)
	{
		after_trim = ft_strtrim(split[i], " \t\n");
		if (ft_strlen(after_trim) > 0)
			count++;
		free(after_trim);
		i++;
	}
}

/* Check whether the character is a 1 or space or newline or tab */
void	check_for_ones(char *str, int i)
{
	if (str[i] != '1' && str[i] != ' ' && str[i] != '\n'
		&& str[i] != '\t')
	{
		free(str);
		print_err_msg("Invalid map/element");
	}
}
