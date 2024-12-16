/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:38:20 by hheng             #+#    #+#             */
/*   Updated: 2024/12/14 18:53:11 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int check_input (int ac, char **av)
{
	if (ac == 1)
	{
		printf("Error\nNo map file provided\n");
		return (1);
	} else if (av > 2) 
	{
		printf("Error\nToo many arguments\n");
		return (1);
	}else if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
	{
		printf("Error\nInvalid file extension\n");
		return (1);
	}
}