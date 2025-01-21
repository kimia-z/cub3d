/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_texture_n_color.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 19:02:42 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/21 19:22:38 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	init_texture_struct(t_game_config *data)
{
	data->valid_texture = malloc(sizeof(t_texture));//check to free
	if (data->valid_texture == NULL)
		return (error_msg("malloc failed for texture"), false);
	data->valid_texture->floor = 0;
	data->valid_texture->ceiling = 0;
	data->valid_texture->ea = NULL;
	data->valid_texture->no = NULL;
	data->valid_texture->so = NULL;
	data->valid_texture->we = NULL;
	return (true);
}

bool	is_texture_valid(t_game_config *data)
{
	if (data->no == NULL)
		return (false);
	if (data->so == NULL)
		return (false);
	if (data->ea == NULL)
		return (false);
	if (data->we == NULL)
		return (false);
	if (init_texture_struct(data) == false)
		return (false);
	return (true);
}

bool	assign_texture(t_game_config *data)
{
	data->valid_texture->no = mlx_load_png(data->no);
	if (!data->valid_texture->no)
		return (error_msg("texture loading failed: north"), false);
	data->valid_texture->so = mlx_load_png(data->so);
	if (!data->valid_texture->so)
		return (error_message("texture loading failed: south"), false);
	data->valid_texture->we = mlx_load_png(data->we);
	if (!data->valid_texture->we)
		return (error_message("texture loading failed: west"), false);
	data->valid_texture->ea = mlx_load_png(data->ea);
	if (!data->valid_texture->ea)
		return (error_message("texture loading failed: east"), false);
	return (true);
}

bool	parse_texture_n_color(t_game_config *data)
{
	if (is_texture_valid(data) == false)
		return (error_message("invalid texture"), false);
	if (assign_texture(data) == false)
		return (false);
	if (parse_color(data, data->ceiling_color) == false
		|| parse_color(data, data->floor_color) == false)
		return (false);
	return (true);
}
