/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kziari <kziari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:19:44 by kziari            #+#    #+#             */
/*   Updated: 2025/02/27 15:44:43 by kziari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	execution(t_game *game)
{
	game->init_mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (game->init_mlx == NULL)
	{
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
		return (clean_all(game));
	}
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	if (init_textures(game) == false)
	{
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
		free(game->player);
		free(game->ray);
		return (clean_all(game));
	}
	if (!init_all(game))
		return (error_msg("memory allocation failed"));
	game->player = init_player(game, game->player);
	mlx_loop_hook(game->init_mlx, press_key, game);
	mlx_loop_hook(game->init_mlx, render, game);
	mlx_loop(game->init_mlx);
	mlx_delete_image(game->init_mlx, game->texture->img);
	mlx_close_window(game->init_mlx);
	mlx_terminate(game->init_mlx);
}
