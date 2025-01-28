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

int	calculate_step_size(t_ray *ray, char c)
{
	float	delta_x;
	float	m;

	m = ray->pos[Y] / ray->pos[X];
	if (c = 'X')
	{
		delta_x = sqrt(1 + (ray->pos[Y] * ray->pos[Y]));
	}
	else if (c = 'Y')
	{

	}
}

void	ray_caster_step(t_data *data, t_ray *ray)
{
	int	step[2];

	/*
		we should know the direction of the ray
		step[0] = 1;
		step[1] = 0;
	*/
	while(/*hit the wall*/)
	{
		if(ray->length[X] < ray->length[Y])
		{
			ray->pos[X] += ray->step[X];
			ray->final_dest = ray->length;
			ray->length += calculate_step_size(ray,'X');

		}
		else if(ray->length[Y] < ray->length[X])
		{

		}
		/*else?*/
	}
}

void	press_key()
{}

void	render()
{}

void	execution(t_data *data)
{
	/*
		1.initialize mlx
		2.load texture
		3.Get the angel
		4.mlx key hook
		5.mlx loop hook
		6.mlx loop
		7.exit
	*/
	// t_mlx	*mlx;
	mlx_t	*mlx_p;
	data->posX = 2.5;
	data->posY = 2.5;
	data->dirX = 1;
	data->dirY = 0.5;


	mlx_p = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	// if (mlx_p == NULL)
	// {
	// 	//error, free, exit
	// }
	// if (!load_texture())
	// {
	// 	//error, free, exit
	// }
	// if (!get_angel())
	// {
	// 	//error, free, exit
	// }

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
