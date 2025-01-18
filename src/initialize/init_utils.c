/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:31:14 by xquah             #+#    #+#             */
/*   Updated: 2025/01/18 10:56:09 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/***
 * @brief Initialize player's position and direction
 * @note Later when parsing is finish initialize the player position from file
 * @note CURRENT: (Hardcode) Set player position to (5, 5) and North facing
 */
void    init_player(t_player *player)
{
    player->dir = 'N';       // set facing north for now
    player->pos_x = 5 + 0.5; // set in middle for now
    player->pos_y = 5 + 0.5; // set in middle for now
    player->dir_x = 0;
    player->dir_y = -1;
    player->plane_x = 0.66;
    player->plane_y = 0;
    player->key_up = false;
    player->key_down = false;
    player->key_left = false;
    player->key_right = false;
    player->left_rotate = false;
    player->right_rotate = false;
}

/**
 * @brief Initialize the MLX window, image, and data address
 */
void    init_mlx(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        printf("Error: Failed to initialize mlx\n");
        exit(EXIT_FAILURE);
    }
    game->win = mlx_new_window(game->mlx, screenWidth, screenHeight, "Raycast Test");
    if (!game->win)
    {
        printf("Error: Failed to create window\n");
        exit(EXIT_FAILURE);
    }
    game->img = mlx_new_image(game->mlx, screenWidth, screenHeight);
    if (!game->img)
    {
        printf("Error: Failed to create image\n");
        exit(EXIT_FAILURE);
    }
    game->data = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->line_length, &game->endian);
    if (!game->data)
    {
        printf("Error: Failed to get data address\n");
        exit(EXIT_FAILURE);
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

/***
 * @brief Load the texture from the .xpm file to an image
 * @param game the game structure
 * @param img the image to store the loaded texture
 * @param filename the filename of the .xpm texture
 */
int load_texture(t_game *game, t_img *tex, char *path)
{
    printf("Debug: Loading texture from: %s\n", path);
    
    // Clean up existing texture if present
    if (tex->img != NULL)
    {
        mlx_destroy_image(game->mlx, tex->img);
        tex->img = NULL;
        tex->addr = NULL;
    }

    // Load the texture
    tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width, &tex->height);
    if (!tex->img)
    {
        printf("Error: mlx_xpm_file_to_image failed for %s\n", path);
        return (FALSE);
    }

    // Get the texture data
    int bits_per_pixel;
    int line_length;
    int endian;
    tex->addr = mlx_get_data_addr(tex->img, &bits_per_pixel, &line_length, &endian);
    if (!tex->addr)
    {
        printf("Error: mlx_get_data_addr failed\n");
        mlx_destroy_image(game->mlx, tex->img);
        tex->img = NULL;
        return (FALSE);
    }

    // Store the texture information
    tex->bits_per_pixel = bits_per_pixel;
    tex->line_length = line_length;
    tex->endian = endian;

    printf("Debug: Texture loaded - width: %d, height: %d\n", tex->width, tex->height);
    return (TRUE);
}


/***
 * @brief Initialize texutures from the map file
 * @note Currently hardcoding the wall textures, ceiling and floor colors
 * @note Changed from individual variables to array of t_img for wall textures (wall_tex[])
 * @note Ceiling and Floor colors changed from RGB struct to size_t
 */
int init_texture(t_game *game)
{
    if (!game)
        return (FALSE);

    game->map_data.wall_tex = (t_img *)malloc(sizeof(t_img) * 4);
    if (!game->map_data.wall_tex)
    {
        printf("Error: Failed to allocate texture array\n");
        return (FALSE);
    }
    
    // Initialize all texture structs to NULL/0
    for (int i = 0; i < 4; i++)
    {
        game->map_data.wall_tex[i].img = NULL;
        game->map_data.wall_tex[i].addr = NULL;
        game->map_data.wall_tex[i].height = 0;
        game->map_data.wall_tex[i].width = 0;
        game->map_data.wall_tex[i].bits_per_pixel = 0;
        game->map_data.wall_tex[i].line_length = 0;
        game->map_data.wall_tex[i].endian = 0;
    }
    
    game->map_data.c_rgb = 0x8FA8C6; //ceiling blue
    game->map_data.f_rgb = 0x949494; //floor grey

    return (TRUE);
}
