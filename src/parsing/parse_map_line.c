/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map_line.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 16:27:28 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/02/26 17:30:55 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//parse_map_line verifies if a line in the .cub file is a valid map line
//Ensures lines only contain valid characters (0-9, N, S, E, W).
//Handles whitespace by trimming the line.
//Initializes the game->map structure if it's not already allocated and 
//sets the (pre_start_line_num) to the current line number

bool	parse_map_line(char *current_line, int line_num, t_game *game)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_strtrim(current_line, "\n\t ");
	while (temp[i] && (ft_isdigit(temp[i]) || is_player_dir(temp[i])))
		i++;
	if (ft_strlen(temp) == 0 || (!ft_isdigit(temp[i]) && temp[i] != '\0'))
		return (free(temp), false);
	if (!game->map)
	{
		game->map = ft_calloc(1, sizeof(t_map));
		if (!game->map)
			return (error_msg("Malloc fail for game->map"), false);
		game->map->pre_start_line_num = line_num;
	}
	return (free(temp), true);
}
