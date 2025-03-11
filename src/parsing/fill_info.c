/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_info.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 11:43:31 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/03/11 12:13:33 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//the temp returns null or texture_path
//it is freed in clean.c

char	*extract_texture_path(char *str)
{
	char	*temp;
	int		i;
	int		len;

	i = 2;
	if (!str)
		return (NULL);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	len = ft_strlen(&str[i]);
	temp = malloc(sizeof(char) * len);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, &str[i], len);
	return (temp);
}

/*
 * Ensures each texture is defined only once by checking if the corresponding 
 * texture pointer in t_game is NULL. If a texture is already set 
 * (i.e., not NULL), it triggers an error message to prevent overwriting 
 * previously assigned values, ensuring the integrity of the game configuration.
 */

int	fill_texture_path(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		if (game->no != NULL)
			return (error_msg("Duplicate texture definition: North"), 1);
		game->no = extract_texture_path(line);
	}
	if (ft_strncmp(line, "WE", 2) == 0)
	{
		if (game->we != NULL)
			return (error_msg("Duplicate texture definition: West"), 1);
		game->we = extract_texture_path(line);
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		if (game->so != NULL)
			return (error_msg("Duplicate texture definition: South"), 1);
		game->so = extract_texture_path(line);
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		if (game->ea != NULL)
			return (error_msg("Duplicate texture definition: East"), 1);
		game->ea = extract_texture_path(line);
	}
	return (0);
}

int	fill_color_line(t_game *game, char *line)
{
	if (ft_strncmp(line, "F", 1) == 0)
	{
		if (game->floor_color != NULL)
			return (error_msg("Duplicate color definition: floor\n"), 1);
		game->floor_color = ft_strdup(line);
	}
	else if (ft_strncmp(line, "C", 1) == 0)
	{
		if (game->ceiling_color != NULL)
			return (error_msg("Duplicate color definition; ceiling\n"), 1);
		game->ceiling_color = ft_strdup(line);
	}
	return (0);
}

int	fill_info(t_game *game, char *line)
{
	if (fill_texture_path(game, line) != 0)
		return (1);
	if (fill_color_line(game, line) != 0)
		return (1);
	return (0);
}
