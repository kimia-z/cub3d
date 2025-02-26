/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kziari <kziari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:21:32 by kziari            #+#    #+#             */
/*   Updated: 2025/02/26 14:48:25 by kziari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_ray	*init_ray(t_game *game, t_ray *ray, int x)
{
	float	camera_x;

	// Compute the camera X coordinate for this screen column (-1 to 1 range)
	camera_x = 2 * x / (double)WIDTH - 1;
	
	// Compute the ray direction
	ray->ray_dir_x = game->player->dir_x + game->player->plane_x * camera_x;
	ray->ray_dir_y = game->player->dir_y + game->player->plane_y *camera_x;

	// Grid position of the ray
	ray->map_x = (int)game->player->x; //player_x
	ray->map_y = (int)game->player->y; //player_y

	// Distance to next grid intersection
	if(ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if(ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player->x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player->y) * ray->delta_dist_y;
	}
	return (ray);
}

int	perform_dda(t_game *game, t_ray *ray)
{
	int	side;

	while(true)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			if (ray->ray_dir_x < 0)
				side = we;
			else
				side = ea;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			if (ray->ray_dir_y < 0)
				side = no;
			else
				side = so;
		}
		if (game->map->map2d[ray->map_y][ray->map_x] == '1' || ray->map_x < 0 || ray->map_x >= game->map->width
			|| ray->map_y < 0 || ray->map_y >= game->map->height)
			break;
	}
	return (side);
}

void	render_wall(t_game *game, t_ray *ray, int side, int i)
{
	float	wall_dist;
	int		line_height;
	int		start_draw;
	int		end_draw;
	int		tex_width;
	int		tex_height;
	int		tex_x;
	int		tex_y;
	double	step;
	double	pos;
	int		j;

	if (side == no || side == so)
		wall_dist = ray->side_dist_y - ray->delta_dist_y;
	else
		wall_dist = ray->side_dist_x - ray->delta_dist_x;
	line_height = (int)(HEIGHT / wall_dist);
	start_draw = (int)(-line_height / 2 + HEIGHT / 2);
	if(start_draw < 0)
		start_draw = 0;
	end_draw = (int)(line_height / 2 + HEIGHT / 2);
	if (end_draw > HEIGHT)
		end_draw = HEIGHT - 1;
	if (side == we || side == ea)
		ray->wall_x = game->player->y + wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->player->x + wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	if (side == no)
	{
		tex_width = game->valid_texture->no->width;
		tex_height = game->valid_texture->no->height;
	}
	else if (side == so)
	{
		tex_width = game->valid_texture->so->width;
		tex_height = game->valid_texture->so->height;
	}
	else if (side == ea)
	{
		tex_width = game->valid_texture->ea->width;
		tex_height = game->valid_texture->ea->height;
	}
	else
	{
		tex_width = game->valid_texture->we->width;
		tex_height = game->valid_texture->we->height;
	}
	tex_x = (int)(ray->wall_x * (double)tex_width);
	if ((side == we || side == ea) && ray->ray_dir_x > 0)
		tex_x = tex_width - tex_x - 1;
	if ((side == no || side == so) && ray->ray_dir_y < 0)
		tex_x = tex_width - tex_x - 1;
	step = 1.0 * tex_height / line_height;
	pos = (start_draw - HEIGHT / 2 + line_height / 2) * step;
	j = 0;
	while (j < HEIGHT)
	{
		if (j < start_draw)
		{
			mlx_put_pixel(game->valid_texture->img, i, j, game->valid_texture->ceiling);
		}
		else if (j >= start_draw && j <= end_draw)
		{
			mlx_texture_t	*texture = NULL;
			int	pixel;
			int rgba[4];
			int	color;

			if (side == no)
				texture = game->valid_texture->no;
			else if (side == so)
				texture = game->valid_texture->so;
			else if (side == we)
				texture = game->valid_texture->we;
			else if (side == ea)
				texture = game->valid_texture->ea;
			tex_y = pos;
			if (tex_y > tex_height)
				tex_y = tex_height - 1;
			pos += step;
			pixel = (tex_x + tex_y * tex_width) * 4;
			rgba[0] = texture->pixels[pixel];
			rgba[1] = texture->pixels[pixel + 1];
			rgba[2] = texture->pixels[pixel + 2];
			rgba[3] = texture->pixels[pixel + 3];
			color = get_rgb(rgba[0], rgba[1], rgba[2], rgba[3]);
			mlx_put_pixel(game->valid_texture->img, i, j, color);
		}
		else if (j > end_draw)
		{
			mlx_put_pixel(game->valid_texture->img,i, j, game->valid_texture->floor);
		}
		j++;
	}
}

void	render(void *param)
{
	/*
		1.calculate ray direction based on position and oriantation of player
		2.calculate delta distance to reach next grid in each direction
		3.calculate step and initial side distances
		4.perfom DDA
		5.calculate wall height
	*/
	t_game		*game;
	int			x;
	int			side;

	game = param;
	x = 0;
	game->ray = malloc(sizeof(t_ray));
	if (!game->ray)
	{
		clean_all(game);
		return (error_msg("memory allocation failed"));
	}
	while (x < WIDTH)
	{
		game->ray = init_ray(game, game->ray, x);
		side = perform_dda(game, game->ray);
		render_wall(game, game->ray, side, x);
		x++;
	}
}
