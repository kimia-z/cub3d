/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kziari <kziari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:18:40 by kziari            #+#    #+#             */
/*   Updated: 2025/03/24 12:26:40 by kziari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_render	*get_tex(t_render *render, t_game *game, int side)
{
	if (side == no)
	{
		render->tex_width = game->texture->no->width;
		render->tex_height = game->texture->no->height;
	}
	else if (side == so)
	{
		render->tex_width = game->texture->so->width;
		render->tex_height = game->texture->so->height;
	}
	else if (side == ea)
	{
		render->tex_width = game->texture->ea->width;
		render->tex_height = game->texture->ea->height;
	}
	else
	{
		render->tex_width = game->texture->we->width;
		render->tex_height = game->texture->we->height;
	}
	return (render);
}

static t_render	*get_info(t_render *render, t_ray *ray, t_game *game, int side)
{
	render->line_height = (int)(HEIGHT / render->wall_dist);
	if (side == we || side == ea)
		ray->wall_x = game->player->y + render->wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->player->x + render->wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	render = get_tex(render, game, side);
	render->tex_x = (int)(ray->wall_x * (double)render->tex_width);
	if (side == we && ray->ray_dir_x < 0)
		render->tex_x = render->tex_width - render->tex_x - 1;
	else if (side == ea && ray->ray_dir_x < 0)
		render->tex_x = render->tex_width - render->tex_x - 1;
	else if (side == no && ray->ray_dir_y > 0)
		render->tex_x = render->tex_width - render->tex_x - 1;
	else if (side == so && ray->ray_dir_y > 0)
		render->tex_x = render->tex_width - render->tex_x - 1;
	render->step = 1.0 * render->tex_height / render->line_height;
	render->start_draw = (int)(-render->line_height / 2 + HEIGHT / 2);
	if (render->start_draw < 0)
		render->start_draw = 0;
	render->end_draw = (int)(render->line_height / 2 + HEIGHT / 2);
	if (render->end_draw > HEIGHT)
		render->end_draw = HEIGHT - 1;
	return (render);
}

static int	get_color(t_game *game, t_render *render, int side, int color)
{
	mlx_texture_t	*texture;
	int				pixel;
	int				rgba[4];

	texture = get_texture(game, side);
	render->tex_y = render->pos;
	if (render->tex_y > render->tex_height)
		render->tex_y = render->tex_height - 1;
	if (render->tex_x < 0 || render->tex_x >= (int)texture->width
		|| render->tex_y < 0 || render->tex_y >= (int)texture->height)
		return (color);
	render->pos += render->step;
	pixel = (render->tex_x + render->tex_y * render->tex_width) * 4;
	rgba[0] = texture->pixels[pixel];
	rgba[1] = texture->pixels[pixel + 1];
	rgba[2] = texture->pixels[pixel + 2];
	rgba[3] = texture->pixels[pixel + 3];
	color = get_rgb(rgba[0], rgba[1], rgba[2], rgba[3]);
	return (color);
}

void	render_wall(t_game *game, t_render *render, int side, int i)
{
	int	j;
	int	color;

	render = get_info(render, game->ray, game, side);
	render->pos = (render->start_draw - HEIGHT / 2
			+ render->line_height / 2) * render->step;
	j = 0;
	while (j < HEIGHT)
	{
		if (j < render->start_draw)
		{
			mlx_put_pixel(game->texture->img, i, j, game->texture->ceiling);
		}
		else if (j >= render->start_draw && j <= render->end_draw)
		{
			color = get_color(game, render, side, color);
			mlx_put_pixel(game->texture->img, i, j, color);
		}
		else if (j > render->end_draw)
		{
			mlx_put_pixel(game->texture->img, i, j, game->texture->floor);
		}
		j++;
	}
}

/*
	1.calculate ray direction based on position and oriantation of player
	2.calculate delta distance to reach next grid in each direction
	3.calculate step and initial side distances
	4.perfom DDA
	5.calculate wall height
*/

void	render(void *param)
{
	t_game		*game;
	int			x;
	int			side;

	game = param;
	x = 0;
	while (x < WIDTH)
	{
		game->ray = init_ray(game, game->ray, x);
		side = perform_dda(game, game->ray);
		if (side == no || side == so)
			game->render->wall_dist = game->ray->side_dist_y
				- game->ray->delta_dist_y;
		else
			game->render->wall_dist = game->ray->side_dist_x
				- game->ray->delta_dist_x;
		render_wall(game, game->render, side, x);
		x++;
	}
}
