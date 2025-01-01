/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_element2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 21:48:53 by hheng             #+#    #+#             */
/*   Updated: 2025/01/01 21:48:59 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Check whether the first element after the last texture is a valid map */
/* And that the string can only contain 1s */
int	check_correct_order(char *str, int check)
{
	int	i;

	i = 0;
	if (check != 0)
		return (check);
	str = ft_strtrim(str, " \t\n");
	if (ft_strlen(str) < 1)
	{
		free(str);
		return (check);
	}
	if (check == 0)
	{
		while (str[i] != '\0')
		{
			check_for_ones(str, i);
			i++;
		}
		check++;
	}
	free(str);
	return (check);
}

/* Get the first line of the map */
/* By triming that line (trim out) space, tabs and newline */
/* If the first character is \0, it is not the first line */
/* Do the same to the next line, until the first character is not \0 */
int	get_first_line(char **temp_map, int first_line)
{
	int		i;
	char	*temp_trim_str;

	i = 0;
	while (temp_map[i] != NULL)
	{
		temp_trim_str = ft_strtrim(temp_map[i], " \t\n");
		if (temp_trim_str[0] == '\0')
		{
			free(temp_trim_str);
			i++;
		}
		else
		{
			first_line = i;
			free(temp_trim_str);
			return (first_line);
		}
	}
	return (-1);
}

/* Get last line of map content */
/* Using the same logic as get_first_line */
/* Start checking from the last line of the temp_map */
int	get_last_line(char **temp_map, int last_line)
{
	int		i;
	int		count;
	char	*temp_trim_str;

	count = 0;
	while (temp_map[count] != NULL)
		count++;
	count--;
	i = 0;
	while (count > i)
	{
		temp_trim_str = ft_strtrim(temp_map[count], " \t\n");
		if (temp_trim_str[0] == '\0')
			free(temp_trim_str);
		else
		{
			last_line = count;
			free(temp_trim_str);
			return (last_line);
		}
		count--;
	}
	return (-2);
}
