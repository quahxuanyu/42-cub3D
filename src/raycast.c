/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:44:43 by xquah             #+#    #+#             */
/*   Updated: 2024/12/22 16:52:53 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Add this function to trim spaces and validate map lines
char *trim_and_validate_map_line(const char *line)
{
    if (!line)
        return NULL;
        
    // Skip leading spaces
    while (*line && (*line == ' ' || *line == '\t'))
        line++;
        
    // Get length without trailing spaces
    size_t len = ft_strlen(line);
    while (len > 0 && (line[len-1] == ' ' || line[len-1] == '\t'))
        len--;
        
    // Allocate and copy trimmed line
    char *trimmed = malloc(len + 1);
    if (!trimmed)
        return NULL;
    ft_strlcpy(trimmed, line, len + 1);
    
    return trimmed;
}

// Modify touch function to handle spaces
bool touch(t_game *game, float px, float py)
{
    int map_x;
    int map_y;

    map_x = px / WALL_SIZE;
    map_y = py / WALL_SIZE;
    
    // Check boundaries
    if (map_y < 0 || map_x < 0 || !game->map[map_y])
        return true;
        
    // Get line length
    size_t line_len = ft_strlen(game->map[map_y]);
    if ((size_t)map_x >= line_len)
        return true;
        
    // Consider spaces as walls
    char cell = game->map[map_y][map_x];
    return (cell == '1' || cell == ' ');
}

// Add this function to find and set player position
bool init_player_position(t_game *game)
{
    const char player_chars[] = "NSEW";
    int found = 0;
    
    for (int y = 0; game->map[y]; y++)
    {
        for (int x = 0; game->map[y][x]; x++)
        {
            char cell = game->map[y][x];
            if (ft_strchr(player_chars, cell))
            {
                game->player.x = x * WALL_SIZE + (WALL_SIZE / 2);
                game->player.y = y * WALL_SIZE + (WALL_SIZE / 2);
                
                // Set initial angle based on direction
                if (cell == 'N') game->player.angle = -PI/2;
                else if (cell == 'S') game->player.angle = PI/2;
                else if (cell == 'E') game->player.angle = 0;
                else if (cell == 'W') game->player.angle = PI;
                
                found = 1;
                // Replace player position with empty space
                game->map[y][x] = '0';
                break;
            }
        }
        if (found) break;
    }
    
    return found;
}


bool	ray_touch(t_game *game, float ray_x, float ray_y)
{
	float	player_x;
	float	player_y;

	player_x = game->player.x;
	player_y = game->player.y;
	if (touch(game, ray_x, ray_y))
	{
		if (player_x - ray_x < player_y - ray_y)
		{
			if (player_x - ray_x > 0)
				game->side = 0;
			else
				game->side = 1;
		}
		else
		{
			if (player_y - ray_y > 0)
				game->side = 2;
			else
				game->side = 3;
		}
		return (true);
	}
	return (false);
}

void draw_ray(t_game *game, float angle, int x)
{
    float ray_x;
    float ray_y;
    float cos_angle;
    float sin_angle;
    float max_distance = 1000.0f; // Prevent infinite loops
    float distance = 0.0f;

    ray_x = game->player.x;
    ray_y = game->player.y;
    cos_angle = cos(angle);
    sin_angle = sin(angle);
    
    while (!ray_touch(game, ray_x, ray_y) && distance < max_distance)
    {
        if (VIEW_STATE == 2)
            my_mlx_pixel_put(game, ray_x, ray_y, 0xFFFF00);
        ray_x += cos_angle;
        ray_y += sin_angle;
        distance += 1.0f;
    }
    
    if (VIEW_STATE == 3)
        three_d_projection(game, ray_x, ray_y, x);
}

void	raycast(t_game *game)
{
	float ray_x;
	float ray_y;
	float cos_angle;
	float sin_angle;
	float FOV = PI / 3;
	float fraction = FOV / screenWidth;
	float angle_diff = (FOV / 2) * -1;	
	int i = -1;
	// draw_ray(game, game->player.angle, i);
	while (++i < screenWidth)
	{
		draw_ray(game, angle_diff + game->player.angle, i);
		angle_diff += fraction;
	}
}