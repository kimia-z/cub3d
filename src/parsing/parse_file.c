/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_file.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:06:44 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/24 16:00:21 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*skip_space(char *str)
{
	char	*temp;
	int		i;
	int		len;

	i = 2;
	if (!str)
		return (NULL);
	if (str[i] != ' ' && str[i] != '\t')
		return (NULL);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	len = ft_strlen(&str[i]);
	temp = malloc(sizeof(char) * len);//check if it needs to be freed later
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, &str[i], len);
	return (temp);
}

/*
 * Ensures each texture is defined only once by checking if the corresponding 
 * texture pointer in t_game_config is NULL. If a texture is already set 
 * (i.e., not NULL), it triggers an error message to prevent overwriting 
 * previously assigned values, ensuring the integrity of the game configuration.
 */

int	fill_texture(t_game_config *data, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		if (data->no != NULL)
			return (error_msg("Duplicate texture definition: North"), 1);
		data->no = skip_space(line);
	}
	if (ft_strncmp(line, "WE", 2) == 0)
	{
		if (data->we != NULL)
			return (error_msg("Duplicate texture definition: West"), 1);
		data->we = skip_space(line);
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		if (data->so != NULL)
			return (error_msg("Duplicate texture definition: South"), 1);
		data->so = skip_space(line);
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		if (data->ea != NULL)
			return (error_msg("Duplicate texture definition: East"), 1);
		data->ea = skip_space(line);
	}
	return (0);
}

int	fill_color(t_game_config *data, char *line)
{
	if (ft_strncmp(line, "F", 1) == 0)
	{
		if (data->floor_color != NULL)
			return (error_msg("Duplicate color definition: floor\n"), 1);
		data->floor_color = ft_strdup(line);
	}
	else if (ft_strncmp(line, "C", 1) == 0)
	{
		if (data->ceiling_color != NULL)
			return (error_msg("Duplicate color definition; ceiling\n"), 1);
		data->ceiling_color = ft_strdup(line);
	}
	return (0);
}

//remove this function if norminette agrees

int	fill_information(t_game_config *data, char *line)
{
	if (fill_texture(data, line) != 0)
		return (1);
	if (fill_color(data, line) != 0)
		return (1);
	return (0);
}
// Opens the file and reads it line by line using get_next_line.
// Processes each line to fill game configuration data (textures, colors, etc.).
// Identifies and processes map lines, initializing map data if required.
// Ensures all lines are parsed before calculating the map's height.
// get_next_line returns NULL at EOF, ensuring no partial height calculation.
// Closes the file descriptor after processing all lines.

int	parse_file(char *file, t_game_config *data)
{
	char	*current_line;
	int		line_num;
	int		fd;

	line_num = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_msg("open file failed\n"), -1);
	current_line = get_next_line(fd);
	if (current_line == NULL)
		return (error_msg("get_next_line failed\n"), -1);
	while (current_line != NULL)
	{
		if (fill_information(data, current_line) != 0)
			return (free(current_line), -1);
		parse_map_line(current_line, line_num, data);
		free(current_line);
		line_num++;
		current_line = get_next_line(fd);
	}
	free(current_line);
	if (data->map)
		data->map->height = line_num - data->map->pre_start_line_num;
	return (close(fd));
}
