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

// int	calculate_step_size(t_ray *ray, char c)
// {
// 	float	delta_x;
// 	float	m;

// 	m = ray->pos[Y] / ray->pos[X];
// 	if (c = 'X')
// 	{
// 		delta_x = sqrt(1 + (ray->pos[Y] * ray->pos[Y]));
// 	}
// 	else if (c = 'Y')
// 	{

// 	}
// }

// void	ray_caster_step(t_game *game, t_ray *ray)
// {
// 	int	step[2];

// 	/*
// 		we should know the direction of the ray
// 		step[0] = 1;
// 		step[1] = 0;
// 	*/
// 	while(/*hit the wall*/)
// 	{
// 		if(ray->length[X] < ray->length[Y])
// 		{
// 			ray->pos[X] += ray->step[X];
// 			ray->final_dest = ray->length;
// 			ray->length += calculate_step_size(ray,'X');

// 		}
// 		else if(ray->length[Y] < ray->length[X])
// 		{

// 		}
// 		/*else?*/
// 	}
// }


void	init_ray(t_game *game, t_ray *ray)
{
	ray = malloc(sizeof(t_ray));
	ray->pos_x = game->map->player_x;
	ray->pos_y = game->map->player_y;
	ray->delta_dist_x = abs(1 / ray->ray_dir_x);
	ray->delta_dist_y = abs(1 / ray->ray_dir_y);
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->map_x = ray->pos_x;
	ray->map_y = ray->pos_y;
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
}

// void	ray_casting(t_ray *ray)
// {
// 	//set dda
// 	//perfom dda --> calculate line height
// 	while(true)
// 	{
		
// 	}
// }

void	render_raycasting(t_game *game)
{
	/*
		1.calculate ray direction based on position and oriantation of player
		2.calculate delta distance to reach next grid in each direction
		3.calculate step and initial side distances
		4.perfom DDA
		5.calculate wall height
	*/

	t_ray	ray;
	//initial texture pixel
	init_ray(game, &ray); //1&2&3
	// ray_casting(&ray);
	//render frame/windonw?
	while(true)
	{
		if (ray.side_dist_x < ray.side_dist_y)
		{
			//continue with x
			ray.side_dist_x += ray.delta_dist_x;
			ray.map_x += ray.step_x;
		}
		else
		{
			//continue with y
			ray.side_dist_y += ray.delta_dist_y;
			ray.map_y += ray.step_y;
		}
		if (game->map->map2d[ray.map_x][ray.map_y] == '1')
		{
			break;
		}
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
		error_msg("mlx initial failed");
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
