/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   start_game.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: kziari <marvin@42.fr>                         +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/01/16 15:19:44 by kziari         #+#    #+#                */
/*   Updated: 2025/01/16 15:19:46 by kziari         ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

/*
	11111
	10001
	10N01
	10001
	11111
*/

#include "cub3d.h"


/*
	1.Map parsing and validating (done)
	2.Casting the rays
	3.Rendering the walls
	4.Player movement(loop 2.Casting the rays and 3.Rendering the walls)
*/


void	init_ray(t_game *game, t_ray *ray, int x)
{
	float	camera_x;

	ray = malloc(sizeof(t_ray));

	// Set the initial position of the ray at the player's position
	ray->pos_x = game->player->x;
	ray->pos_y = game->player->y;

	// Compute the camera X coordinate for this screen column (-1 to 1 range)
	camera_x = 2 * x / (float)WIDTH - 1;

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
}

void	init_player(t_game *game, t_player *player)
{
	player = malloc (sizeof(t_player));
	player->x = game->map->player_x + 0.5;
	player->y = game->map->player_y + 0.5;
	if (game->map->player_facing_to = 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (game->map->player_facing_to = 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (game->map->player_facing_to = 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (game->map->player_facing_to = 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

int	perform_dda(t_game *game, t_ray *ray)
{
	int	side;

	while(true)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			//continue with x
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			side = 0;
		}
		else
		{
			//continue with y
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			side = 1;
		}
		if (game->map->map2d[ray->map_x][ray->map_y] == '1')
		{
			break;
		}
	}
	return (side);
}

void	render_wall(t_game *game, t_ray *ray, int side)
{
	float	wall_dist;
	int		line_height;
	int		star_draw;
	int		end_draw;

	if (side == 0)
		wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
	line_height = (int)(HEIGHT / wall_dist);
	star_draw = -line_height / 2 + HEIGHT / 2;
	if(star_draw < 0)
		star_draw = 0;
	end_draw = line_height / 2 + HEIGHT / 2;
	if (end_draw >= HEIGHT)
		end_draw = HEIGHT - 1;
}

void	render_raycasting(t_game *game)
{
	/*
		1.calculate ray direction based on position and oriantation of player
		2.calculate delta distance to reach next grid in each direction
		3.calculate step and initial side distances
		4.perfom DDA
		5.calculate wall height
	*/

	t_ray		ray;
	t_player	player;
	int			x;
	int			side;

	x = 0;
	//initial texture pixel
	init_player(game, &player);
	while (x < WIDTH)
	{
		init_ray(game, &ray, x);
		side = perform_dda(game, &ray);
		render_wall(game, &ray, side);
		x++;
	}
}

void	render_images(t_game *game)
{
	render_raycasting(game);
}

void	init_textures(t_game *game)
{
	//convert texture to displayeable image
	game->valid_texture->img_no = mlx_texture_to_image(game->init_mlx, game->valid_texture->no);
	if (game->valid_texture->img_no)
	{
		return(error_msg("texture to image failed: North"));
	}
	game->valid_texture->img_so = mlx_texture_to_image(game->init_mlx, game->valid_texture->so);
	if (game->valid_texture->img_so)
	{
		return(error_msg("texture to image failed: South"));
	}
	game->valid_texture->img_ea = mlx_texture_to_image(game->init_mlx, game->valid_texture->ea);
	if (game->valid_texture->img_ea)
	{
		return(error_msg("texture to image failed: East"));
	}
	game->valid_texture->img_we = mlx_texture_to_image(game->init_mlx, game->valid_texture->we);
	if (game->valid_texture->img_we)
	{
		return(error_msg("texture to image failed: West"));
	}
	
	//display the image
	//mlx_image_to_window()
}

void	execution(t_game *game)
{
	/*
		1.initialize mlx
		2.initialize textures
		3.render images
		4.render ray casting
		5.listen for inputs
		6.mlx loop hook
		7.mlx loop
		8.exit and 
	*/

	//start mlx
	game->init_mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (game->init_mlx == NULL)
	{
		//free?
		mlx_strerror(mlx_errno);
		// error_msg("mlx initial failed");
		return;
	}
	init_textures(game);
	render_images(game);
	// /*
	// 	This function sets the key callback, which is called when a
	// 	key is pressed on the keyboard. Useful for single keypress detection.
	// */
	// mlx_key_hook(mlx_p, press_key, data);

	// /*
	// 	Generic loop hook for any custom hooks to add to the main loop.
	// 	Executes a function per frame, so be careful.
	// */
	// if (!mlx_loop_hook(mlx_p, render, data))
	// {
	// 	//error, free, exit
	// }

	// /*
	// 	Initializes the rendering of MLX, this function won't return
	// 	until mlx_close_window is called, meaning it will loop until
	// 	the user requests that the window should close.
	// */
	// mlx_loop(mlx_p);

	// //ft_exit();
}
