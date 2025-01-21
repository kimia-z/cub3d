/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:06:52 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/21 19:07:07 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	init_config(t_game_config *data)
{
	//data->mapa = NULL;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->floor_color = NULL;
	data->ceiling_color = NULL;
	data->valid_texture = NULL;
	data->map = NULL;
}
