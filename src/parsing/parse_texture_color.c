/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kziari <kziari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:02:42 by rshaheen          #+#    #+#             */
/*   Updated: 2025/02/27 15:24:18 by kziari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	init_texture_struct(t_game *game)
{
	game->texture = malloc(sizeof(t_texture));
	if (game->texture == NULL)
		return (error_msg("malloc failed for texture"), false);
	game->texture->floor = 0;
	game->texture->ceiling = 0;
	game->texture->ea = NULL;
	game->texture->no = NULL;
	game->texture->so = NULL;
	game->texture->we = NULL;
	return (true);
}

bool	is_texture_valid(t_game *game)
{
	if (game->no == NULL)
		return (false);
	if (game->so == NULL)
		return (false);
	if (game->ea == NULL)
		return (false);
	if (game->we == NULL)
		return (false);
	if (init_texture_struct(game) == false)
		return (false);
	return (true);
}

bool	parse_texture_n_color(t_game *game)
{
	if (is_texture_valid(game) == false)
		return (error_msg("invalid texture"), false);
	if (parse_color(game, game->ceiling_color) == false
		|| parse_color(game, game->floor_color) == false)
		return (false);
	return (true);
}
