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

// void	render_images(t_game *game)
// {
// 	render_raycasting(game);
// }

// void	img_init(t_game *game)
// {
// 	game->valid_texture->img_no = mlx_new_image(game->init_mlx, WIDTH, HEIGHT);
// 	if (game->valid_texture->img_no)
// 	{
// 		return(ft_putendl_fd(mlx_strerror(mlx_errno), 2));
// 	}
// 	game->valid_texture->img_so = mlx_new_image(game->init_mlx, WIDTH, HEIGHT);
// 	if (game->valid_texture->img_so)
// 	{
// 		return(ft_putendl_fd(mlx_strerror(mlx_errno), 2));
// 	}
// 	game->valid_texture->img_ea = mlx_new_image(game->init_mlx, WIDTH, HEIGHT);
// 	if (game->valid_texture->img_ea)
// 	{
// 		return(ft_putendl_fd(mlx_strerror(mlx_errno), 2));
// 	}
// 	game->valid_texture->img_we = mlx_new_image(game->init_mlx, WIDTH, HEIGHT);
// 	if (game->valid_texture->img_we)
// 	{
// 		return(ft_putendl_fd(mlx_strerror(mlx_errno), 2));
// 	}
// }

void	init_textures(t_game *game)
{

	/*
		1.mlx_new_img
		2.mlx_image_to_window
		3.mlx_load_png
	*/

	//mlx_new_image()
	//convert texture to displayeable image
	// if (assign_texture(game) == false)
	// {
	// 	return;
	// }
	// img_init(game);
	// game->valid_texture->img_no = mlx_texture_to_image(game->init_mlx, game->valid_texture->no);
	// if (game->valid_texture->img_no)
	// {
	// 	return(ft_putendl_fd(mlx_strerror(mlx_errno), 2));
	// }
	// game->valid_texture->img_so = mlx_texture_to_image(game->init_mlx, game->valid_texture->so);
	// if (game->valid_texture->img_so)
	// {
	// 	return(ft_putendl_fd(mlx_strerror(mlx_errno), 2));
	// }
	// game->valid_texture->img_ea = mlx_texture_to_image(game->init_mlx, game->valid_texture->ea);
	// if (game->valid_texture->img_ea)
	// {
	// 	return(ft_putendl_fd(mlx_strerror(mlx_errno), 2));
	// }
	// game->valid_texture->img_we = mlx_texture_to_image(game->init_mlx, game->valid_texture->we);
	// if (game->valid_texture->img_we)
	// {
	// 	return(ft_putendl_fd(mlx_strerror(mlx_errno), 2));
	// }
	
	//display the image
	// mlx_image_to_window()
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

	t_player	player;
	
	//start mlx
	game->init_mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (game->init_mlx == NULL)
	{
		//error, free, exit
		//free?
		ft_putendl_fd(mlx_strerror(mlx_errno), 2);
		return;
	}
	// render_images(game);
	// /*
	// 	This function sets the key callback, which is called when a
	// 	key is pressed on the keyboard. Useful for single keypress detection.
	// */
	// mlx_key_hook(game->init_mlx, &press_key, game);

	// /*
	// 	Initializes the rendering of MLX, this function won't return
	// 	until mlx_close_window is called, meaning it will loop until
	// 	the user requests that the window should close.
	// */
	init_textures(game);
	init_player(game, &player);
	mlx_key_hook(game->init_mlx, &press_key, game);
	mlx_key_hook(game->init_mlx, &render, game);
	mlx_terminate(game->init_mlx);
	mlx_loop(game->init_mlx);
	// //ft_exit();
}
