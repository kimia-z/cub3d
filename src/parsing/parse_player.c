/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_player.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/24 16:29:25 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/29 12:25:12 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	is_player_dir(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (c);
	return (0);
}

//setting the variable first_non_empty_row as height
//it has been done by passing the variable to this func by reference
//(using a pointer like &num_of_chars_in_row)
//so the changes to this variable persist outside the function.

bool	search_player_set_config(t_game_config *data,
				int *row, int *clmn, int *player_count)
{
	while (data->map->map2d[(*row)][(*clmn)])
	{
		if (data->first_non_empty_row == 0)
			data->first_non_empty_row = data->map->height;
		if (is_player_dir(data->map->map2d[(*row)][(*clmn)]))
		{
			(*player_count)++;
			if ((*player_count) != 1)
				return (false);
			data->map->player_x = (*clmn);
			data->map->player_y = (*row);
			data->map->player_facing_to = is_player_dir(
					data->map->map2d[(*row)][(*clmn)]);
		}
		(*clmn)++;
	}
	return (true);
}
// calculate width here 
// if the width is smaller than the chars of the current row
// we set it to the highest weidht 
// TODO: check if (- 1 ) in width is necessary  coz index starts at 0
// height++ keeps trck of how many rows processed

void	update_map_size(t_game_config *data, int num_of_chars_in_row)
{
	if (num_of_chars_in_row > data->map->width)
		data->map->width = num_of_chars_in_row;
	data->map->height++;
}
//while iterates through every row(element of array) in map2d
//num_of_chars_in_row resets to 0 for every row
//call search_player_set_config for every row

bool	parse_player(t_game_config *data)
{
	int	num_of_chars_in_row;
	int	row;
	int	player_count;

	row = 0;
	player_count = 0;
	data->first_non_empty_row = 0;
	while (data->map->map2d[++row])
	{
		num_of_chars_in_row = 0;
		if (search_player_set_config(
				data, &row, &num_of_chars_in_row, &player_count) == false)
			return (false);
		update_map_size(data, num_of_chars_in_row);
	}
	if (player_count != 1)
		return (false);
	data->map->height = data->first_non_empty_row;
	return (true);
}

//TODO: make a copy of map and then use it for floodfill
//TODO: study first_no_empty_row and check if we can not use it
//The height is being overwritten as data->first_non_empty_row, which is not correct
//You likely want the total number of rows (non-empty) instead. test it