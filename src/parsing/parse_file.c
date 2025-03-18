/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_file.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:06:44 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/03/18 10:47:53 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_2d_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) || is_player_dir(line[i]))
			return (true);
		i++;
	}
	return (false);
}
//fisrt it trims whitespace from all received lines
//Then it updates temp lines using while loop so that temp---
//Only contain valid characters (0-9, N, S, E, W) for 2Dmap
//Initializes the game->map structure if it's not already allocated and 
//sets the (pre_start_line_num) to the current line number

bool	allocate_2dmap_line(char *current_line, int line_num, t_game *game)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_strtrim(current_line, "\n\t ");
	if (!temp)
		return (false);
	while (temp[i] && (ft_isdigit(temp[i]) || is_player_dir(temp[i])))
		i++;
	if (temp[i] != '\0' && (ft_strlen(temp) == 0 || !ft_isdigit(temp[i])
			|| !is_player_dir(temp[i])))
		return (error_msg("invalid char in 2dmap\n"),free(temp), false);
	if (!game->map)
	{
		game->map = ft_calloc(1, sizeof(t_map));
		if (!game->map)
			return (error_msg("Malloc fail for game->map"), false);
		game->map->pre_start_line_num = line_num;
	}
	return (free(temp), true);
}

bool	is_texture_png(char *str)
{
	int	len;

	if (!str)
		return (false);
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
// Check if the line contains only empty spaces or tabs by while
//// break loop as we encounter non-whitespace characters
// If we reached the end and no non-whitespace characters were found
// Processes each line to fill game configuration game (textures, colors, etc.).
// Identifies and processes map lines, initializing map game if required.
// Ensures all lines are parsed before calculating the map's height.
// get_next_line returns NULL at EOF, ensuring no partial height calculation.
// Closes the file descriptor after processing all lines.

int	parse_file(char *file, t_game *game)
{
	char	*current_line;
	int		line_num;
	int		fd;

	line_num = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_msg("cannot open file\n"), -1);
	current_line = get_next_line(fd);
	while (current_line != NULL)
	{
		if (is_2d_map_line(current_line) == true)
		{
			if (allocate_2dmap_line(current_line, line_num, game) == false)
				return (free(current_line), close(fd), -1);
		}
		if (validate_texture_line(current_line) == false
			|| fill_info(game, current_line) != 0)
			return (free(current_line), close(fd), -1);
		(free(current_line), current_line = get_next_line(fd));
		line_num++;
	}
	if (game->map && game->map->pre_start_line_num >= 0
		&& line_num > game->map->pre_start_line_num)
		game->map->height = line_num - game->map->pre_start_line_num;
	else
		return (error_msg("2D map is missing\n"), -1);
	return (close(fd));
}
