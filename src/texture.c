/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:20:03 by xquah             #+#    #+#             */
/*   Updated: 2025/01/01 15:43:51 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned int	get_pixel_color(t_img *tex, int x, int y)
{
    char	*pixel;
    int		color;

    pixel = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
    color = *(unsigned int *)pixel;
    return (color);
}