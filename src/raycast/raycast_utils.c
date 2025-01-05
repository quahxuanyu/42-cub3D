/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:44:43 by xquah             #+#    #+#             */
/*   Updated: 2025/01/05 14:20:40 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    init_ray(t_player *player, t_ray *ray, int x)
{
    ray->camera_perc = 2 * x / (double)screenWidth - 1;
    ray->dir_x = player->dir_x + player->plane_x * ray->camera_perc;
    ray->dir_y = player->dir_y + player->plane_y * ray->camera_perc;
    ray->map_x = (int)player->pos_x;
    ray->map_y = (int)player->pos_y;
    ray->delta_dist_x = fabs(1 / ray->dir_x);
    ray->delta_dist_y = fabs(1 / ray->dir_y);
}

void    get_initial_dist(t_player *player, t_ray *ray)
{
    if (ray->dir_x >= 0)
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = -1;
        ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
    }
    if (ray->dir_y >= 0)
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = -1;
        ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
    }
}

void    dda_algo(t_game *game, t_player *player, t_ray *ray)
{
    int hit;

    hit = 0;
    // perform DDA
    while (hit == 0)
    {
        // jump to next map square, either in x-direction, or in y-direction
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        // Check if ray has hit a wall
        if (game->map_data.map[ray->map_y][ray->map_x] == '1')
            hit = 1;
    }
}

void    calc_wall_dist(t_ray *ray)
{
    if (ray->side == VERTICAL)
        ray->wall_dist = ray->side_dist_x - ray->delta_dist_x;
    else if (ray->side == HORIZONTAL)
        ray->wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

void    draw_line_on_image(t_game *game, t_ray *ray, int x)
{
    int line_height;
    int draw_start;
    int draw_end;
    
    line_height = (int)(screenHeight / ray->wall_dist);
    draw_start = screenHeight / 2 - line_height / 2;
    draw_end = screenHeight / 2 + line_height / 2;
    while (draw_start < draw_end)
    {
        if (ray->side == VERTICAL)
            my_mlx_pixel_put(game, x, draw_start, 0x0000FF);
        else
            my_mlx_pixel_put(game, x, draw_start, 0x00FF00);
        draw_start++;
    }
}