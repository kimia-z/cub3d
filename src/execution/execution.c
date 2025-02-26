/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kziari <kziari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:19:44 by kziari            #+#    #+#             */
/*   Updated: 2025/02/26 13:46:50 by kziari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
	1.Map parsing and validating (done)
	2.Casting the rays
	3.Rendering the walls
	4.Player movement(loop 2.Casting the rays and 3.Rendering the walls)
*/

t_player	*init_player(t_game *game, t_player *player)
{
	player->x = game->map->player_x + 0.5;
	player->y = game->map->player_y + 0.5;
	if (game->map->player_facing_to == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (game->map->player_facing_to == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (game->map->player_facing_to =='E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (game->map->player_facing_to == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
	return(player);
}

bool	assign_texture(t_game *game)
{
	game->valid_texture->no = mlx_load_png(game->no);
	if (!game->valid_texture->no)
		return (error_msg("texture loading failed: north"), false);
	game->valid_texture->so = mlx_load_png(game->so);
	if (!game->valid_texture->so)
		return (error_msg("texture loading failed: south"), false);
	game->valid_texture->we = mlx_load_png(game->we);
	if (!game->valid_texture->we)
		return (error_msg("texture loading failed: west"), false);
	game->valid_texture->ea = mlx_load_png(game->ea);
	if (!game->valid_texture->ea)
		return (error_msg("texture loading failed: east"), false);
	return (true);
}
bool	init_textures(t_game *game)
{

	/*
		1.mlx_new_image
		2.mlx_image_to_window
		3.mlx_load_png
	*/

	game->valid_texture->img = mlx_new_image(game->init_mlx, WIDTH, HEIGHT);
	if (game->valid_texture->img == NULL)
		return (ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2), false);
	game->valid_texture->index = mlx_image_to_window(game->init_mlx, game->valid_texture->img, 0,0);
	if (game->valid_texture->index == -1)
		return (ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2), false);
	if (!assign_texture(game))
		return (ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2), false);
	return(true);
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
		8.exit
	*/

	game->player = malloc (sizeof(t_player));
	if (game->player == NULL)
	{
		error_msg("memory allocation failed");
		clean_all(game);
		return ;
	}
	game->init_mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (game->init_mlx == NULL)
	{
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
		clean_all(game);
		return;
	}
	if (init_textures(game) == false)
	{
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
		clean_all(game);
		return ;
	}
	game->player = init_player(game, game->player);
	mlx_loop_hook(game->init_mlx, press_key, game);
	mlx_loop_hook(game->init_mlx, render, game);
	mlx_loop(game->init_mlx);
	mlx_delete_image(game->init_mlx, game->valid_texture->img);
	clean_texture(game->valid_texture);
	mlx_close_window(game->init_mlx);
	mlx_terminate(game->init_mlx);
}
