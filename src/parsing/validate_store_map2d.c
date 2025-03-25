/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_store_map2d.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/24 15:56:45 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/03/25 12:34:03 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	skip_to_map_start(t_game *game, char *temp, int i, int fd)
{
	while (i++ < game->map->pre_start_line_num)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		free(temp);
	}
}
//space is VALIDATED as a char here

int	is_valid_char(char *str)
{
	const char	*valid;
	int			i;

	valid = "01NSEW\n ";
	i = 0;
	while (str[i])
	{
		if (!ft_strchr(valid, str[i]))
			return (1);
		i++;
	}
	return (0);
}

static bool	allocate_map2d(t_game *game)
{
	game->map->map2d = ft_calloc(game->map->height + 1, sizeof(char *));
	if (!game->map->map2d)
		return (error_msg("memory allocation failed for map2d\n"), false);
	return (true);
}

static bool	process_map_lines(t_game *game, int fd)
{
	char	*temp;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (1)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		if (is_valid_char(temp))
			flag = -2;
		game->map->map2d[i++] = ft_strtrim(temp, "\n");
		free(temp);
	}
	if (flag != 0)
		return (error_msg("invalid char"), false);
	return (true);
}

bool	validate_n_store_map2d(char *map_file, t_game *game)
{
	int		fd;
	int		i;
	char	*temp;

	i = 0;
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (error_msg("cannot open file\n"), false);
	temp = NULL;
	skip_to_map_start(game, temp, i, fd);
	if (allocate_map2d(game) == false)
		return (false);
	return (process_map_lines(game, fd));
}
