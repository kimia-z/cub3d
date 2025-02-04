/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   hook.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: kziari <marvin@42.fr>                         +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/04 15:49:26 by kziari         #+#    #+#                */
/*   Updated: 2025/02/04 15:49:27 by kziari         ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_game *game)
{
	if (game->map->map2d[game->map->player_y - 1][game->map->player_x] != '1')
	{
		//game->texture->player->instances->y -= 64;
		game->map->player_y--;
	}
	else
	{
		ft_putendl_fd("!You hit the wall!", 2);
	}
}

void	press_key(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS && keydata.action == MLX_REPEAT)
	{
		//look left
		//ray casting
		//render image

		render_images(game);
	}
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS && keydata.action == MLX_REPEAT)
	{
		//look right
		//ray casting
		//render image

		render_images(game);
	}
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS && keydata.action == MLX_REPEAT)
	{
		//move forward
		//ray casting
		//render image
		move_up(game);
		render_images(game);
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS && keydata.action == MLX_REPEAT)
	{
		//move backward
		//ray casting
		//render image

		render_images(game);
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS && keydata.action == MLX_REPEAT)
	{
		//move left
		//ray casting
		//render image

		render_images(game);
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS && keydata.action == MLX_REPEAT)
	{
		//move right
		//ray casting
		//render image

		render_images(game);
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		//close window
		//quit program
		mlx_close_window(game->init_mlx);
	}
}
