/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_file.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:06:44 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/03/11 12:00:36 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//validate_all_line verifies if a line in the .cub file is a valid map line
//Ensures lines only contain valid characters (0-9, N, S, E, W).
//Handles whitespace by trimming the line.
//Initializes the game->map structure if it's not already allocated and 
//sets the (pre_start_line_num) to the current line number

bool	validate_all_line(char *current_line, int line_num, t_game *game)
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

//for checking png, first remove trailing newlines/tabs
//then if the line begins with SO/EA/NO/WE--
////we check if it is only SO/EA/NO/WE and nothing sfterwords--
// then extract texture path and see if png

bool	check_png(char *current_line)
{
	int		i;
	char	*temp;
	char	*texture_path;

	i = 0;
	temp = ft_strtrim(current_line, "\n\t ");
	if (ft_strncmp(temp, "SO", 2) == 0 || ft_strncmp(temp, "NO", 2) == 0
		|| ft_strncmp(temp, "WE", 2) == 0 || ft_strncmp(temp, "EA", 2) == 0)
	{
		if (ft_strlen(temp) <= 2)
		{
			free(temp);
			return (error_msg("texture file not found\n"), false);
		}
		texture_path = ft_strtrim(temp + 2, "\n\t ");
		if (!is_texture_png(texture_path))
		{
			free(temp);
			free(texture_path);
			return (false);
		}
		free(texture_path);
	}
	return (free(temp), true);
}
// Opens the file and reads it line by line using get_next_line.
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
	if (current_line == NULL)
		return (error_msg("get_next_line failed\n"), -1);
	while (current_line != NULL)
	{
		validate_all_line(current_line, line_num, game);
		if (check_png(current_line) == false)
			return (free(current_line), -1);
		if (fill_info(game, current_line) != 0)
			return (free(current_line), -1);
		free(current_line);
		line_num++;
		current_line = get_next_line(fd);
	}
	if (game->map)
		game->map->height = line_num - game->map->pre_start_line_num;
	return (close(fd));
}
