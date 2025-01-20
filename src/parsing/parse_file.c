#include "../../cub3d.h"

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
		if (data->NO != NULL)
			return (error_msg("Duplicate texture definition for North"), 1);
		data->NO = skip_space(line);
	}
	if (ft_strncmp(line, "WE", 2) == 0)
	{
		if (data->WE != NULL)
			return (error_msg("Duplicate texture definition for West"), 1);
		data->WE = skip_space(line);
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		if (data->SO != NULL)
			return (error_msg("Duplicate texture definition for South"), 1);
		data->SO = skip_space(line);
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		if (data->EA != NULL)
			return (error_msg("Duplicate texture definition for East"), 1);
		data->EA = skip_space(line);
	}
	return (0);
}

int	fill_color(t_game_config *data, char *line)
{
	if (ft_strncmp(line, "F", 1) == 0)
	{
		if (data->floor_color != NULL)
			return (error_msg("Floor color already defined, cannot redefine."), 1);
		data->floor_color = ft_strdup(line);
	}
	else if (ft_strncmp(line, "C", 1) == 0)
	{
		if (data->ceiling_color != NULL)
			return (error_msg("Ceiling color already defined, cannot redefine."), 1);
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

int	parse_file(char *file, t_game_config *data)
{
	char	*current_line;
	int		line_num;
	int		fd;

	line_num = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_msg("File read failed\n"), -1);
	current_line = get_next_line(fd);
	if (current_line == NULL)
		return (error_message("get_next_line failed\n"), -1);
	while (current_line != NULL)
	{
		if (fill_information(data, current_line) != 0)
			return (free(current_line), -1);
		// is_map(current_line, line_num, data);
		// free(current_line);
		// line_num++;
		// current_line = get_next_line(fd);
	}
	// free(current_line);
	// if (data->map)
	// 	data->map->h_map = line_num - data->map->start_y;
	// return (close(fd));
}


