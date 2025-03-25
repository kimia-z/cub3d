/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_texture_color.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 19:02:42 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/03/25 10:07:07 by rshaheen      ########   odam.nl         */
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
	int32_t	floor_rgb;
	int32_t	ceiling_rgb;

	if (is_texture_valid(game) == false)
		return (error_msg("invalid map content\n"), false);
	if (!game->ceiling_color || !game->floor_color)
		return (error_msg("color line missing\n"), false);
	else
	{
		if (game->floor_color[0] != 'F' || !ft_isspace(game->floor_color[1]))
			return (error_msg("floor color line misconfiguration\n"), false);
		floor_rgb = parse_color(game->floor_color);
		if (floor_rgb == -2)
			return (false);
		game->texture->floor = floor_rgb;
		if (game->ceiling_color[0] != 'C'
			|| !ft_isspace(game->ceiling_color[1]))
			return (error_msg("ceiling color line misconfiguration\n"), false);
		ceiling_rgb = parse_color(game->ceiling_color);
		if (ceiling_rgb == -2)
			return (false);
		game->texture->ceiling = ceiling_rgb;
	}
	return (true);
}
