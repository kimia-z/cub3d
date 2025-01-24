/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_game_config.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 18:51:09 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/24 14:29:04 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// int	is_config_full(t_game_config *data)
// {
// 	return (data->ceiling_color && data->floor_color
// 		&& data->ea && data->we && data->so && data->no);
// }

// bool	validate_game_config(char *argv, t_game_config *data)
// {

// 	if (is_config_full(data) == false)
// 		return (error_msg("Missing config info"), false);
	// if (is_map_filled(argv, data) == false)
	// 	return (false);
	// if (find_player(data) == false)
	// 	return (error_message("Player not found"), false);
	// if (flood_fill(data->map, 0, data->map->p_y, data->map->p_x))
	// 	return (error_message("Invalid map"), false);
	//return (true);
//}
//TODO: /optional/breakdown or separate is_map_filled function and not pass
// argv here