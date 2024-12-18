/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:33:48 by xquah             #+#    #+#             */
/*   Updated: 2024/12/18 12:30:26 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x >= screenWidth || y >= screenHeight || x < 0 || y < 0)
		return ;
	dst = game->data + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int*) dst = color;
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;

	i = -1;
	while (++i < size)
		my_mlx_pixel_put(game, x + i, y, color);
	i = -1;
	while (++i < size)
		my_mlx_pixel_put(game, x, y + i, color);
	i = -1;
	while (++i < size)
		my_mlx_pixel_put(game, x + i, y + size, color);
	i = -1;
	while (++i <= size)
		my_mlx_pixel_put(game, x + size, y + i, color);
}