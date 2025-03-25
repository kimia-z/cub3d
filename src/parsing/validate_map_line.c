/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map_line.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/25 12:56:24 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/03/25 12:58:15 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	handle_invalid_line(char *temp)
{
	if (temp[0] == 'F' || temp[0] == 'C' || temp[0] == 'N' || temp[0] == 'S'
		|| temp[0] == 'W' || temp[0] == 'E'
		|| (temp[0] == 'S' && temp[1] == 'O')
		|| (temp[0] == 'N' && temp[1] == 'O')
		|| (temp[0] == 'E' && temp[1] == 'A')
		|| (temp[0] == 'W' && temp[1] == 'E'))
		return (free(temp), 0);
	else
		return (error_msg("invalid chars in map"), free(temp), -1);
}

//fisrt it trims whitespace from all received lines
//it skips temp lines that has
//valid characters (0-9, N, S, E, W) for 2Dmap
//handles invalid lines
//sets the (pre_start_line_num) to the current line number

int	validate_2dmap_line(char *line, int line_num, t_game *game)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_strtrim(line, "\n\t ");
	if (!temp)
		return (-1);
	while (temp[i] && (ft_isdigit(temp[i]) || is_player_dir(temp[i])
			|| temp[i] == ' '))
		i++;
	if (temp[i] != '\0')
		return (handle_invalid_line(temp));
	if (ft_strlen(temp) == 0)
		return (free(temp), 0);
	if (!game->map)
	{
		game->map = ft_calloc(1, sizeof(t_map));
		if (!game->map)
			return (error_msg("Malloc fail for game->map"), -1);
		game->map->pre_start_line_num = line_num;
	}
	return (free(temp), true);
}
