/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_player.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/24 16:29:25 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/24 17:12:26 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	is_player_dir(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (c);
	return (0);
}

bool	set_player_coordinate(t_game_config *data, int *row, int *clmn, int *i)
{
	while (data->map->map2d[(*row)][(*clmn)])
	{
		if (data->map_start_row == 0)
			data->map_start_row = data->map->height;
		if (is_player_dir(data->map->map2d[(*row)][(*clmn)]))
		{
			(*i)++;
			if ((*i) != 1)
				return (false);
			data->map->player_x = (*clmn);
			data->map->player_y = (*row);
			data->map->player_facing_to = is_player_dir(
					data->map->map2d[(*row)][(*clmn)]);
			data->map->map2d[(*row)][(*clmn)] = '0';
		}
		(*clmn)++;
	}
	return (true);
}

void	update_map_size(t_game_config *data, int column)
{
	if (column > data->map->map_weidth)
		data->map->map_weidth = column - 1;
	data->map->height++;
}

bool	parse_player(t_game_config *data)
{
	int	colmn;
	int	row;
	int	i;

	row = 0;
	i = 0;
	data->map_start_row = 0;
	while (data->map->map2d[++row])
	{
		colmn = 0;
		if (set_player_coordinate(data, &row, &colmn, &i) == false)
			return (false);
		update_map_size(data, colmn);
	}
	if (i != 1)
		return (false);
	data->map->height -= data->map_start_row;
	return (true);
}
