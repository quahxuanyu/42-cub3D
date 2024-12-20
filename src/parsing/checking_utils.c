/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:56:31 by hheng             #+#    #+#             */
/*   Updated: 2024/12/20 17:56:34 by hheng            ###   ########.fr       */
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