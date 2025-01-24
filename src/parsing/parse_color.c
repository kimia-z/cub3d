/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_color.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 19:31:07 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/24 14:45:27 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	count_arr_elements(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
//32-bit integer = data type.
//Decimal = number system
//hexadecimal = number system

//32-bit number is represented using 32 binary digits (bits), 
//where each bit can be either 0 or 1. can be signed or unsigned.
//32-bit binary number: 11010110101110101011010111110001(32 digits)
//Hexadecimal version is used for easier reading and compactness
//The binary number above would be represented as 0xDAB5F1F1 in hexadecimal.

//get_rgb COMBINES the individual RGB (Red, Green, Blue) values 
//and the alpha (opacity) value into a single 32-bit integer.
//Left shifting a number n by m bits (n << m) means multiplying n by 2^m.
//because every number needs to be specifically positioned in a 32-bit number
// | (bitwise OR) operator combines all the shifted values into 1 32-bit number.

static int	get_rgb(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_colors(t_game_config *data, char **color_num, char **line_elmn)
{
	int		i;
	int		number;
	int		arg[3];
	int32_t	rgb;

	i = 0;
	while (color_num[i])
	{
		number = ft_atoi(color_num[i]);
		if (number < 0 || number > 255)
			return (error_msg("RGB values must be 0-255."), 1);
		arg[i] = number;
		i++;
	}
	rgb = get_rgb(arg[0], arg[1], arg[2], 255);
	if (!ft_strcmp(line_elmn[0], "F"))
		data->valid_texture->floor = rgb;
	else if (!ft_strcmp(line_elmn[0], "C"))
		data->valid_texture->ceiling = rgb;
	return (EXIT_SUCCESS);
}

//parse_color receives one color line at a time from the map
//replace tabs with spaces for simplification
//split the string at space
//must be only 2 elements in the array:
//element one: (name of the 'to be painted' area i. e. floor or ceiling)
//element 2: (the rgb values for colors)
//split rgb values at ','; must be 3 

int	parse_color(t_game_config *data, char *color_line)
{
	int		i;
	char	**color_num;
	char	**line_elmn;

	i = 0;
	if (!color_line)
		return (error_msg("missing color string"), 0);
	while (color_line[i] == '\t')
		color_line[i++] = ' ';
	color_line[ft_strlen(color_line)] = '\0';
	line_elmn = ft_split(color_line, ' ');
	if (count_arr_elements(line_elmn) != 2)
		return (free_array(line_elmn), error_msg("Invalid color format\n"), 0);
	color_num = ft_split(line_elmn[1], ',');
	if (count_arr_elements(color_num) != 3)
		return (free_array(color_num), error_msg("Invalid color numbers\n"), 0);
	if (!get_colors(data, color_num, line_elmn))
		return (free_array(color_num), free_array(line_elmn), 1);
	free_array(color_num);
	free_array(line_elmn);
	return (0);
}

//TODO: consider returning 1 when error


