/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ray_casting.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: kziari <marvin@42.fr>                         +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/04 15:21:32 by kziari         #+#    #+#                */
/*   Updated: 2025/02/04 15:21:33 by kziari         ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_ray	*init_ray(t_game *game, t_ray *ray, int x)
{
	float	camera_x;

	// Set the initial position of the ray at the player's position
	ray->pos_x = game->player->x;
	ray->pos_y = game->player->y;
	
	// Compute the camera X coordinate for this screen column (-1 to 1 range)
	camera_x = 2 * x / (double)WIDTH - 1;

	// Compute the ray direction
	ray->ray_dir_x = game->player->dir_x + game->player->plane_x * camera_x;
	ray->ray_dir_y = game->player->dir_y + game->player->plane_y *camera_x;

	// Grid position of the ray
	ray->map_x = (int)ray->pos_x; //player_x
	ray->map_y = (int)ray->pos_y; //player_y

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
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
	// printf("game_player=%f\nray_posx=%f\n", game->player->x,ray->pos_x);
	//printf("finish init ray\n\n");
	return (ray);
}



int	perform_dda(t_game *game, t_ray *ray)
{
	int	side;

	//printf("before dda loop\n");
	while(true)
	{
		//printf("side_dist_x=%f\nside_dist_y=%f\n", ray->side_dist_x, ray->side_dist_y);
		if (ray->side_dist_x < ray->side_dist_y)
		{
			//printf("side_dist_x < side_dist_y\n");
			//continue with x
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			if (ray->ray_dir_x < 0)
				side = we;
			else
				side = ea;
		}
		else
		{
			//printf("side_dist_x >= side_dist_y\n");
			//printf("delta_dist_y=%f\nstep_y=%f\nmap_y=%d\nray_dir_y=%f\n\n", ray->delta_dist_y, ray->step_y, ray->map_y, ray->ray_dir_y);
			//continue with y
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			if (ray->ray_dir_y < 0)
				side = no;
			else
				side = so;
			//printf("side_dist_y=%f\nmap_y=%d\nray_dir_y=%f\nside=%d\n", ray->side_dist_y, ray->map_y, ray->ray_dir_y, side);
		}
		//printf("\n\nmap[%d][%d] = %c\n", ray->map_y, ray->map_x, game->map->map2d[ray->map_y][ray->map_x]);
		if (game->map->map2d[ray->map_y][ray->map_x] == '1' || ray->map_x < 0 || ray->map_x >= game->map->width
			|| ray->map_y < 0 || ray->map_y >= game->map->height)
		{
			//printf("hit the wall\n");
			break;
		}
	}
	//printf("after dda loop\n\n");
	return (side);
}

// void	draw_wall(t_game *game)
// {

// }

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

	// wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
	//wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
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
		ray->wall_x = ray->pos_y + wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = ray->pos_x + wall_dist * ray->ray_dir_x;
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
	tex_x = (int) (ray->wall_x * (double)tex_width);
	if ((side == we || side == ea) && ray->ray_dir_x > 0)
		tex_x = tex_width - tex_x - 1;
	if ((side == no || side == so) && ray->ray_dir_y < 0)
		tex_x = tex_width - tex_x - 1;
	step = 1.0 * tex_height / line_height;
	pos = fabs((start_draw - HEIGHT / 2 + line_height / 2) * step);
	j = 0;
	while (j < HEIGHT)
	{
		if (j < start_draw)
		{
			mlx_put_pixel(game->valid_texture->img, i, j, game->valid_texture->ceiling);
		}
		else if (j >= start_draw && j <= end_draw)
		{
			//draw_wall
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
	game->ray = malloc(sizeof(t_ray));
	if (!game->ray)
	{
		return;
	}
	x = 0;
	//initial texture pixel
	// printf("\n\nbefore ray loop\n");
	while (x < WIDTH)
	{
		// printf("after ray loop\n\n");
		game->ray = init_ray(game, game->ray, x);
		side = perform_dda(game, game->ray);
		render_wall(game, game->ray, side, x);
		x++;
	}
}
