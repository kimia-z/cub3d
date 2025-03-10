/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_png.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 16:24:43 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/03/10 16:27:33 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdbool.h>

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
	len = ft_strlen(str);
	if (str && ft_strncmp(&str[len - 4], ".png", 4) != 0)
	{
		error_msg("texture file invalid\n");
		return (false);
	}
	return (true);
}


bool	check_png(char *current_line)
{
	int		i;
	char	*temp;
	char	*texture_path;

	i = 0;
	temp = ft_strtrim(current_line, "\n\t ");
	if (ft_strncmp(temp, "SO ", 3) == 0 || ft_strncmp(temp, "NO ", 3) == 0
		|| ft_strncmp(temp, "WE ", 3) == 0 || ft_strncmp(temp, "EA ", 3) == 0)
	{
		texture_path = ft_strtrim(temp + 3, "\n\t ");
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
