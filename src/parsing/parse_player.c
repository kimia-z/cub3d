/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_player.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/24 16:29:25 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/03/19 14:06:28 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	is_player_dir(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (c);
	return (0);
}

//setting the variable height_keeper as height
//it has been done by passing the variable to this func by reference
//(using a pointer like &column)
//so the changes to this variable persist outside the function.

bool	search_player_set_config(t_game *game,
				int *row, int *column, int *player_count)
{
	while (game->map->map2d[(*row)][(*column)])
	{
		if (game->height_keeper == 0)
			game->height_keeper = game->map->height;
		if (is_player_dir(game->map->map2d[(*row)][(*column)]))
		{
			(*player_count)++;
			if ((*player_count) != 1)
				return (false);
			game->map->player_x = (*column);
			game->map->player_y = (*row);
			game->map->player_facing_to = is_player_dir(
					game->map->map2d[(*row)][(*column)]);
		}
		(*column)++;
	}
	return (true);
}
// calculate width here 
// if the width is smaller than the chars of the current row
// we set it to the highest weidht 
// height++ keeps track of how many rows processed
//meaning move to the next row

void	update_map_size(t_game *game, int column)
{
	if (column > game->map->width)
		game->map->width = column;
	game->map->height++;
}
//while iterates through every row(element of array) in map2d
//column resets to 0 for every row//it means column
//call search_player_set_config for every row
//height marker just remembers the height
//since we will be increasing and decreasing height here

bool	parse_player(t_game *game)
{
	int	column;
	int	row;
	int	player_count;

	row = -1;
	player_count = 0;
	game->height_keeper = 0;
	while (game->map->map2d[++row])
	{
		column = 0;
		if (search_player_set_config(
				game, &row, &column, &player_count) == false)
			return (false);
		update_map_size(game, column);
	}
	if (player_count != 1)
		return (error_msg("player not found\n"), false);
	game->map->height = game->height_keeper;
	return (true);
}
