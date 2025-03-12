/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_info.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 11:43:31 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/03/12 12:50:07 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//texture_path is freed in clean.c

char	*allocate_texture_path(char *str)
{
	char	*texture_path;
	int		i;
	int		len;

	i = 2;
	if (!str)
		return (NULL);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	len = ft_strlen(&str[i]);
	texture_path = malloc(sizeof(char) * len);
	if (!texture_path)
		return (NULL);
	ft_strlcpy(texture_path, &str[i], len);
	return (texture_path);
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
		game->no = allocate_texture_path(line);
	}
	if (ft_strncmp(line, "WE", 2) == 0)
	{
		if (game->we != NULL)
			return (error_msg("Duplicate texture definition: West"), 1);
		game->we = allocate_texture_path(line);
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		if (game->so != NULL)
			return (error_msg("Duplicate texture definition: South"), 1);
		game->so = allocate_texture_path(line);
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		if (game->ea != NULL)
			return (error_msg("Duplicate texture definition: East"), 1);
		game->ea = allocate_texture_path(line);
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
