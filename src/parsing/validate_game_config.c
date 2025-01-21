/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_game_config.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 18:51:09 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/21 19:29:44 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"


bool	validate_game_config(char *argv, t_game_config *data)
{
	
	// if (is_full(data) == false)
	// 	return (error_message("Missing elements"), false);
	// if (is_map_filled(argv, data) == false)
	// 	return (false);
	// if (find_player(data) == false)
	// 	return (error_message("Player not found"), false);
	// if (flood_fill(data->map, 0, data->map->p_y, data->map->p_x))
	// 	return (error_message("Invalid map"), false);
	return (true);
}
//TODO: /optional/breakdown or separate is_map_filled function and not pass
// argv here