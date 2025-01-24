/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_game_config.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 18:51:09 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/24 16:29:11 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//is_config_full is checking if all variables in the t_game_config struct r set
//meaning (non-zero or non-NULL).

int	is_config_full(t_game_config *data)
{
	if (data->ceiling_color == 0)
		return (error_msg("missing ceiling color\n"), false);
	if (data->floor_color == 0)
		return (error_msg("missing floor color\n"), false);
	if (data->ea == NULL)
		return (error_msg("missing east texture\n"), false);
	if (data->we == NULL)
		return (error_msg("missing west texture\n"), false);
	if (data->so == NULL)
		return (error_msg("missing south texture\n"), false);
	if (data->no == NULL)
		return (error_msg("missing north texture\n"), false);
	return (true);
}

bool	validate_game_config(char *map_file, t_game_config *data)
{
	if (is_config_full(data) == false)
		return (error_msg("missing config info\n"), false);
	if (validate_n_store_map2d(map_file, data) == false)
		return (false);
	if (parse_player(data) == false)
		return (error_msg("Player not found"), false);
	// if (flood_fill(data->map, 0, data->map->p_y, data->map->p_x))
	// 	return (error_message("Invalid map"), false);
	return (true);
}
//TODO: /optional/breakdown or separate is_map_filled function and not pass
//TODO: rename validate_n_store_map2d, as parse_map??
