/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_store_map2d.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/24 15:56:45 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/24 16:26:02 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	skip_to_map_start(t_game_config *data, char *temp, int i, int fd)
{
	while (i++ < data->map->pre_start_line_num)
	{
		temp = get_next_line(fd);
		free(temp);
	}
}

static int	is_valid_char(char *str)
{
	char	*valid;
	int		i;

	valid = "01NSEW\n ";
	i = -1;
	while (str[++i])
	{
		if (!ft_strchr(valid, str[i]))
			return (1);
	}
	return (0);
}

static bool	allocate_map2d(t_game_config *data)
{
	data->map->map2d = ft_calloc(data->map->height + 1, sizeof(char *));
	if (!data->map->map2d)
		return (error_msg("memory allocation failed for map2d\n"), false);
	return (true);
}

bool	validate_n_store_map2d(char *map_file, t_game_config *data)
{
	int		fd;
	int		i;
	char	*temp;

	i = 0;
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (error_msg("open file failed"), false);
	temp = NULL;
	skip_to_map_start(data, temp, i, fd);
	i = 0;
	if (allocate_map2d(data) == false)
		return (false);
	while (1)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		if (is_valid_char(temp))
			return (error_msg("invalid character in map"), free(temp), false);
		data->map->map2d[i++] = ft_strtrim(temp, "\n");
		free(temp);
	}
	free(temp);
	return (true);
}


