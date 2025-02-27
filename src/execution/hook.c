/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kziari <kziari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:49:26 by kziari            #+#    #+#             */
/*   Updated: 2025/02/27 12:14:33 by kziari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	move_side(t_game *game, int flag)
{
	double	move_step;
	double	new_x;
	double	new_y;

	if (flag == RIGHT)
		move_step = 0.05;
	else
		move_step = -0.05;
	new_x = game->player->x + game->player->plane_x * move_step;
	new_y = game->player->y + game->player->plane_y * move_step;
	if ((game->map->map2d[(int)(new_y - HITBOX)][(int)(new_x)] == '0')
	&& (game->map->map2d[(int)(new_y)][(int)(new_x - HITBOX)] == '0')
	&& (game->map->map2d[(int)(new_y + HITBOX)][(int)(new_x)] == '0')
	&& (game->map->map2d[(int)(new_y)][(int)(new_x + HITBOX)] == '0')
	&& (game->map->map2d[(int)(new_y)][(int)(new_x)] == '0'))
	{
		game->player->x = new_x;
		game->player->y = new_y;
		return ;
	}
}

static void	move(t_game *game, int flag)
{
	double	move_step;
	double	new_x;
	double	new_y;

	if (flag == FORWARD)
		move_step = 0.05;
	else
		move_step = -0.05;
	new_x = game->player->x + game->player->dir_x * move_step;
	new_y = game->player->y + game->player->dir_y * move_step;
	if ((game->map->map2d[(int)(new_y - HITBOX)][(int)(new_x)] == '0')
	&& (game->map->map2d[(int)(new_y)][(int)(new_x - HITBOX)] == '0')
	&& (game->map->map2d[(int)(new_y + HITBOX)][(int)(new_x)] == '0')
	&& (game->map->map2d[(int)(new_y)][(int)(new_x + HITBOX)] == '0')
	&& (game->map->map2d[(int)(new_y)][(int)(new_x)] == '0'))
	{
		game->player->x = new_x;
		game->player->y = new_y;
		return ;
	}
}

static void	turn(t_game *game, int flag)
{
	double	new_plane_x;
	double	new_x_direction;
	double	move_step;

	if (flag == TURN_LEFT)
		move_step = -0.05;
	else
		move_step = 0.05;
	new_plane_x = game->player->plane_x * cos(move_step)
		- game->player->plane_y * sin(move_step);
	game->player->plane_y = game->player->plane_x * sin(move_step)
		+ game->player->plane_y * cos(move_step);
	new_x_direction = game->player->dir_x * cos(move_step)
		- game->player->dir_y * sin(move_step);
	game->player->dir_y = game->player->dir_x * sin(move_step)
		+ game->player->dir_y * cos(move_step);
	game->player->plane_x = new_plane_x;
	game->player->dir_x = new_x_direction;
}

void	press_key(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->init_mlx, MLX_KEY_W))
		move(game, FORWARD);
	if (mlx_is_key_down(game->init_mlx, MLX_KEY_S))
		move(game, BACKWARD);
	if (mlx_is_key_down(game->init_mlx, MLX_KEY_A))
		move_side(game, LEFT);
	if (mlx_is_key_down(game->init_mlx, MLX_KEY_D))
		move_side(game, RIGHT);
	if (mlx_is_key_down(game->init_mlx, MLX_KEY_RIGHT))
		turn(game, TURN_RIGHT);
	if (mlx_is_key_down(game->init_mlx, MLX_KEY_LEFT))
		turn(game, TURN_LEFT);
	if (mlx_is_key_down(game->init_mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->init_mlx);
}
