/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:58:13 by hheng             #+#    #+#             */
/*   Updated: 2025/01/19 16:14:06 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Function to initialize the torch
void init_torch(t_game *game)
{
    game->torch.img.img = mlx_xpm_file_to_image(game->mlx, 
        "textures/minecraft_torch.xpm",
        &game->torch.img.width, 
        &game->torch.img.height);
    
    if (!game->torch.img.img)
    {
        printf("Error: Failed to load torch texture\n");
        return;
    }
    
    game->torch.img.addr = mlx_get_data_addr(game->torch.img.img,
        &game->torch.img.bits_per_pixel,
        &game->torch.img.line_length,
        &game->torch.img.endian);
    
    game->torch.bob_offset = 0;
    game->torch.bob_direction = 1;
}

// Function to get color from torch image
int get_torch_pixel(t_img *img, int x, int y)
{
    char    *dst;
    
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    return (*(unsigned int*)dst);
}

// Function to draw torch with swaying effect
void draw_torch(t_game *game)
{
    int x, y;
    int screen_x, screen_y;
    int color;
    float scale = 5.5;  // Increased scale from 2.0 to 3.5
    
    // Update torch bobbing (adjusted for larger scale)
    game->torch.bob_offset += 0.08 * game->torch.bob_direction;
    if (fabs(game->torch.bob_offset) > 4.0)
        game->torch.bob_direction *= -1;

    // Center position calculation
    int scaled_width = game->torch.img.width * scale;
    int scaled_height = game->torch.img.height * scale;
    
// Position in right corner (adjusted from center)
    int base_x = (screenWidth / 2) - (scaled_width / 2);  // 50 pixels from right edge
    int base_y = screenHeight - scaled_height - 10;
	
    // Draw scaled torch sprite
    for (y = 0; y < game->torch.img.height; y++)
    {
        for (x = 0; x < game->torch.img.width; x++)
        {
            // Calculate scaled positions
            screen_x = base_x + (x * scale) + game->torch.bob_offset;
            screen_y = base_y + (y * scale);
            
            color = get_torch_pixel(&game->torch.img, x, y);
            
            // Only draw non-transparent pixels (assuming black is transparent)
            if (color != 0x000000)  // 0x000000 is black/transparent
            {
                // Draw scaled pixel (as a small rectangle)
                for (int i = 0; i < scale; i++)
                {
                    for (int j = 0; j < scale; j++)
                    {
                        my_mlx_pixel_put(game, 
                            screen_x + i, 
                            screen_y + j, 
                            color);
                    }
                }
            }
        }
    }
}