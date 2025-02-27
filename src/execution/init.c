/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kziari <kziari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:06:30 by kziari            #+#    #+#             */
/*   Updated: 2025/02/27 15:23:38 by kziari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_player	*init_player_helper(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	return (player);
}

static bool	assign_texture(t_game *game)
{
	game->texture->no = mlx_load_png(game->no);
	if (!game->texture->no)
		return (error_msg("texture loading failed: north"), false);
	game->texture->so = mlx_load_png(game->so);
	if (!game->texture->so)
		return (error_msg("texture loading failed: south"), false);
	game->texture->we = mlx_load_png(game->we);
	if (!game->texture->we)
		return (error_msg("texture loading failed: west"), false);
	game->texture->ea = mlx_load_png(game->ea);
	if (!game->texture->ea)
		return (error_msg("texture loading failed: east"), false);
	return (true);
}

t_player	*init_player(t_game *game, t_player *player)
{
	player = init_player_helper(player);
	player->x = game->map->player_x + 0.5;
	player->y = game->map->player_y + 0.5;
	if (game->map->player_facing_to == 'N')
	{
		player->dir_y = -1;
		player->plane_x = 0.66;
	}
	else if (game->map->player_facing_to == 'S')
	{
		player->dir_y = 1;
		player->plane_x = -0.66;
	}
	else if (game->map->player_facing_to == 'E')
	{
		player->dir_x = 1;
		player->plane_y = 0.66;
	}
	else if (game->map->player_facing_to == 'W')
	{
		player->dir_x = -1;
		player->plane_y = -0.66;
	}
	return (player);
}

bool	init_textures(t_game *game)
{
	game->texture->img = mlx_new_image(game->init_mlx, WIDTH, HEIGHT);
	if (game->texture->img == NULL)
		return (ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2), false);
	game->texture->index = mlx_image_to_window(game->init_mlx,
			game->texture->img, 0, 0);
	if (game->texture->index == -1)
		return (ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2), false);
	if (!assign_texture(game))
		return (ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2), false);
	return (true);
}

bool	init_all(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	if (game->player == NULL)
		return (clean_all(game), false);
	game->ray = malloc(sizeof(t_ray));
	if (!game->ray)
	{
		free(game->player);
		return (clean_all(game), false);
	}
	game->render = malloc(sizeof(t_render));
	if (!game->render)
	{
		free(game->player);
		free(game->ray);
		return (clean_all(game), false);
	}
	return (true);
}
