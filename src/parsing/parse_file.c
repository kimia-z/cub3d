/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_file.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:06:44 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/03/25 13:00:11 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_texture_png(char *str)
{
	int	len;
	int	fd;

	if (!str)
		return (false);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (error_msg("cannot open texture file\n"), false);
	close (fd);
	len = ft_strlen(str);
	if (len < 4)
	{
		error_msg("texture file invalid: filename too short\n");
		return (false);
	}
	if (str && ft_strncmp(&str[len - 4], ".png", 4) != 0)
	{
		error_msg("texture file invalid\n");
		return (false);
	}
	return (true);
}

//if it is a texture line begins with identifier (SO/EA/NO/WE) we enter block
//remove "trailing" newlines/tabs becuse for cases like .png\n
////If we have nothing after identifier or if there is no space/tab after it
//////exit

bool	validate_texture_line(char *line)
{
	int		i;
	char	*temp;
	char	*texture_path;

	i = 0;
	temp = NULL;
	if ((ft_strncmp(line, "SO", 2) == 0 || ft_strncmp(line, "NO", 2) == 0
			|| ft_strncmp(line, "WE", 2) == 0
			|| ft_strncmp(line, "EA", 2) == 0))
	{
		temp = ft_strtrim(line, "\n\t ");
		if (!temp)
			return (error_msg("malloc failed for ft_strtrim\n"), false);
		if (ft_strlen(temp) <= 2)
			return (free(temp), error_msg("texture file not found\n"), false);
		if (temp[2] != ' ' && temp[2] != '\t')
			return (free(temp), error_msg("texture line misaligned\n"), false);
		texture_path = ft_strtrim(temp + 2, "\n\t ");
		if (!texture_path)
			return (free(temp), false);
		if (!is_texture_png(texture_path))
			return (free(temp), free(texture_path), false);
		free(texture_path);
	}
	return (free(temp), true);
}
// Opens the file and reads it line by line using get_next_line.
// if we read a line (non-null)
// process and allocate 2d map line if valid
// Processes each line to fill game configuration game (textures, colors, etc.).
// calculate height

static int	process_line(char *line, t_game *game, int line_num, int *flag)
{
	if (validate_2dmap_line(line, line_num, game) == -1)
		*flag = -3;
	if (validate_texture_line(line) == false || assign_input(game, line) != 0)
		*flag = -2;
	return (*flag);
}

static int	validate_map_presence(t_game *game, int line_num)
{
	if (game->map && game->map->pre_start_line_num >= 0
		&& line_num > game->map->pre_start_line_num)
	{
		game->map->height = line_num - game->map->pre_start_line_num;
		return (0);
	}
	return (error_msg("map is missing\n"), -1);
}

int	parse_file(char *file, t_game *game)
{
	char	*current_line;
	int		line_num;
	int		fd;
	int		flag;

	line_num = 0;
	flag = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_msg("cannot open file\n"), -1);
	current_line = get_next_line(fd);
	while (current_line != NULL)
	{
		process_line(current_line, game, line_num, &flag);
		free(current_line);
		current_line = get_next_line(fd);
		line_num++;
	}
	if (flag != 0)
		return (close(fd), -1);
	return (validate_map_presence(game, line_num), close(fd));
}
