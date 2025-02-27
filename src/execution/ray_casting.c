/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kziari <kziari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:21:32 by kziari            #+#    #+#             */
/*   Updated: 2025/02/27 15:19:17 by kziari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_ray	*init_ray_helper(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player->x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player->y)
			* ray->delta_dist_y;
	}
	return (ray);
}
// Distance to next grid intersection

t_ray	*init_ray(t_game *game, t_ray *ray, int x)
{
	float	camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = game->player->dir_x + game->player->plane_x * camera_x;
	ray->ray_dir_y = game->player->dir_y + game->player->plane_y * camera_x;
	ray->map_x = (int)game->player->x;
	ray->map_y = (int)game->player->y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray = init_ray_helper(game, ray);
	return (ray);
}

static int	set_side(t_ray *ray, bool is_vertical)
{
	int	side;

	if (ray->ray_dir_x < 0 && !is_vertical)
		side = we;
	if (ray->ray_dir_x >= 0 && !is_vertical)
		side = ea;
	if (ray->ray_dir_y < 0 && is_vertical)
		side = no;
	if (ray->ray_dir_y >= 0 && is_vertical)
		side = so;
	return (side);
}

int	perform_dda(t_game *game, t_ray *ray)
{
	int	side;

	while (true)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			side = set_side(ray, false);
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			side = set_side(ray, true);
		}
		if (game->map->map2d[ray->map_y][ray->map_x] == '1' || ray->map_x < 0
			|| ray->map_x >= game->map->width || ray->map_y < 0
			|| ray->map_y >= game->map->height)
			break ;
	}
	return (side);
}
