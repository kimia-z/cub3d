/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_color.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 19:31:07 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/21 19:34:08 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_arrlen(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

static int	get_rgb(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_colors(t_file *valid_file, char **color, char **word)
{
	int		i;
	int		number;
	int		arg[3];
	int32_t	rgb;

	i = 0;
	while (color[i])
	{
		number = ft_atoi(color[i]);
		if (number < 0 || number > 255)
			return (error_message("Wrong color selection"), 1);
		arg[i] = number;
		i++;
	}
	rgb = get_rgb(arg[0], arg[1], arg[2], 255);
	if (!ft_strcmp(word[0], "F"))
		valid_file->valid_tex->floor = rgb;
	else if (!ft_strcmp(word[0], "C"))
		valid_file->valid_tex->ceil = rgb;
	return (EXIT_SUCCESS);
}

int	parse_color(t_game_config *valid_file, char *word)
{
	int		i;
	char	**color;
	char	**line;

	i = 0;
	if (!word)
		return (error_message("missing color"), 0);
	while (word[i] == '\t')
		word[i++] = ' ';
	word[ft_strlen(word)] = '\0';
	line = ft_split(word, ' ');
	if (ft_arrlen(line) != 2)
		return (free_split(line), error_message("Wrong color selection"), 0);
	color = ft_split(line[1], ',');
	if (ft_arrlen(color) != 3)
		return (free_split(color), error_message("Wrong color selection"), 0);
	if (!get_colors(valid_file, color, line))
		return (free_split(color), free_split(line), 1);
	free_split(color);
	free_split(line);
	return (0);
}

