/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:20:03 by xquah             #+#    #+#             */
/*   Updated: 2024/12/18 12:46:43 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <limits.h>

void	init_texture(t_game *game, char *filename)
{
    int		fd;
    int		bits_per_pixel;
    int		line_length;
    int		endian;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        printf("Error\nTexture file not found\n");
        exit(1);
    }
	game->tex.width = 64;
	game->tex.width = 64;
	game->tex.img = mlx_xpm_file_to_image(game->mlx, filename, &game->tex.width, &game->tex.height);
    if (!game->tex.img)
    {
        printf("Error\nFailed to load texture\n");
        exit(1);
    }
    game->tex.addr = mlx_get_data_addr(game->tex.img, &bits_per_pixel, &line_length, &endian);
    game->tex.bits_per_pixel = bits_per_pixel;
    game->tex.line_length = line_length;
    game->tex.endian = endian;
}

unsigned int	get_pixel_color(t_img *tex, int x, int y)
{
    char	*pixel;
    int		color;

    pixel = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
    color = *(unsigned int *)pixel;
    return (color);
}