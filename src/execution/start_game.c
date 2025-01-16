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

#include "cub3d.h"

/*
	1.Map parsing and validating (done)
	2.Casting the rays
	3.Rendering the walls
	4.Player movement(loop 2.Casting the rays and 3.Rendering the walls)
*/

void	press_key()
{}

void	render()
{}

void	start_game(t_data *data)
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
	

	mlx_p = mlx_init(WIDTH, HEIGHT, "cub3d", RESIZE);
	if (mlx_p == NULL)
	{
		//error, free, exit
	}
	if (!load_texture())
	{
		//error, free, exit
	}
	if (!get_angel())
	{
		//error, free, exit
	}

	/*
		This function sets the key callback, which is called when a
		key is pressed on the keyboard. Useful for single keypress detection.
	*/
	mlx_key_hook(mlx_p, press_key, data);

	/*
		Generic loop hook for any custom hooks to add to the main loop.
		Executes a function per frame, so be careful.
	*/
	if (!mlx_loop_hook(mlx_p, render, data))
	{
		//error, free, exit
	}

	/*
		Initializes the rendering of MLX, this function won't return
		until mlx_close_window is called, meaning it will loop until
		the user requests that the window should close.
	*/
	mlx_loop(mlx_p);
	
	ft_exit();
}
